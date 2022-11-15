//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/doxygen.hpp>
#include <doxybook/text_markdown_printer.hpp>
#include <doxybook/utils.hpp>
#include <fstream>
#include <sstream>

std::string
doxybook::text_markdown_printer::print(
    xml_text_parser::node const& node,
    std::string const& language) const {
    print_data data;
    print(data, nullptr, &node, nullptr, nullptr, language);
    auto str = data.ss.str();
    while (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }
    return str;
}

void
doxybook::text_markdown_printer::print(
    print_data& data,
    xml_text_parser::node const* parent,
    xml_text_parser::node const* node,
    xml_text_parser::node const* previous,
    xml_text_parser::node const* next,
    std::string const& language) const {
    auto newline = [&] {
        data.ss << "\n";
        if (data.quote) {
            data.ss << "> ";
        }
    };

    switch (node->type) {
    case xml_text_parser::node::type::TEXT:
    {
        if (config_.link_and_inline_code_as_html && data.in_computer_output) {
            data.ss << utils::escape(node->data);
        } else {
            data.ss << node->data;
        }
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT1:
    {
        newline();
        data.ss << "# ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT2:
    {
        newline();
        data.ss << "## ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT3:
    {
        newline();
        data.ss << "### ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT4:
    {
        newline();
        data.ss << "#### ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT5:
    {
        newline();
        data.ss << "##### ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::SECT6:
    {
        newline();
        data.ss << "###### ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::BOLD:
    {
        data.ss << "**";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::EMPHASIS:
    {
        data.ss << "_";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::STRIKE:
    {
        data.ss << "~~";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::VARIABLELIST:
    case xml_text_parser::node::type::ORDEREDLIST:
    case xml_text_parser::node::type::ITEMIZEDLIST:
    {
        if (data.lists.empty()) {
            newline();
        }
        newline();
        data.eol = true;
        data.lists.push_back(
            { 0, node->type == xml_text_parser::node::type::ORDEREDLIST });
        break;
    }
    case xml_text_parser::node::type::LISTITEM:
    {
        if (data.lists.size() > 1) {
            data.ss << std::string((data.lists.size() - 1) * 4, ' ');
        }
        data.lists.back().counter++;
        if (data.lists.back().ordered && data.lists.size() == 1) {
            data.ss << data.lists.back().counter << ". ";
        } else {
            data.ss << "* ";
        }
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::ULINK:
    {
        if (config_.link_and_inline_code_as_html) {
            if (!node->extra.empty()) {
                data.ss << "<a href=\"" << node->extra << "\">";
                data.valid_link = true;
            }
        } else {
            data.ss << "[";
        }
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::REF:
    {
        if (config_.link_and_inline_code_as_html) {
            auto const found = doxygen_.get_cache().find(node->extra);
            if (found != doxygen_.get_cache().end()
                && !found->second->get_url().empty())
            {
                data.ss << "<a href=\"" << found->second->get_url() << "\">";
                data.valid_link = true;
            }
        } else {
            data.ss << "[";
        }
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::IMAGE:
    {
        auto const prefix = config_.base_url + config_.images_folder;
        data.ss << "![" << node->extra << "](" << prefix
                << (prefix.empty() ? "" : "/") << node->extra << ")";
        data.eol = false;
        if (config_.copy_images) {
            std::ifstream
                src(utils::join(input_dir_, node->extra), std::ios::binary);
            if (src && config_.use_folders && !config_.images_folder.empty()) {
                std::ofstream
                    dst(utils::join(
                            config_.output_dir,
                            config_.images_folder,
                            node->extra),
                        std::ios::binary);
                if (dst) {
                    dst << src.rdbuf();
                }
            } else if (src) {
                std::ofstream
                    dst(utils::join(config_.output_dir, node->extra),
                        std::ios::binary);
                if (dst) {
                    dst << src.rdbuf();
                }
            }
        }
        break;
    }
    case xml_text_parser::node::type::COMPUTEROUTPUT:
    {
        if (config_.link_and_inline_code_as_html) {
            data.ss << "<code>";
        } else {
            data.ss << "`";
        }
        data.in_computer_output = true;
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::PROGRAMLISTING:
    {
        if (node->extra.empty()) {
            newline();
            newline();
            data.ss << "```" << language;
            newline();
        } else {
            auto i = node->extra.find_last_of('.');
            if (i != std::string::npos) {
                data.ss << "```"
                        << utils::normalize_language(node->extra.substr(i + 1));
                newline();
                newline();
            }
        }
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::VERBATIM:
    {
        newline();
        newline();
        data.ss << "```";
        newline();
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::BLOCKQUOTE:
    {
        newline();
        data.quote = true;
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::SP:
    {
        data.ss << " ";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::HRULER:
    {
        newline();
        newline();
        data.ss << "------------------";
        newline();
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::VARLISTENTRY:
    {
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::SUPERSCRIPT:
    {
        data.ss << "<sup>";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::NONBREAKSPACE:
    {
        data.ss << "&nbsp;";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::TABLE:
    {
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::TABLE_ROW:
    {
        data.ss << "|";
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::TABLE_CELL:
    {
        data.ss << " ";
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::SQUO:
    {
        data.ss << "\"";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::NDASH:
    {
        data.ss << "&ndash;";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::MDASH:
    {
        data.ss << "&mdash;";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::LINEBREAK:
    {
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::ONLYFOR:
    {
        data.ss << "(";
        data.eol = false;
        break;
    }
    default:
    {
        break;
    }
    }

    switch (node->type) {
    case xml_text_parser::node::type::PROGRAMLISTING:
    {
        program_listing(data, *node);
        break;
    }
    case xml_text_parser::node::type::FORMULA:
    {
        if (node->children.empty()) {
            break;
        }
        auto const& child = node->children.front();
        auto const& formula = child.data;
        if (formula.empty()) {
            break;
        }
        if (formula[0] == '$' && formula.size() >= 3) {
            data.ss << config_.formulaInlineStart;
            data.ss << formula.substr(1, formula.size() - 2);
            data.ss << config_.formulaInlineEnd;
        } else if (formula.find("\\[") == 0 && formula.size() >= 5) {
            data.ss << config_.formulaBlockStart;
            data.ss << formula.substr(2, formula.size() - 4);
            data.ss << config_.formulaBlockEnd;
        }
        break;
    }
    default:
    {
        for (size_t i = 0; i < node->children.size(); i++) {
            auto const childNext = i + 1 < node->children.size() ?
                                       &node->children[i + 1] :
                                       nullptr;
            auto const childPrevious = i > 0 ? &node->children[i - 1] : nullptr;
            print(
                data,
                node,
                &node->children[i],
                childPrevious,
                childNext,
                language);
        }
    }
    }

    switch (node->type) {
    case xml_text_parser::node::type::TITLE:
    {
        newline();
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::BOLD:
    {
        data.ss << "**";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::EMPHASIS:
    {
        data.ss << "_";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::STRIKE:
    {
        data.ss << "~~";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::ULINK:
    {
        if (config_.link_and_inline_code_as_html) {
            if (data.valid_link) {
                data.ss << "</a>";
            }
        } else {
            data.ss << "]";
            if (!node->extra.empty()) {
                data.ss << "(" << node->extra << ")";
            }
        }
        data.valid_link = false;
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::REF:
    {
        if (config_.link_and_inline_code_as_html) {
            if (data.valid_link) {
                data.ss << "</a>";
            }
        } else {
            data.ss << "]";
            auto const found = doxygen_.get_cache().find(node->extra);
            if (found != doxygen_.get_cache().end()) {
                data.ss << "(" << found->second->get_url() << ")";
            }
        }
        data.valid_link = false;
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::BLOCKQUOTE:
    {
        data.quote = false;
        newline();
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::PARA:
    {
        if (parent && parent->type == xml_text_parser::node::type::TABLE_CELL) {
            break;
        }
        if (parent && parent->type == xml_text_parser::node::type::LISTITEM) {
            if (!data.eol) {
                newline();
                data.eol = true;
            }
        } else {
            if (!data.eol) {
                newline();
                newline();
                data.eol = true;
            }
        }
        break;
    }
    case xml_text_parser::node::type::COMPUTEROUTPUT:
    {
        if (config_.link_and_inline_code_as_html) {
            data.ss << "</code>";
        } else {
            data.ss << "`";
        }
        data.in_computer_output = false;
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::ITEMIZEDLIST:
    case xml_text_parser::node::type::VARIABLELIST:
    case xml_text_parser::node::type::ORDEREDLIST:
    {
        data.lists.pop_back();
        if (data.lists.empty()) {
            newline();
        }
        break;
    }
    case xml_text_parser::node::type::LISTITEM:
    {
        break;
    }
    case xml_text_parser::node::type::CODELINE:
    {
        newline();
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::PROGRAMLISTING:
    {
        data.ss << "```";
        newline();
        newline();
        if (!node->extra.empty() && node->extra.find_last_of('.') != 0) {
            // If it's not only the extension name, output the filename
            data.ss << "_Filename: " << node->extra << "_";
            newline();
            newline();
        }
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::VERBATIM:
    {
        data.ss << "```";
        newline();
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::VARLISTENTRY:
    {
        newline();
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::SUPERSCRIPT:
    {
        data.ss << "</sup>";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::TABLE:
    {
        newline();
        newline();
        data.eol = true;
        data.table_header = false;
        break;
    }
    case xml_text_parser::node::type::TABLE_ROW:
    {
        if (!data.table_header) {
            newline();
            data.ss << "| ";
            for (size_t i = 0; i < node->children.size(); i++) {
                data.ss << " -------- |";
            }
            data.table_header = true;
        }
        newline();
        data.eol = true;
        break;
    }
    case xml_text_parser::node::type::TABLE_CELL:
    {
        data.ss << " |";
        data.eol = false;
        break;
    }
    case xml_text_parser::node::type::ONLYFOR:
    {
        data.ss << ")";
        data.eol = false;
        break;
    }
    default:
    {
        break;
    }
    }
}

void
doxybook::text_markdown_printer::program_listing(
    print_data& data,
    xml_text_parser::node const& node) const {
    switch (node.type) {
    case xml_text_parser::node::type::TEXT:
    {
        data.ss << node.data;
        break;
    }
    default:
    {
        break;
    }
    }

    auto newline = [&] {
        data.ss << "\n";
        if (data.quote) {
            data.ss << ">> ";
        }
    };

    for (auto const& child: node.children) {
        program_listing(data, child);
    }

    switch (node.type) {
    case xml_text_parser::node::type::CODELINE:
    {
        newline();
        break;
    }
    case xml_text_parser::node::type::SP:
    {
        data.ss << " ";
        break;
    }
    default:
    {
        break;
    }
    }
}
