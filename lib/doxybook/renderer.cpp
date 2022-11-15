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
        const auto arg = args.at(0)->get<std::string>();
        return arg.empty();
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
        const auto arg0 = args.at(0)->get<std::string>();
        const auto arg1 = args.at(1)->get<std::string>();
        nlohmann::json ret = nlohmann::json::array();
        for (auto& token: utils::split(arg0, arg1)) {
            ret.push_back(std::move(token));
        }
        return ret;
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

    env_->add_callback("includes", 2, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        nlohmann::json const& what = *args.at(1);
        return std::search(range.begin(), range.end(), what.begin(), what.end())
               != range.end();
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
        for (auto& el: m.items()) {
            r.push_back(el.key());
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
        // return subranges of range1 that are not in range2
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        nlohmann::json const& or_v = *args.at(2);
        if (m.contains(k)) {
            return m[k];
        }
        return or_v;
    });

    env_->add_callback("groupBy", 2, [](inja::Arguments& args) -> nlohmann::json {
        // m is array of objs
        nlohmann::json const& m = *args.at(0);
        std::string const k = args.at(1)->get<std::string>();
        std::vector<std::uint8_t> copied(m.size(), 0);
        nlohmann::json res = nlohmann::json::object({});
        for (std::size_t i = 0; i < m.size(); ++i) {
            if (copied[i] || !m[i].contains(k)) {
                copied[i] = 0x01;
                continue;
            }
            copied[i] = 0x01;
            std::string group_name = m[i][k].get<std::string>();
            res[group_name] = nlohmann::json::array({});
            res[group_name].push_back(m[i]);
            for (std::size_t j = i; j < m.size(); ++j) {
                if (copied[j]) {
                    continue;
                }
                if (m[j][k] == m[i][k]) {
                    res[group_name].push_back(m[j]);
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

    env_->add_callback("implode", 3, [](inja::Arguments& args) -> nlohmann::json {
        nlohmann::json const& range = *args.at(0);
        std::string key = args.at(1)->get<std::string>();
        std::string delim = args.at(2)->get<std::string>();
        if (range.empty()) {
            return "";
        }
        std::string res = range[0][key].get<std::string>();
        for (std::size_t i = 1; i < range.size(); ++i) {
            res += delim;
            res += range[i][key].get<std::string>();
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
