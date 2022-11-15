//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_GENERATOR_HPP
#define DOXYBOOK_GENERATOR_HPP

#include <doxybook/doxygen.hpp>
#include <doxybook/json_converter.hpp>
#include <doxybook/renderer.hpp>
#include <string>
#include <unordered_set>

namespace doxybook {
    /// A class that stores a @ref doxygen object and generates the markdown
    /// documentation
    /**
     * This is main class in this whole library. The cli executable basically
     * controls this generator.
     */
    class generator {
    public:
        /// A set of kinds we should use in an operation
        using filter_set = std::unordered_set<kind>;

        /// A section we should generate
        struct summary_section {
            /// The type of the section
            folder_category type;

            /// The kinds we should use
            filter_set filter;

            /// The kinds we should skip
            filter_set skip;
        };

        /// Constructor
        /**
         * The constructor requires the configuration and doxygen object which
         * should be previously constructed.
         *
         * @param config Configuration options
         * @param doxygen Doxygen files
         * @param json_converter Converter from json to markdown
         * @param templates_path An optional path with templates
         */
        explicit generator(
            config const& config,
            doxygen const& doxygen,
            json_converter const& json_converter,
            std::optional<std::string> const& templates_path);

        /// Generate the documentation for the specified doxygen kinds
        void
        print(filter_set const& filter, filter_set const& skip);

        /// Generate json for the specified doxygen kinds
        void
        json(filter_set const& filter, filter_set const& skip);

        /// Generate a manifest file
        void
        manifest();

        /// Generate the indexes for the specified doxygen kinds
        void
        print_index(
            folder_category type,
            filter_set const& filter,
            filter_set const& skip);

        /// Generate the summary for the specified doxygen sections
        void
        summary(
            std::string const& input_file,
            std::string const& output_file,
            std::vector<summary_section> const& sections);

    private:
        void
        print_recursively(
            node const& parent,
            filter_set const& filter,
            filter_set const& skip);

        nlohmann::json
        manifest_recursively(node const& node);

        void
        json_recursively(
            node const& parent,
            filter_set const& filter,
            filter_set const& skip);

        std::string
        kind_to_template_name(kind kind);

        nlohmann::json
        build_index_recursively(
            node const& node,
            filter_set const& filter,
            filter_set const& skip);

        void
        summary_recursive(
            std::stringstream& ss,
            int indent,
            std::string const& folderName,
            node const& node,
            filter_set const& filter,
            filter_set const& skip);

        bool
        should_include(node const& node);

        config const& config_;
        doxygen const& doxygen_;
        json_converter const& json_converter_;
        renderer renderer_;
    };
} // namespace doxybook

#endif