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
#include <doxybook/xml.hpp>
#include <spdlog/spdlog.h>
#include <cassert>
#include <set>
#include "tinyxml2/tinyxml2.h"

static bool
is_kind_allowed_language(std::string const& kind) {
    static std::set<std::string> values = {
        "namespace", "class", "struct", "interface", "function", "variable",
        "typedef",   "enum",  "slot",   "signal",    "union",
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
    // Remove entires from index which parent has been updated
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

    // Then load basic information from all other nodes.
    for (auto const& pair: kindRefidMap) {
        if (!is_kind_allowed_language(pair.first)) {
            continue;
        }
        try {
            auto found = cache_.find(pair.second);
            if (found == cache_.end()) {
                index_->children_.push_back(
                    node::parse(cache_, input_dir, pair.second, false));
                auto child = index_->children_.back();
                if (child->parent_ == nullptr) {
                    child->parent_ = index_.get();
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
    cleanup(index_);

    // Next, load all groups
    for (auto const& pair: kindRefidMap) {
        if (!is_kind_allowed_group(pair.first)) {
            continue;
        }
        try {
            auto found = cache_.find(pair.second);
            if (found == cache_.end()) {
                index_->children_.push_back(
                    node::parse(cache_, input_dir, pair.second, true));
                auto child = index_->children_.back();
                if (child->parent_ == nullptr) {
                    child->parent_ = index_.get();
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
    cleanup(index_);

    // Next, load all directories and files
    for (auto const& pair: kindRefidMap) {
        if (!is_kind_allowed_dirs(pair.first)) {
            continue;
        }
        try {
            auto found = cache_.find(pair.second);
            if (found == cache_.end()) {
                index_->children_.push_back(
                    node::parse(cache_, input_dir, pair.second, true));
                auto child = index_->children_.back();
                if (child->parent_ == nullptr) {
                    child->parent_ = index_.get();
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
    cleanup(index_);

    // Next, pages
    for (auto const& pair: kindRefidMap) {
        if (!is_kind_allowed_pages(pair.first)) {
            continue;
        }
        try {
            auto found = cache_.find(pair.second);
            if (found == cache_.end()) {
                index_->children_.push_back(
                    node::parse(cache_, input_dir, pair.second, true));
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
    cleanup(index_);

    // Lastly, examples (we don't need to sort these ones)
    for (auto const& pair: kindRefidMap) {
        if (!is_kind_allowed_examples(pair.first)) {
            continue;
        }
        try {
            auto found = cache_.find(pair.second);
            if (found == cache_.end()) {
                index_->children_.push_back(
                    node::parse(cache_, input_dir, pair.second, true));
                auto child = index_->children_.back();
                if (child->parent_ == nullptr) {
                    child->parent_ = index_.get();
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

    get_index_cache(cache_, index_);

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
