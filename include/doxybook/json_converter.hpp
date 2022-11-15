//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_JSON_CONVERTER_HPP
#define DOXYBOOK_JSON_CONVERTER_HPP

#include <doxybook/config.hpp>
#include <doxybook/node.hpp>
#include <doxybook/text_printer.hpp>
#include <nlohmann/json.hpp>

namespace doxybook {
    /// Convert elements to json so they can be rendered with inja
    class json_converter {
    public:
        /// Constructor
        explicit json_converter(
            config const& config,
            doxygen const& doxygen,
            text_printer const& plainPrinter,
            text_printer const& markdownPrinter);


        /// Convert a vector of strings to a json array
        nlohmann::json
        convert(std::vector<std::string> const& vec) const;

        /// Convert a class_reference to json
        nlohmann::json
        convert(node::class_reference const& class_) const;

        /// Convert a vector of class references to json
        nlohmann::json
        convert(std::vector<node::class_reference> const& classes) const;

        /// Convert a source location to json
        nlohmann::json
        convert(node::source_location const& location) const;

        /// Convert a doxygen param to json
        nlohmann::json
        convert(node::param const& param) const;

        /// Convert a parameter list item to json
        nlohmann::json
        convert(node::parameter_list_item const& item) const;

        /// Convert a parameter list to json
        nlohmann::json
        convert(std::vector<node::parameter_list_item> const& item) const;

        /// Convert a doxygen node to json
        nlohmann::json
        convert(node const& node) const;

        /// Convert a doxygen node data to json
        nlohmann::json
        convert(node const& node, node::data const& data) const;

        /// Convert a doxygen node to json
        nlohmann::json
        get_as_json(node const& node) const;

    private:
        config const& config_;
        doxygen const& doxygen_;
        text_printer const& plain_printer_;
        text_printer const& markdown_printer_;
    };
} // namespace doxybook

#endif