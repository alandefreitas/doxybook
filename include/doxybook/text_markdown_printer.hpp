//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_TEXT_MARKDOWN_PRINTER_HPP
#define DOXYBOOK_TEXT_MARKDOWN_PRINTER_HPP

#include <doxybook/text_printer.hpp>
#include <sstream>
namespace doxybook {
    /// Print xml nodes as markdown
    class text_markdown_printer : public text_printer {
    public:
        /// Constructor
        explicit text_markdown_printer(
            config const& config,
            std::string input_dir,
            doxygen const& doxygen)
            : text_printer(config, doxygen)
            , input_dir_(std::move(input_dir)) {}

        /// Print an xml node
        std::string
        print(xml_text_parser::node const& node, std::string const& language)
            const override;

    private:
        struct list_data {
            int counter{ 0 };
            bool ordered{ false };
        };

        struct print_data {
            std::stringstream ss;
            int indent{ 0 };
            std::list<list_data> lists;
            bool quote{ false };
            bool eol{ false };
            bool table_header{ false };
            bool in_computer_output{ false };
            bool valid_link{ false };
        };

        void
        print(
            print_data& data,
            xml_text_parser::node const* parent,
            xml_text_parser::node const* node,
            xml_text_parser::node const* previous,
            xml_text_parser::node const* next,
            std::string const& language) const;

        void
        program_listing(print_data& data, xml_text_parser::node const& node)
            const;

        std::string input_dir_;
    };
} // namespace doxybook

#endif