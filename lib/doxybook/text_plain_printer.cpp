//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/text_plain_printer.hpp>
#include <doxybook/utils.hpp>
#include <sstream>

std::string
doxybook::text_plain_printer::print(
    xml_text_parser::node const& node,
    std::string const& language) const {
    std::stringstream ss;
    print(ss, node);
    auto str = ss.str();
    while (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }
    return str;
}

void
doxybook::text_plain_printer::print(
    std::stringstream& ss,
    xml_text_parser::node const& node) const {
    switch (node.type) {
    case xml_text_parser::node::type::TEXT:
    {
        ss << node.data;
        break;
    }
    default:
    {
        break;
    }
    }

    for (auto const& child: node.children) {
        print(ss, child);
    }

    switch (node.type) {
    case xml_text_parser::node::type::CODELINE:
    {
        ss << "\n";
        break;
    }
    case xml_text_parser::node::type::SP:
    {
        ss << " ";
        break;
    }
    default:
    {
        break;
    }
    }
}
