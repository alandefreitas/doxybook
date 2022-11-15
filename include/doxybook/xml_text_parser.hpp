//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_XML_TEXT_PARSER_HPP
#define DOXYBOOK_XML_TEXT_PARSER_HPP

#include <doxybook/xml.hpp>
#include <string>
#include <vector>

namespace doxybook {
    /// Parser for a doxygen xml file as an @ref xml document
    class xml_text_parser {
    public:
        class tag;
        using children_type = std::vector<std::unique_ptr<tag>>;

        /// A parsed xml node
        struct node {
            /// The node type
            enum class type
            {
                UNKNOWN = -1,
                TEXT = 0,
                PARA,
                PARAS,
                BOLD,
                EMPHASIS,
                STRIKE,
                HRULER,
                IMAGE,
                ULINK,
                REF,
                COMPUTEROUTPUT,
                LISTITEM,
                SIMPLESEC,
                ITEMIZEDLIST,
                VARIABLELIST,
                ORDEREDLIST,
                PARAMETERLIST,
                PARAMETERNAME,
                PARAMETERITEM,
                PARAMETERDESCRIPTION,
                PARAMETERNAMELIST,
                XREFSECT,
                XREFTITLE,
                XREFDESCRIPTION,
                PROGRAMLISTING,
                CODELINE,
                TERM,
                VARLISTENTRY,
                ANCHOR,
                SP,
                HIGHTLIGHT,
                SECT1,
                SECT2,
                SECT3,
                SECT4,
                SECT5,
                SECT6,
                TITLE,
                SUPERSCRIPT,
                NONBREAKSPACE,
                TABLE,
                TABLE_ROW,
                TABLE_CELL,
                VERBATIM,
                SQUO,
                NDASH,
                MDASH,
                LINEBREAK,
                ONLYFOR,
                FORMULA,
                BLOCKQUOTE,
            };

            /// The node type
            type type{ type::UNKNOWN };

            /// The child nodes
            std::vector<node> children;

            /// The node data as a string
            std::string data;

            /// Extra data
            std::string extra;
        };

        /// Parse elements
        static node
        parse_paras(xml::element const& element);

        /// Parse element
        static node
        parse_para(xml::element const& element);

        /// Convert string to node type
        static enum node::type
        str_to_type(std::string const& str);

    private:
        static void
        traverse(std::vector<node*> tree, xml::node const& element);
    };
} // namespace doxybook

#endif