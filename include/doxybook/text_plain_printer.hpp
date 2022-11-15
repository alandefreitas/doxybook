//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_TEXT_PLAIN_PRINTER_HPP
#define DOXYBOOK_TEXT_PLAIN_PRINTER_HPP

#include <doxybook/text_printer.hpp>

namespace doxybook {
    /// Print elements as plain text
    class text_plain_printer : public text_printer {
    public:
        /// Constructor
        explicit text_plain_printer(config const& config, doxygen const& doxygen)
            : text_printer(config, doxygen) {}

        /// Print an element as plain text
        std::string
        print(xml_text_parser::node const& node, std::string const& language)
            const override;

    private:
        void
        print(std::stringstream& ss, xml_text_parser::node const& node) const;
    };
} // namespace doxybook

#endif