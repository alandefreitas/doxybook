//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/xml_text_parser.hpp>
#include <spdlog/spdlog.h>
#include <functional>
#include <unordered_map>

enum doxybook::xml_text_parser::node::type
doxybook::xml_text_parser::str_to_type(std::string const& str)
{
    static std::unordered_map<std::string, enum node::type> kinds = {
        {                "para",                 node::type::PARA},
        {                "bold",                 node::type::BOLD},
        {            "emphasis",             node::type::EMPHASIS},
        {              "strike",               node::type::STRIKE},
        {              "hruler",               node::type::HRULER},
        {               "image",                node::type::IMAGE},
        {               "ulink",                node::type::ULINK},
        {                 "ref",                  node::type::REF},
        {            "listitem",             node::type::LISTITEM},
        {        "itemizedlist",         node::type::ITEMIZEDLIST},
        {        "variablelist",         node::type::VARIABLELIST},
        {         "orderedlist",          node::type::ORDEREDLIST},
        {        "varlistentry",         node::type::VARLISTENTRY},
        {                "term",                 node::type::TERM},
        {              "anchor",               node::type::ANCHOR},
        {          "simplesect",            node::type::SIMPLESEC},
        {      "computeroutput",       node::type::COMPUTEROUTPUT},
        {"parameterdescription", node::type::PARAMETERDESCRIPTION},
        {       "parametername",        node::type::PARAMETERNAME},
        {       "parameterlist",        node::type::PARAMETERLIST},
        {       "parameteritem",        node::type::PARAMETERITEM},
        {   "parameternamelist",    node::type::PARAMETERNAMELIST},
        {                "type",                 node::type::PARA},
        {          "argsstring",                 node::type::PARA},
        {              "defval",                 node::type::PARA},
        {            "declname",                 node::type::PARA},
        {            "xrefsect",             node::type::XREFSECT},
        {           "xreftitle",            node::type::XREFTITLE},
        {     "xrefdescription",      node::type::XREFDESCRIPTION},
        {         "initializer",                 node::type::PARA},
        {      "programlisting",       node::type::PROGRAMLISTING},
        {            "codeline",             node::type::CODELINE},
        {                  "sp",                   node::type::SP},
        {           "highlight",           node::type::HIGHTLIGHT},
        {             "defname",                 node::type::PARA},
        {               "title",                node::type::TITLE},
        {               "sect1",                node::type::SECT1},
        {               "sect2",                node::type::SECT2},
        {               "sect3",                node::type::SECT3},
        {               "sect4",                node::type::SECT4},
        {               "sect5",                node::type::SECT5},
        {               "sect6",                node::type::SECT6},
        {             "heading",                node::type::SECT1},
        {         "superscript",          node::type::SUPERSCRIPT},
        {   "nonbreakablespace",        node::type::NONBREAKSPACE},
        {               "table",                node::type::TABLE},
        {                 "row",            node::type::TABLE_ROW},
        {               "entry",           node::type::TABLE_CELL},
        {            "verbatim",             node::type::VERBATIM},
        {               "lsquo",                 node::type::SQUO},
        {           "linebreak",            node::type::LINEBREAK},
        {               "ndash",                node::type::NDASH},
        {               "mdash",                node::type::MDASH},
        {             "onlyfor",              node::type::ONLYFOR},
        {             "formula",              node::type::FORMULA},
        {          "blockquote",           node::type::BLOCKQUOTE},
    };

    auto const it = kinds.find(str);
    if (it == kinds.end()) {
        spdlog::warn(
            "Text tag \"{}\" not recognised, please contact the author",
            str);
        return node::type::UNKNOWN;
    }

    return it->second;
}

doxybook::xml_text_parser::node
doxybook::xml_text_parser::parse_paras(xml::element const& element) {
    node result;
    result.type = node::type::PARAS;
    std::vector<node*> tree = { &result };
    auto para = element.first_child_element();
    while (para) {
        traverse(tree, para.as_node());
        para = para.next_sibling_element();
    }
    return result;
}

doxybook::xml_text_parser::node
doxybook::xml_text_parser::parse_para(xml::element const& element) {
    node result;
    result.type = node::type::PARA;
    std::vector<node*> tree = { &result };
    traverse(tree, element.as_node());
    return result;
}

void
doxybook::xml_text_parser::traverse(
    std::vector<node*> tree,
    xml::node const& element) {
    if (!element) {
        return;
    }

    if (element.is_element()) {
        auto const& e = element.as_element();
        node node;
        node.type = str_to_type(e.get_name());
        tree.back()->children.push_back(std::move(node));
        auto const ptr = &tree.back()->children.back();
        tree.push_back(ptr);

        if (e.get_name() == "heading") {
            auto const level = std::stoi(e.get_attr("level", "1"));
            switch (level) {
            case 1:
                ptr->type = node::type::SECT1;
                break;
            case 2:
                ptr->type = node::type::SECT2;
                break;
            case 3:
                ptr->type = node::type::SECT3;
                break;
            case 4:
                ptr->type = node::type::SECT4;
                break;
            case 5:
                ptr->type = node::type::SECT5;
                break;
            case 6:
                ptr->type = node::type::SECT6;
                break;
            default:
                ptr->type = node::type::SECT1;
                break;
            }
        }

        switch (ptr->type) {
        case node::type::SIMPLESEC:
        {
            ptr->extra = e.get_attr("kind");
            break;
        }
        case node::type::PARAMETERLIST:
        {
            ptr->extra = e.get_attr("kind");
            break;
        }
        case node::type::REF:
        {
            ptr->extra = e.get_attr("refid");
            break;
        }
        case node::type::ULINK:
        {
            ptr->extra = e.get_attr("url");
            break;
        }
        case node::type::IMAGE:
        {
            ptr->extra = e.get_attr("name");
            break;
        }
        case node::type::TABLE:
        {
            ptr->extra = e.get_attr("cols", "");
            break;
        }
        case node::type::XREFSECT:
        {
            auto const id = e.get_attr("id");
            auto const pos = id.find('_');
            if (pos != std::string::npos) {
                ptr->extra = id.substr(0, pos);
            } else {
                ptr->extra = id;
            }
            break;
        }
        case node::type::PROGRAMLISTING:
        {
            ptr->extra = e.get_attr("filename", "");
            break;
        }
        default:
        {
            break;
        }
        }
    }

    if (element.has_text()) {
        if (!element.is_element()) {
            auto const text = element.get_text();
            if (!text.empty()) {
                node node;
                node.data = text;
                node.type = node::type::TEXT;
                tree.back()->children.push_back(node);
            }
        } else {
            auto const text = element.get_text();
        }
    }

    auto child = element.first_child();
    while (child) {
        traverse(tree, child);
        child = child.next_sibling();
    }

    if (element.is_element()) {
        tree.pop_back();
    }
}
