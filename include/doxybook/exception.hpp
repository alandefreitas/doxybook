//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_EXCEPTION_HPP
#define DOXYBOOK_EXCEPTION_HPP

#include <string>

namespace doxybook {
    /// Doxybook exceptions
    /**
     * This is a very basic class used to represent doxybook exceptions
     */
    class exception : public std::exception {
    public:
        /// Constructor
        exception() = default;

        /// Constructor
        explicit exception(std::string msg) : msg_(std::move(msg)) {}

        /// The error message
        char const*
        what() const throw() override {
            return msg_.c_str();
        }

    private:
        std::string msg_;
    };
} // namespace doxybook

#endif