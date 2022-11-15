//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_PATH_HPP
#define DOXYBOOK_PATH_HPP

#include <algorithm>
#include <sstream>
#include <string>

namespace doxybook {
    namespace path {
        namespace detail {
            // Stream first to output
            inline void
            join(std::stringstream& ss, std::string const& first) {
                ss << first;
            }

            // Stream args to output as directory
            template <typename... Args>
            inline void
            join(
                std::stringstream& ss,
                std::string const& first,
                Args const&... args) {
#ifdef _WIN32
                ss << first << "\\";
#else
                ss << first << "/";
#endif
                detail::join(ss, args...);
            }
        } // namespace detail

        /// Join string arguments as a path
        template <typename... Args>
        inline std::string
        join(Args const&... args) {
            std::stringstream ss;
            detail::join(ss, args...);
            return ss.str();
        }

        /// Get the filename from a path string
        inline std::string
        filename(std::string const& path) {
            auto const a = path.find_last_of('/');
            auto const b = path.find_last_of('\\');
            if (a != std::string::npos && b != std::string::npos) {
                return path.substr(std::max<size_t>(a, b) + 1);
            } else if (a != std::string::npos) {
                return path.substr(a + 1);
            } else if (b != std::string::npos) {
                return path.substr(b + 1);
            } else {
                return path;
            }
        }
    }; // namespace path
} // namespace doxybook

#endif