//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/config.hpp>
#include <doxybook/doxygen.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/node.hpp>
#include <doxybook/path.hpp>
#include <doxybook/utils.hpp>
#include <doxybook/xml.hpp>
#include <spdlog/spdlog.h>
#include <cassert>
#include <set>
#include "tinyxml2/tinyxml2.h"

static bool
is_kind_allowed_language(std::string const& kind) {
    static std::set<std::string> values = {
        "namespace", "class",   "struct", "interface", "function", "concept",
        "variable",  "typedef", "enum",   "slot",      "signal",   "union",
    };
    return values.find(kind) != values.end();
}

static bool
is_kind_allowed_group(std::string const& kind) {
    return kind == "group";
}

static bool
is_kind_allowed_dirs(std::string const& kind) {
    return kind == "dir" || kind == "file";
}

static bool
is_kind_allowed_pages(std::string const& kind) {
    return kind == "page";
}

static bool
is_kind_allowed_examples(std::string const& kind) {
    return kind == "example";
}

doxybook::doxygen::doxygen(const class config& c)
    : config_(c)
    , index_(std::make_shared<node>("index")) {}

void
doxybook::doxygen::load(std::string const& input_dir) {
    // Remove entries from index which parent has been updated
    auto const cleanup = [](std::shared_ptr<doxybook::node> const& node) {
        auto it = node->children_.begin();
        while (it != node->children_.end()) {
            if (it->get()->parent_ != node.get()) {
                node->children_.erase(it++);
            } else {
                ++it;
            }
        }
    };

    // Load basic information about all nodes.
    // This includes refid, brief, and list of members.
    // This won't load detailed documentation or other data! (we will do that
    // later)
    auto const kindRefidMap = get_index_kinds(input_dir);

    auto load_filtered = [&](auto kind_filter, bool is_group_or_file) {
        for (auto const& pair: kindRefidMap) {
            if (!kind_filter(pair.first)) {
                continue;
            }
            try {
                auto found = cache_.find(pair.second);
                if (found == cache_.end()) {
                    index_->children_.push_back(node::parse(
                        cache_,
                        input_dir,
                        pair.second,
                        is_group_or_file,
                        config_.undocumented_macros));
                    auto child = index_->children_.back();
                    if (child->parent_ == nullptr) {
                        child->parent_ = index_.get();
                    }
                    if (child->refid_ == "indexpage") {
                        child->refid_ = config_.main_page_name;
                    }
                }
            }
            catch (std::exception& e) {
                spdlog::warn(
                    "Failed to parse member {} error: {}",
                    pair.second,
                    e.what());
            }
        }
    };

    // Then load basic information from all other nodes.
    load_filtered(is_kind_allowed_language, false);
    cleanup(index_);
    // Next, load all groups
    load_filtered(is_kind_allowed_group, true);
    cleanup(index_);
    // Next, load all directories and files
    load_filtered(is_kind_allowed_dirs, true);
    cleanup(index_);
    // Next, pages
    load_filtered(is_kind_allowed_pages, true);
    cleanup(index_);
    // Lastly, examples (we don't need to sort these ones)
    load_filtered(is_kind_allowed_examples, true);

    get_index_cache(cache_, index_);

    // Append concepts to their namespaces
    // concepts are compound elements, but we want to render it
    // as a type

    // Fix concept parents
    //    for (auto const& pair: kindRefidMap) {
    //        if (pair.first != "concept") {
    //            continue;
    //        }
    //        try {
    //            auto found = cache_.find(pair.second);
    //            if (found == cache_.end()) {
    //                index_->children_.push_back(node::parse(
    //                    cache_,
    //                    input_dir,
    //                    pair.second,
    //                    is_group_or_file,
    //                    config_.undocumented_macros));
    //                auto child = index_->children_.back();
    //                if (child->parent_ == nullptr) {
    //                    child->parent_ = index_.get();
    //                }
    //                if (child->refid_ == "indexpage") {
    //                    child->refid_ = config_.main_page_name;
    //                }
    //            }
    //        }
    //        catch (std::exception& e) {
    //            spdlog::warn(
    //                "Failed to parse member {} error: {}",
    //                pair.second,
    //                e.what());
    //        }
    //    }

    // Update group pointers
    update_group_pointers(index_);
}

void
doxybook::doxygen::update_group_pointers(
    std::shared_ptr<doxybook::node> const& node) {
    if (node->kind_ == kind::MODULE) {
        for (auto const& child: node->children_) {
            child->group_ = node.get();
        }
    }

    for (auto const& child: node->children_) {
        if (child->kind_ == kind::MODULE) {
            update_group_pointers(child);
        }
    }
}

void
doxybook::doxygen::finalize(
    text_printer const& plain_printer,
    text_printer const& markdown_printer) {
    finalize_recursively(plain_printer, markdown_printer, index_);
    // adjust concept parents
    for (auto& p: cache_) {
        std::string const& refid = p.first;
        std::shared_ptr<node>& node = p.second;
        if (node->kind_ != kind::CONCEPT) {
            continue;
        }
        // look for parent namespace
        std::string_view namesv(node->name_);
        std::size_t nsp = namesv.rfind("::");
        if (nsp == std::string_view::npos) {
            continue;
        }
        std::string_view ns = namesv.substr(0, nsp);
        std::shared_ptr<doxybook::node> parent;
        for (auto& p2: cache_) {
            if (p2.second->kind_ != kind::NAMESPACE) {
                continue;
            }
            if (p2.second->name_ == ns) {
                parent = p2.second;
                break;
            }
        }
        node->parent_ = parent.get();
        node->parent_->children_.push_back(node);
        // adjust name based on parent namespace
        node->name_ = namesv.substr(nsp + 2);
        node->title_ = std::string_view(node->title_).substr(nsp + 2);
        node->anchor_ = node::anchorMaker(config_, *node);
        node->url_ = node::urlMaker(config_, *node);
        if (config_.link_lowercase) {
            node->url_ = utils::to_lower(node->url_);
        }

        // look for group using heuristics
        // 1st heuristic: look for trait for the same concept
        std::string_view unqualified_name(node->name_);
        auto lp = unqualified_name.rfind("::");
        if (lp != std::string_view::npos) {
            unqualified_name = unqualified_name.substr(lp + 2);
        }
        std::map<doxybook::node*, int> frequency;
        doxybook::node* equivalent_trait_group = nullptr;
        for (auto& p2: parent->children_) {
            if (!p2->group_) {
                continue;
            }
            if (p2->kind_ != kind::STRUCT && p2->kind_ != kind::CLASS
                && p2->kind_ != kind::VARIABLE && p2->kind_ != kind::USING
                && p2->kind_ != kind::CONCEPT)
            {
                continue;
            }
            std::string_view cname(p2->name_);
            if (cname.substr(0, 3) != "is_" && cname.substr(0, 4) != "has_"
                && cname.substr(cname.size() - 2, 2) != "_t"
                && cname.substr(cname.size() - 2, 2) != "_v"
                && cname.substr(cname.size() - 3, 3) != "_for"
                && p2->kind_ != kind::CONCEPT)
            {
                continue;
            }
            frequency[p2->group_]++;
            if (cname.substr(0, 3) == "is_") {
                cname.remove_prefix(3);
            } else if (cname.substr(0, 4) == "has_") {
                cname.remove_prefix(4);
            }
            if (cname.substr(cname.size() - 2, 2) == "_t") {
                cname.remove_suffix(2);
            } else if (cname.substr(cname.size() - 2, 2) == "_v") {
                cname.remove_suffix(2);
            }
            if (cname == unqualified_name && p2->group_) {
                equivalent_trait_group = p2->group_;
                break;
            }
        }
        if (equivalent_trait_group) {
            node->group_ = equivalent_trait_group;
            node->group_->children_.push_back(node);
            continue;
        }

        // 2nd heuristic: look for symbols defined in the same file
        doxybook::node* same_file_group = nullptr;
        if (!parent->xml_path_.empty()) {
            std::string concept_location;
            {
                xml doc(p.second->xml_path_);
                auto root = parent->assert_child(doc, "doxygen");
                auto compounddef = parent->assert_child(root, "compounddef");
                auto location = compounddef.first_child_element("location");
                concept_location = location.get_attr("file", "");
            }

            xml doc(parent->xml_path_);
            auto root = parent->assert_child(doc, "doxygen");
            auto compounddef = parent->assert_child(root, "compounddef");
            auto sectiondef = compounddef.first_child_element("sectiondef");
            while (sectiondef && !same_file_group) {
                auto memberdef = sectiondef.first_child_element("memberdef");
                while (memberdef && !same_file_group) {
                    std::string other_id = memberdef.get_attr("id", "");
                    auto it = cache_.find(other_id);
                    if (it != cache_.end() && it->second->group_) {
                        auto location = memberdef.first_child_element(
                            "location");
                        if (location) {
                            std::string other_location
                                = location.get_attr("file", "");
                            if (concept_location == other_location) {
                                same_file_group = it->second->group_;
                            }
                        }
                    }
                    memberdef = memberdef.next_sibling_element("memberdef");
                }
                sectiondef = sectiondef.next_sibling_element("sectiondef");
            }
        }
        if (same_file_group) {
            node->group_ = same_file_group;
            node->group_->children_.push_back(node);
            continue;
        }

        // 3st heuristic: find the most common group in that namespace
        // among the classes that look like traits
        doxybook::node* most_common_group = nullptr;
        int most_common_count = 0;
        for (auto [g, c]: frequency) {
            if (c > most_common_count) {
                most_common_count = c;
                most_common_group = g;
            }
        }
        if (most_common_group) {
            node->group_ = most_common_group;
            node->group_->children_.push_back(node);
        }
    }
}

void
doxybook::doxygen::finalize_recursively(
    text_printer const& plainPrinter,
    text_printer const& markdownPrinter,
    std::shared_ptr<doxybook::node> const& node) {
    for (auto const& child: node->children_) {
        child->finalize(config_, plainPrinter, markdownPrinter, cache_);
        finalize_recursively(plainPrinter, markdownPrinter, child);
    }
}

doxybook::doxygen::kind_refid_map
doxybook::doxygen::get_index_kinds(std::string const& input_dir) const {
    auto const indexPath = path::join(input_dir, "index.xml");
    xml xml(indexPath);

    std::unordered_multimap<std::string, std::string> map;

    auto root = xml.first_child_element("doxygenindex");
    if (!root) {
        throw EXCEPTION("Unable to find root element in file {}", indexPath);
    }

    auto compound = root.first_child_element("compound");
    if (!compound) {
        throw EXCEPTION("No <compound> element in file {}", indexPath);
    }
    while (compound) {
        try {
            auto const kind = compound.get_attr("kind");
            auto const refid = compound.get_attr("refid");
            assert(!refid.empty());
            map.insert(std::make_pair(kind, refid));
        }
        catch (std::exception& e) {
            spdlog::warn("compound error {}", e.what());
        }
        compound = compound.next_sibling_element("compound");
    }

    return map;
}

void
doxybook::doxygen::get_index_cache(
    node_cache_map& cache,
    std::shared_ptr<doxybook::node> const& parent) const {
    for (auto const& child: parent->children_) {
        cache.insert(std::make_pair(child->refid_, child));
        get_index_cache(cache, child);
    }
}

std::shared_ptr<doxybook::node>
doxybook::doxygen::find(std::string const& refid) const {
    try {
        return cache_.at(refid);
    }
    catch (std::exception& e) {
        (void) e;
        throw EXCEPTION("Failed to find node from cache by refid {}", refid);
    }
}

std::shared_ptr<doxybook::node>
doxybook::doxygen::find_if(std::function<bool(node const&)> f) const {
    auto it = std::find_if(cache_.begin(), cache_.end(), [&f](auto const& p) {
        return f(*p.second);
    });
    if (it != cache_.end()) {
        return it->second;
    }
    return nullptr;
}
