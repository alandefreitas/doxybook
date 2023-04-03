//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#define NOMINMAX 1
#include <doxybook/default_templates.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/renderer.hpp>
#include <doxybook/utils.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <dirent.h>
#include <set>
#include <inja/inja.hpp>
#include <unordered_set>

#ifdef _WIN32
static const std::string SEPARATOR = "\\";
#else
static const std::string SEPARATOR = "/";
#endif

static std::string
trimPath(std::string path) {
    while (path.back() == '/') {
        path.pop_back();
    }
    while (path.back() == '\\') {
        path.pop_back();
    }
    if (path.find(".\\") == 0) {
        path = path.substr(2);
    }
    if (path.find("./") == 0) {
        path = path.substr(2);
    }
    return path;
}

static std::string
stripTmplSuffix(std::string path) {
    if (path.size() > 4 && path.find(".tmpl") == path.size() - 5) {
        path.erase(path.size() - 5);
    }
    return path;
}

static void
directoryIterator(
    std::string const& path,
    std::function<void(std::string const&)> const& callback) {
    auto dir = opendir(path.c_str());
    if (dir == nullptr) {
        throw EXCEPTION("Failed to read directory {}", path);
    }

    auto const p = trimPath(path);
    auto ent = readdir((DIR*) dir);
    while (ent != nullptr) {
        auto const file = std::string(ent->d_name);
        if (file.size() > 4 && file.find(".tmpl") == file.size() - 5) {
            callback(p + SEPARATOR + file);
        }
        ent = readdir((DIR*) dir);
    }
}

static std::string
filename(std::string const& path) {
    auto const found = path.find_last_of("/\\");
    if (found == std::string::npos) {
        return path;
    }
    return path.substr(found + 1);
}

static std::string
basename(std::string const& path) {
    auto const str = filename(path);
    auto const found = str.find_last_of('.');
    if (found == std::string::npos) {
        return str;
    }
    return str.substr(0, found);
}

doxybook::renderer::renderer(
    const struct config& config,
    const class doxygen& doxygen,
    json_converter const& json_converter,
    std::optional<std::string> const& templates_path)
    : config_(config)
    , doxygen_(doxygen)
    , json_converter_(json_converter)
    , env_(std::make_unique<inja::Environment>(
          templates_path.has_value() ?
              trimPath(*templates_path) + SEPARATOR :
              "./")) {
    env_->add_callback("isEmpty", 1, [](inja::Arguments& args) -> bool {
        if (args.at(0)->is_string()) {
            return args.at(0)->get<std::string_view>().empty();
        }
        return args.at(0)->empty();
    });

    env_->add_callback("at", 2, [](inja::Arguments& args) -> bool {
        if (args.at(0)->is_array()) {
            return args.at(0)->at(args.at(1)->get<std::size_t>());
        } else if (args.at(0)->is_object()) {
            return args.at(0)->at(args.at(1)->get<std::string>());
        }
        return "";
    });

    env_->add_callback("existsNonEmptyIn", 2, [](inja::Arguments& args) -> bool {
        nlohmann::json const& j = *args.at(0);
        std::string k = args.at(1)->get<std::string>();
        if (!j.contains(k)) {
            return false;
        }
        if (j[k].is_string()) {
            return !j[k].get<std::string_view>().empty();
        }
        return !j[k].empty();
    });

    env_->add_callback("escape", 1, [](inja::Arguments& args) -> std::string {
        const auto arg = args.at(0)->get<std::string>();
        return utils::escape(arg);
    });

    env_->add_callback(
        "safeAnchorId",
        1,
        [&config](inja::Arguments& args) -> std::string {
            const auto arg = args.at(0)->get<std::string>();
            return utils::
                safe_anchor_id(arg, config.replaceUnderscoresInAnchors);
        });

    env_->add_callback("title", 1, [](inja::Arguments& args) {
        const auto arg = args.at(0)->get<std::string>();
        return utils::title(arg);
    });

    env_->add_callback("date", 1, [](inja::Arguments& args) -> std::string {
        const auto arg = args.at(0)->get<std::string>();
        return utils::date(arg);
    });

    env_->add_callback(
        "stripNamespace",
        1,
        [](inja::Arguments& args) -> std::string {
            const auto arg = args.at(0)->get<std::string>();
            return utils::strip_namespace(arg);
        });

    env_->add_callback("split", 2, [](inja::Arguments& args) -> nlohmann::json {
        // split("a,b,c", ",") -> ["a", "b", "c"]
        const auto arg0 = args.at(0)->get<std::string>();
        const auto arg1 = args.at(1)->get<std::string>();
        nlohmann::json ret = nlohmann::json::array();
        for (auto& token: utils::split(arg0, arg1)) {
            ret.push_back(std::move(token));
        }
        return ret;
    });

    env_->add_callback(
        "splitAll",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            // split all elements of array
            // splitAll(["a,b", "c"], ",") -> ["a", "b", "c"]
            const auto str_range = *args.at(0);
            const auto delim = args.at(1)->get<std::string>();
            nlohmann::json ret = nlohmann::json::array();
            for (auto& str: str_range) {
                ret.push_back(nlohmann::json::array({}));
                for (auto& token: utils::split(str, delim)) {
                    ret.back().push_back(std::move(token));
                }
            }
            return ret;
        });

    env_->add_callback(
        "splitFirst",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            const auto text = args.at(0)->get<std::string>();
            const auto delim = args.at(1)->get<std::string>();
            std::size_t p = text.find(delim);
            nlohmann::json res = nlohmann::json::object();
            if (p != std::string::npos) {
                res["first"] = text.substr(0, p);
                res["second"] = text.substr(p);
            } else {
                res["first"] = text;
                res["second"] = "";
            }
            return res;
        });

    env_->add_callback(
        "parsArrayToObj",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            // Array (1) of arrays (2) where each entry is a list of strings
            // Each entry in (1) is the list of @par in an overload
            // Each entry in (2) is a string with the @par title "\n\n" and
            // the par block.
            // This callback returns an object where each element is an object
            // where keys are the par title and values are the text
            const auto all_overload_parblocks = *args.at(0);
            const auto delim = "\n\n";
            nlohmann::json res = nlohmann::json::array();
            for (auto const& overload_par_blocks: all_overload_parblocks) {
                res.push_back(nlohmann::json::object());
                for (auto const& jtext: overload_par_blocks) {
                    std::string text = jtext.get<std::string>();
                    std::size_t title_end = text.find(delim);
                    if (title_end != std::string::npos) {
                        res.back()[text.substr(0, title_end)] = text.substr(
                            title_end);
                    } else {
                        res.back()[""] = text;
                    }
                }
            }
            return res;
        });

    env_->add_callback(
        "parsArrayKeys",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            // Array (1) of arrays (2) where each entry is a list of strings
            // Each entry in (1) is the list of @par in an overload
            // Each entry in (2) is a string with the @par title "\n\n" and
            // the par block.
            // This callback returns an array where each element is the
            // title of a @par. The titles are kept in order, unlike in
            // a dictionary.
            const auto all_overload_parblocks = *args.at(0);
            const auto delim = "\n\n";
            nlohmann::json res = nlohmann::json::array();
            for (auto const& overload_par_blocks: all_overload_parblocks) {
                for (auto const& jtext: overload_par_blocks) {
                    std::string text = jtext.get<std::string>();
                    std::size_t title_end = text.find(delim);
                    if (title_end != std::string::npos) {
                        res.push_back(text.substr(0, title_end));
                    } else {
                        res.push_back("");
                    }
                }
            }
            return res;
        });

    env_->add_callback(
        "splitFirstLine",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            const auto text = args.at(0)->get<std::string>();
            std::size_t p = text.find('\n');
            nlohmann::json res = nlohmann::json::object();
            if (p != std::string::npos) {
                res["first"] = text.substr(0, p);
                res["second"] = text.substr(p);
            } else {
                res["first"] = text;
                res["second"] = "";
            }
            return res;
        });

    env_->add_callback("first", 1, [](inja::Arguments& args) -> nlohmann::json {
        const auto arg = args.at(0)->get<nlohmann::json>();
        return arg.front();
    });

    env_->add_callback("last", 1, [](inja::Arguments& args) -> nlohmann::json {
        const auto arg = args.at(0)->get<nlohmann::json>();
        return arg.back();
    });

    env_->add_callback("get", 2, [](inja::Arguments& args) -> nlohmann::json {
        const auto obj = args.at(0)->get<nlohmann::json>();
        const auto key = args.at(1)->get<std::string>();
        return obj.at(key);
    });

    env_->add_callback("index", 2, [](inja::Arguments& args) -> nlohmann::json {
        const auto arr = args.at(0)->get<nlohmann::json>();
        const auto idx = args.at(1)->get<int>();
        if (idx >= 0) {
            return arr.at(idx);
        } else {
            return arr.at(arr.size() + idx);
        }
    });

    env_->add_callback("countProperty", 3, [](inja::Arguments& args) -> int {
        const auto arr = args.at(0)->get<nlohmann::json>();
        const auto key = args.at(1)->get<std::string>();
        const auto value = args.at(2)->get<std::string>();
        auto count = 0;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            auto& obj = *it;
            auto val = obj.at(key);
            if (val == value) {
                count++;
            }
        }
        return count;
    });

    env_->add_callback(
        "queryProperty",
        3,
        [](inja::Arguments& args) -> nlohmann::json {
            const auto arr = args.at(0)->get<nlohmann::json>();
            const auto key = args.at(1)->get<std::string>();
            const auto value = args.at(2)->get<std::string>();
            auto ret = nlohmann::json::array();
            for (auto it = arr.begin(); it != arr.end(); ++it) {
                auto& obj = *it;
                if (obj.at(key) == value) {
                    ret.push_back(obj);
                }
            }
            return ret;
        });

    env_->add_callback("render", 2, [=](inja::Arguments& args) -> nlohmann::json {
        const auto name = args.at(0)->get<std::string>();
        const auto data = args.at(1)->get<nlohmann::json>();
        return this->render(name, data);
    });

    env_->add_callback("load", 1, [&](inja::Arguments& args) -> nlohmann::json {
        const auto refid = args.at(0)->get<std::string>();
        return json_converter.get_as_json(*doxygen.find(refid));
    });

    env_->add_callback("replace", 3, [](inja::Arguments& args) -> nlohmann::json {
        auto str = args.at(0)->get<std::string>();
        const auto what = args.at(1)->get<std::string>();
        const auto sub = args.at(2)->get<std::string>();

        std::string::size_type n = 0;
        while ((n = str.find(what, n)) != std::string::npos) {
            str.replace(n, what.size(), sub);
            n += sub.size();
        }
        return str;
    });

    env_->add_callback(
        "contains",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            nlohmann::json const& range = *args.at(0);
            nlohmann::json const& what = *args.at(1);
            return std::find(range.begin(), range.end(), what) != range.end();
        });

    env_->add_callback(
        "allContains",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            // check if all arrays in arrays of arrays contain element
            nlohmann::json const& range_out = *args.at(0);
            nlohmann::json const& what = *args.at(1);
            return std::all_of(
                range_out.begin(),
                range_out.end(),
                [&what](nlohmann::json const& range_in) {
            return std::find(range_in.begin(), range_in.end(), what)
                   != range_in.end();
                });
        });

    env_->add_callback("allOf", 2, [](inja::Arguments& args) -> nlohmann::json {
        // check if all values in array of objects are true
        nlohmann::json const& obj_range = *args.at(0);
        std::string const& key = args.at(1)->get<std::string>();
        return std::all_of(
            obj_range.begin(),
            obj_range.end(),
            [&key](nlohmann::json const& obj) -> bool {
                if (obj.is_object() && obj.contains(key)) {
                    nlohmann::json const& v = obj[key];
                    if (v.is_boolean()) {
                        return v.get<bool>();
                    }
                    if (v.is_number()) {
                        return v.get<int>() != 0;
                    }
                    if (v.is_string()) {
                        return !v.get<std::string>().empty();
                    }
                    return !v.empty();
                }
                return false;
            });
    });

    env_->add_callback(
        "noneContains",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            // check if all arrays in arrays of arrays contain element
            nlohmann::json const& range_out = *args.at(0);
            nlohmann::json const& what = *args.at(1);
            return std::none_of(
                range_out.begin(),
                range_out.end(),
                [&what](nlohmann::json const& range_in) {
            return std::find(range_in.begin(), range_in.end(), what)
                   != range_in.end();
                });
        });

    env_->add_callback("includes", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json const& what = *args.at(1);
        return std::search(range.begin(), range.end(), what.begin(), what.end())
               != range.end();
    });

    env_->add_callback("chunk", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        int cn = args.at(1)->get<int>();
        nlohmann::json res = nlohmann::json::array({});
        std::size_t n = range.size();
        for (std::size_t i = 0; i < n; i += cn) {
            res.push_back(nlohmann::json::array());
            res.back().insert(
                res.back().end(),
                range.begin() + i,
                range.begin() + std::min(i + cn, n));
        }
        return res;
    });

    env_->add_callback(
        "collapse",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            nlohmann::json const& range = *args.at(0);
            nlohmann::json flat = nlohmann::json::array({});
            for (auto& el: range) {
                if (el.is_array()) {
                    flat.insert(flat.end(), el.begin(), el.end());
                } else {
                    flat.push_back(el);
                }
            }
            return flat;
        });

    env_->add_callback("count", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json const& el = *args.at(1);
        return std::count(range.begin(), range.end(), el);
    });

    env_->add_callback("diff", 2, [](inja::Arguments& args) -> nlohmann::json {
        // return subranges of range1 that are not in range2
        nlohmann::json const& range1 = *args.at(0);
        nlohmann::json const& range2 = *args.at(0);
        auto it = std::
            search(range1.begin(), range1.end(), range2.begin(), range2.end());
        if (it == range1.end()) {
            return range1;
        }
        nlohmann::json res = nlohmann::json::array({});
        res.insert(res.end(), range1.begin(), it);
        res.insert(res.end(), it + range2.size(), range1.end());
        return res;
    });

    env_->add_callback("keys", 1, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        nlohmann::json r = nlohmann::json::array({});
        if (m.is_object()) {
            // get keys from objects
            for (auto& el: m.items()) {
                r.push_back(el.key());
            }
        } else if (m.is_array()) {
            // get keys from an array of objects
            for (auto& v: m) {
                for (auto& el: v.items()) {
                    r.push_back(el.key());
                }
            }
        }
        return r;
    });

    env_->add_callback("values", 1, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        nlohmann::json r = nlohmann::json::array({});
        for (auto& el: m.items()) {
            r.push_back(el.value());
        }
        return r;
    });

    env_->add_callback("forget", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(2)->get<std::string>();
        nlohmann::json r = m;
        r.erase(k);
        return r;
    });

    env_->add_callback("getOr", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        nlohmann::json const& or_v = *args.at(2);
        if (m.contains(k)) {
            return m[k];
        }
        return or_v;
    });

    env_->add_callback("getIf", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        if (m.contains(k)) {
            return m[k];
        }
        return "";
    });

    env_->add_callback("groupBy", 2, [](inja::Arguments& args) -> nlohmann::json {
        // m is array of objs
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        std::vector<std::uint8_t> copied(m.size(), 0);
        nlohmann::json res = nlohmann::json::array({});
        for (std::size_t i = 0; i < m.size(); ++i) {
            if (copied[i] || !m[i].contains(k)) {
                copied[i] = 0x01;
                continue;
            }
            copied[i] = 0x01;
            std::string group_name = m[i][k].get<std::string>();
            res.push_back(nlohmann::json::array({}));
            res.back().push_back(m[i]);
            for (std::size_t j = i; j < m.size(); ++j) {
                if (copied[j]) {
                    continue;
                }
                if (m[j][k] == m[i][k]) {
                    res.back().push_back(m[j]);
                    copied[j] = 0x01;
                }
            }
        }
        return res;
    });

    env_->add_callback("has", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        return m.contains(k);
    });

    env_->add_callback("hasAny", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& m = *args.at(0);
        nlohmann::json const& keys = *args.at(1);
        for (auto& k: keys) {
            if (m.contains(k)) {
                return true;
            }
        }
        return false;
    });

    env_->add_callback("trim", 1, [](inja::Arguments& args) -> nlohmann::json {
        std::string_view str = args.at(0)->get<std::string_view>();
        auto p1 = str.find_first_not_of(" \n\r\t");
        if (p1 == std::string::npos) {
            p1 = 0;
        }
        auto p2 = str.find_last_not_of(" \n\r\t");
        if (p2 == std::string::npos) {
            p2 = str.size();
        } else {
            ++p2;
        }
        return str.substr(p1, p2 - p1);
    });

    env_->add_callback("trimAll", 1, [](inja::Arguments& args) -> nlohmann::json {
        // Trim and also remove \n\r\t, and consecutive whitespace
        std::string_view str = args.at(0)->get<std::string_view>();
        auto p1 = str.find_first_not_of(" \n\r\t");
        if (p1 == std::string::npos) {
            p1 = 0;
        }
        auto p2 = str.find_last_not_of(" \n\r\t");
        if (p2 == std::string::npos) {
            p2 = str.size();
        } else {
            ++p2;
        }
        std::string res;
        res.reserve(p2 - p1);
        for (std::size_t i = p1; i < p2; ++i) {
            if (str[i] == '\n' || str[i] == '\r' || str[i] == '\t') {
                continue;
            }
            if (str[i] == ' ' && i != 0 && str[i - 1] == ' ') {
                continue;
            }
            res.push_back(str[i]);
        }
        return res;
    });

    env_->add_callback(
        "startsWith",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            std::string_view str = args.at(0)->get<std::string_view>();
            std::string_view prefix = args.at(1)->get<std::string_view>();
            if (prefix.size() > str.size()) {
                return false;
            }
            return str.substr(0, prefix.size()) == prefix;
        });

    env_->add_callback(
        "removePrefix",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            std::string_view str = args.at(0)->get<std::string_view>();
            std::size_t prefix_size = args.at(1)->get<std::size_t>();
            if (prefix_size > str.size()) {
                return "";
            }
            return str.substr(prefix_size);
        });

    env_->add_callback("implode", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string key = args.at(1)->get<std::string>();
        std::string delim = args.at(2)->get<std::string>();
        if (range.empty()) {
            return "";
        }
        std::size_t i = 0;
        while (i < range.size() && !range[i].contains(key)) {
            ++i;
        }
        if (i == range.size()) {
            return "";
        }
        std::string res = range[i][key].get<std::string>();
        ++i;
        while (i < range.size()) {
            auto it = range[i].find(key);
            if (it != range[i].end()) {
                res += delim;
                res += it->get<std::string>();
            }
            ++i;
        }
        return res;
    });

    env_->add_callback(
        "intersect",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            nlohmann::json const& range1 = *args.at(0);
            nlohmann::json const& range2 = *args.at(0);
            nlohmann::json res = nlohmann::json::array({});
            for (auto& el: range1) {
                if (std::find(range2.begin(), range2.end(), el) != range2.end())
                {
                    res.push_back(el);
                }
            }
            return res;
        });

    env_->add_callback("join", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string delim = args.at(2)->get<std::string>();
        if (range.empty()) {
            return "";
        }
        std::string res = range[0].get<std::string>();
        for (std::size_t i = 1; i < range.size(); ++i) {
            res += delim;
            res += range[i].get<std::string>();
        }
        return res;
    });

    env_->add_callback("merge", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& obj = *args.at(0);
        nlohmann::json const& over = *args.at(1);
        nlohmann::json res = obj;
        for (auto& i: over.items()) {
            res[i.key()] = i.value();
        }
        return res;
    });

    env_->add_callback(
        "mergeRecursive",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            nlohmann::json const& obj = *args.at(0);
            nlohmann::json const& over = *args.at(1);
            nlohmann::json res = obj;
            for (auto& i: over.items()) {
                if (!res.contains(i.key())) {
                    res[i.key()] = i.value();
                } else if (!res[i.key()].is_array()) {
                    res[i.key()] = nlohmann::json::array(
                        { res[i.key()], i.value() });
                } else {
                    res[i.key()].push_back(i.value());
                }
            }
            return res;
        });

    env_->add_callback("pluck", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string key = args.at(1)->get<std::string>();
        nlohmann::json res = nlohmann::json::array({});
        for (auto const& el: range) {
            if (el.contains(key)) {
                res.push_back(el[key]);
            }
        }
        return res;
    });

    env_->add_callback("prepend", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json const& value = *args.at(1);
        nlohmann::json res = range;
        res.insert(res.begin(), value);
        return res;
    });

    env_->add_callback("reverse", 1, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json res = range;
        std::reverse(res.begin(), res.end());
        return res;
    });

    env_->add_callback("sortBy", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string key = args.at(1)->get<std::string>();
        nlohmann::json res = range;
        std::sort(
            res.begin(),
            res.end(),
            [&key](nlohmann::json const& a, nlohmann::json const& b) {
            const bool ak = a.contains(key);
            const bool bk = b.contains(key);
            if (!ak) {
                return bk;
            }
            if (!bk) {
                return false;
            } else {
                return a[key] < b[key];
            }
            });
        return res;
    });

    env_->add_callback("unique", 1, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json res = range;
        std::sort(res.begin(), res.end());
        auto last = std::unique(res.begin(), res.end());
        res.erase(last, res.end());
        return res;
    });

    env_->add_callback(
        "uniqueBriefs",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            nlohmann::json const& range = *args.at(0);
            nlohmann::json res = range;
            std::sort(res.begin(), res.end());
            auto last = std::unique(res.begin(), res.end());
            res.erase(last, res.end());
            last = std::
                remove_if(res.begin(), res.end(), [](nlohmann::json const& x) {
                    constexpr std::string_view doxy_overload_prefix
                        = "This is an overloaded member function, provided for "
                          "convenience";
                    auto sv = x.get<std::string_view>();
                    return sv.substr(0, doxy_overload_prefix.size())
                           == doxy_overload_prefix;
                });
            res.erase(last, res.end());
            return res;
        });

    env_->add_callback(
        "orderedUnique",
        1,
        [](inja::Arguments& args) -> nlohmann::json {
            // Get unique elements but don't get them out of order
            nlohmann::json const& range = *args.at(0);
            nlohmann::json res = range;
            std::sort(res.begin(), res.end());
            auto last = std::unique(res.begin(), res.end());
            res.erase(last, res.end());
            std::sort(
                res.begin(),
                res.end(),
                [&range](nlohmann::json const& a, nlohmann::json const& b) {
            return std::find(range.begin(), range.end(), a)
                   < std::find(range.begin(), range.end(), b);
                });
            return res;
        });

    env_->add_callback(
        "uniqueBy",
        2,
        [](inja::Arguments& args) -> nlohmann::json {
            // Return objects that are unique in the specified fields
            nlohmann::json const& range = *args.at(0);
            nlohmann::json fields = *args.at(1);
            if (fields.is_string()) {
                fields = nlohmann::json::array({ fields });
            }
            nlohmann::json res = range;
            std::sort(
                res.begin(),
                res.end(),
                [&fields](nlohmann::json const& a, nlohmann::json const& b) {
            for (auto const& f: fields) {
                auto fv = f.get<std::string>();
                if (a[fv] < b[fv]) {
                    return true;
                } else if (b[fv] < a[fv]) {
                    return false;
                }
            }
            return false;
                });
            auto last = std::unique(
                res.begin(),
                res.end(),
                [&fields](nlohmann::json const& a, nlohmann::json const& b) {
            for (auto const& f: fields) {
                auto fv = f.get<std::string>();
                if (a[fv] != b[fv]) {
                    return false;
                }
            }
            return true;
                });
            res.erase(last, res.end());
            return res;
        });

    env_->add_callback("where", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string const& key = args.at(1)->get<std::string>();
        nlohmann::json const& v = *args.at(2);
        nlohmann::json res = nlohmann::json::array({});
        for (auto& obj: range) {
            if (obj.contains(key) && obj[key] == v) {
                res.push_back(obj);
            }
        }
        return res;
    });

    env_->add_callback("whereIn", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string const& key = args.at(1)->get<std::string>();
        nlohmann::json const& values = *args.at(2);
        nlohmann::json res = nlohmann::json::array({});
        for (auto& obj: range) {
            if (obj.contains(key)
                && std::find(values.begin(), values.end(), obj[key])
                       != values.end())
            {
                res.push_back(obj);
            }
        }
        return res;
    });

    env_->add_callback("zip", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range1 = *args.at(0);
        nlohmann::json const& range2 = *args.at(1);
        nlohmann::json res = nlohmann::json::array({});
        auto it1 = range1.begin();
        auto it2 = range1.begin();
        while (it1 != range1.end() && it2 != range2.end()) {
            res[it1->get<std::string>()] = *it2;
        }
        return res;
    });

    env_->add_callback("dump", 1, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& j = *args.at(0);
        return j.dump(4);
    });

    env_->add_callback(
        "sourceUrl",
        1,
        [this](inja::Arguments& args) -> nlohmann::json {
            std::string loc = args.at(0)->get<std::string>();
            auto f = [&loc](node const& n) -> bool {
                if (n.is_file_or_dir()) {
                    std::string title;
                    if (n.get_kind() == kind::FILE
                        && n.get_parent()->get_kind() == kind::DIR)
                    {
                        title = n.get_parent()->get_name() + "/" + n.get_name();
                    } else {
                        title = n.get_name();
                    }
                    if (title == loc) {
                        return true;
                    }
                }
                return false;
            };
            std::shared_ptr<node> r = doxygen_.find_if(f);
            if (r) {
                return r->get_url();
            }
            return nlohmann::json::string_t{};
        });

    env_->add_callback(
        "refidBrief",
        1,
        [this](inja::Arguments& args) -> nlohmann::json {
            std::string refid = args.at(0)->get<std::string>();
            std::shared_ptr<node> r = doxygen_.find(refid);
            if (r) {
                if (!r->get_brief().empty()) {
                    return r->get_brief();
                }
                if (!r->get_qualified_name().empty()) {
                    auto n = doxygen_.find_if([&r](node const& n) -> bool {
                        return n.get_qualified_name() == r->get_qualified_name()
                               && !n.get_brief().empty();
                    });
                    if (n) {
                        return n->get_brief();
                    }
                }
            }
            return nlohmann::json::string_t{};
        });

    env_->add_void_callback("noop", 0, [](inja::Arguments& args) {});
    // env->set_trim_blocks(false);
    // env->set_lstrip_blocks(false);

    // These are the templates we will be using.
    // So we don't load other templates that will never get used!
    std::unordered_set<std::string> templatesToLoad = {
        config.template_index_classes,    config.template_index_examples,
        config.template_index_files,      config.template_index_groups,
        config.template_index_namespaces, config.template_index_related_pages,
        config.template_kind_class,       config.template_kind_example,
        config.template_kind_file,        config.template_kind_group,
        config.template_kind_dir,         config.template_kind_namespace,
        config.template_kind_page,        config.template_kind_union,
        config.template_kind_interface,   config.template_kind_struct
    };

    // This is a list of other templates found in the templates directory (if
    // supplied)
    std::unordered_map<std::string, std::string> otherTemplates;
    std::string includePrefix = "";

    if (templates_path.has_value()) {
        includePrefix = trimPath(*templates_path) + SEPARATOR;

        directoryIterator(includePrefix, [&](std::string const& file) {
            const auto name = basename(file);
            otherTemplates.insert(std::make_pair(name, file));
        });
    }

    spdlog::info("Using lookup template path: '{}'", includePrefix);

    // Recursive template loader with dependencies.
    // Thanks to C++17 we can use recursive lambdas.
    std::set<std::string> loaded;
    const std::function<void(std::string const&, bool)> loadDependency =
        [&](std::string const& name, bool const include) {
        // Check if this template has been loaded.
        if (loaded.find(name) != loaded.end()) {
            return;
        }

        // Find the template in the list of default templates
        // and in the list of provided templates via "--templates <path>"
        // argument.
        const auto oit = otherTemplates.find(name);
        const auto dit = default_templates.find(name);

        try {
            // Recursively load the dependencies but only if this
            // template is available in the list of default templates.
            //
            // This is useful if you have a custom template "meta.tmpl"
            // that is used by some other default template.
            //
            // Or you have a custom template "kind_class.tmpl" but uses custom
            // template "header" that is not provided and therefore should be
            // loaded from the list of default templates.
            //
            // We want to ensure that the default templates and custom templates
            // can coexist.
            if (dit != default_templates.end()) {
                for (const auto& dep: dit->second.dependencies) {
                    loadDependency(dep, true);
                }
            }

            // The template has been found in the provided template path (i.e.
            // "--templates <path>")
            if (oit != otherTemplates.end()) {
                spdlog::info(
                    "Parsing template: '{}' from file: '{}'",
                    name,
                    oit->second);

                // Parse the template.
                // The inja library will load all of the other templates
                // that are specified by {% include "<name>" %} in the tmpl
                // file. These includes are automatically resolved based on the
                // provided template path (i.e. "--templates <path>") thanks to
                // providing the templates path to the constructor of
                // inja::Environment
                auto tmpl = env_->parse_template(filename(oit->second));
                const auto it = templates_
                                    .insert(std::make_pair(
                                        stripTmplSuffix(name),
                                        std::make_unique<inja::Template>(
                                            std::move(tmpl))))
                                    .first;

                // Only include the dependencies.
                // This is needed if a default template is parsed via env->parse
                // and wants to include some other template. We need to let inja
                // know about that template before parsing it.
                if (include) {
                    env_->include_template(name, *it->second);
                    env_->include_template(includePrefix + name, *it->second);
                }

            } else if (dit != default_templates.end()) {
                spdlog::info("Parsing template: '{}' from default", name);

                // Parse the template from the list of default templates.
                // This won't do any automatic resolving of {% include "<name>"
                // %} and therefore we have to do env->include_template(<name>,
                // <ref>)
                auto tmpl = env_->parse(dit->second.src);
                const auto it = templates_
                                    .insert(std::make_pair(
                                        stripTmplSuffix(name),
                                        std::make_unique<inja::Template>(
                                            std::move(tmpl))))
                                    .first;

                // Same as above
                if (include) {
                    env_->include_template(name, *it->second);
                    env_->include_template(includePrefix + name, *it->second);
                }
            } else {
                throw EXCEPTION("No template provided for: '{}'", name);
            }

            // Remember that we have parsed this template.
            loaded.insert(name);
        }
        catch (std::exception& e) {
            throw EXCEPTION(
                "Failed to load template: '{}' error: {}",
                name,
                e.what());
        }
    };

    // Load all of the required templates specified by the config.
    for (auto const& name: templatesToLoad) {
        loadDependency(name, false);
    }

    // Load all of the other templates in the directory that were not loaded in
    // the loop above. Because of the custom function {{render("<name>", data)}}
    // provided in the template renderer, as an alternative to {% include <name>
    // %}, we have to load all of the other templates too!
    //
    // The render function will not automatically resolve the template by the
    // argument "<name>" so we have to ensure that the template is provided
    // upfront.
    //
    // This is different from the {% include "<name>" %} which does resolving
    // automatically.
    for (auto const& pair: otherTemplates) {
        auto const& name = pair.first;
        auto const& file = pair.second;

        // Check if this template has been already loaded.
        if (loaded.find(name) != loaded.end()) {
            continue;
        }

        try {
            spdlog::info("Parsing template: '{}' from file: '{}'", name, file);
            auto tmpl = env_->parse_template(name + ".tmpl");
            templates_.insert(std::make_pair(
                name,
                std::make_unique<inja::Template>(std::move(tmpl))));
        }
        catch (std::exception& e) {
            throw EXCEPTION(
                "Failed to load template: '{}' error: {}",
                name,
                e.what());
        }
    }
}

doxybook::renderer::~renderer() = default;

void
doxybook::renderer::render(
    std::string const& name,
    std::string const& path,
    nlohmann::json const& data) const {
    auto const it = templates_.find(stripTmplSuffix(name));
    if (it == templates_.end()) {
        throw EXCEPTION("Template {} not found", name);
    }

    auto const absPath = path::join(config_.output_dir, path);
    if (config_.debug_template_json) {
        std::ofstream dump(absPath + ".json");
        dump << data.dump(2);
    }

    std::fstream file(absPath, std::ios::out);
    if (!file) {
        throw EXCEPTION("Failed to open file for writing {}", absPath);
    }
    spdlog::info("Rendering {}", absPath);
    try {
        env_->render_to(file, *it->second, data);
    }
    catch (std::exception& e) {
        throw EXCEPTION("Render template '{}' error {}", name, e.what());
    }
}

std::string
doxybook::renderer::render(std::string const& name, nlohmann::json const& data)
    const {
    auto const it = templates_.find(stripTmplSuffix(name));
    if (it == templates_.end()) {
        throw EXCEPTION("Template {} not found", stripTmplSuffix(name));
    }

    std::stringstream ss;
    try {
        env_->render_to(ss, *it->second, data);
    }
    catch (std::exception& e) {
        throw EXCEPTION(
            "Failed to render template '{}' error {}",
            name,
            e.what());
    }
    return ss.str();
}
