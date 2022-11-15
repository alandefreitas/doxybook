//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_EXCEPTION_UTILS_HPP
#define DOXYBOOK_EXCEPTION_UTILS_HPP

#include <doxybook/exception.hpp>
#include <doxybook/path.hpp>
#include <fmt/format.h>

#define __FILENAME__ doxybook::path::filename(__FILE__)

#define EXCEPTION(MSG, ...)                                        \
    doxybook::exception(                                           \
        fmt::format("Exception at {}:{} ", __FILENAME__, __LINE__) \
        + fmt::format(MSG, ##__VA_ARGS__))

#define WARNING(MSG, ...)                                        \
    doxybook::spdlog::warn(                                      \
        fmt::format("Warning at {}:{} ", __FILENAME__, __LINE__) \
        + fmt::format(MSG, ##__VA_ARGS__))

#endif