//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_UTILS_HPP
#define DOXYBOOK_UTILS_HPP

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace doxybook {
    namespace utils {
        namespace detail {
            inline void
            join(std::stringstream& ss, std::string const& first) {
                ss << first;
            }

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

        /// Escape a string
        extern std::string
        escape(std::string str);

        /// Capitalize string
        extern std::string
        title(std::string str);

        /// Convert string to lowercase
        extern std::string
        to_lower(std::string str);

        /// Create a safe anchor for a string
        /**
         * @param str string to convert
         * @param replace_underscores replaces underscores with hyphens
         * @return converted string
         */
        extern std::string
        safe_anchor_id(std::string str, bool replace_underscores);

        /// Convert a namespace string to a package string
        /**
         * This replaces all occurences of "::" with "."
         */
        extern std::string
        namespace_to_package(std::string str);

        /// Get current date as a string
        extern std::string
        date(std::string const& format);

        /// Strip namespace from symbol
        extern std::string
        strip_namespace(std::string const& format);

        /// Strip anchors from a string
        extern std::string
        strip_anchor(std::string const& str);

        /// Split string with the specified delimiter
        extern std::vector<std::string>
        split(std::string const& str, std::string const& delim);

        /// Create a directory
        extern void
        create_directory(std::string const& path);

        /// Normalize the language name
        extern std::string
        normalize_language(std::string const& language);

        /// Replace newlines with whitespaces
        extern std::string
        replace_newline(std::string str);
    } // namespace utils
} // namespace doxybook

#endif