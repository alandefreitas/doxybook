//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_DOXYGEN_HPP
#define DOXYBOOK_DOXYGEN_HPP

#include <doxybook/node.hpp>
#include <string>
#include <unordered_map>

namespace doxybook {
    class text_printer;

    /// All the nodes representing the content of doxygen xml files
    class doxygen {
    public:
        /// Constructor
        explicit doxygen(config const& c);

        /// Destructor
        virtual ~doxygen() = default;

        /// Load an xml directory generated with doxygen
        void
        load(std::string const& input_dir);

        /// Finalize by printing the index with the printers
        void
        finalize(
            text_printer const& plain_printer,
            text_printer const& markdown_printer);

        /// Get root node representing the index
        node const&
        get_index() const {
            return *index_;
        }

        /// Find a node with the given ID
        std::shared_ptr<node>
        find(std::string const& refid) const;

        /// Get cache of nodes
        node_cache_map const&
        get_cache() const {
            return cache_;
        }

    private:
        // A map with the refids of each kind
        using kind_refid_map = std::unordered_multimap<std::string, std::string>;

        kind_refid_map
        get_index_kinds(std::string const& input_dir) const;

        void
        get_index_cache(
            node_cache_map& cache,
            std::shared_ptr<node> const& node) const;

        // Finalize given a certain node, which might have child nodes
        void
        finalize_recursively(
            text_printer const& plain_printer,
            text_printer const& markdown_printer,
            std::shared_ptr<node> const& node);

        void
        update_group_pointers(std::shared_ptr<node> const& node);

        config const& config_;

        // The root object that holds everything (index.xml)
        std::shared_ptr<node> index_;

        node_cache_map cache_;
    };
} // namespace doxybook

#endif