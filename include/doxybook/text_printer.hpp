//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_TEXT_PRINTER_HPP
#define DOXYBOOK_TEXT_PRINTER_HPP

#include <doxybook/config.hpp>
#include <doxybook/node.hpp>
#include <doxybook/xml_text_parser.hpp>
#include <string>

namespace doxybook {
    class doxygen;

    /// An abstract text printer
    class text_printer {
    public:
        /// Constructor
        explicit text_printer(config const& config, doxygen const& doxygen)
            : config_(config)
            , doxygen_(doxygen) {}

        /// Destructor
        virtual ~text_printer() = default;

        /// Convert an element to text
        virtual std::string
        print(
            xml_text_parser::node const& node,
            std::string const& language = "cpp") const
            = 0;

    protected:
        config const& config_;
        doxygen const& doxygen_;
    };
} // namespace doxybook


#endif