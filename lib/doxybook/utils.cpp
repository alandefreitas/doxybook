//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifdef _WIN32
#    define NOMINMAX
#    include <Windows.h>
#else
#    include <sys/stat.h>
#endif

#include <doxybook/exception_utils.hpp>
#include <doxybook/utils.hpp>
#include <chrono>
#include <dirent.h>
#include <filesystem>
#include <locale>
#include <regex>
#include <sstream>
#include <unordered_map>

static std::string
replace_all(std::string str, std::string const& from, std::string const& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

std::string
doxybook::utils::normalize_language(std::string const& language) {
    auto res = language;
    std::transform(res.begin(), res.end(), res.begin(), tolower);
    static std::unordered_map<std::string, std::string> lang_map{
        {  "h",    "cpp"},
        {"c++",    "cpp"},
        { "cs", "csharp"},
        { "c#", "csharp"},
    };

    if (auto it = lang_map.find(res); it != lang_map.end()) {
        res = it->second;
    }
    return res;
}

std::string
doxybook::utils::replace_newline(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char ch) {
        if (ch == '\n') {
            return ' ';
        }
        return ch;
    });
    return str;
}

std::string
doxybook::utils::title(std::string str) {
    if (!str.empty()) {
        str[0] = ::toupper(str[0]);
    }
    return str;
}

extern std::string
doxybook::utils::to_lower(std::string str) {
    for (auto& c: str) {
        c = ::tolower(c);
    }
    return str;
}

std::string
doxybook::utils::safe_anchor_id(std::string str, bool replace_underscores) {
    str = replace_all(to_lower(std::move(str)), "::", "");
    str = replace_all(str, " ", "-");
    if (replace_underscores) {
        str = replace_all(str, "_", "-");
    }
    return str;
}

std::string
doxybook::utils::namespace_to_package(std::string str) {
    return replace_all(std::move(str), "::", ".");
}

std::string
doxybook::utils::date(std::string const& format) {
    auto const t = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), format.c_str(), std::localtime(&t));
    return mbstr;
}

std::string
doxybook::utils::strip_namespace(std::string const& str) {
    auto inside = 0;
    size_t count = 0;
    size_t offset = std::string::npos;
    for (auto const& c: str) {
        switch (c) {
        case '(':
        case '[':
        case '<':
        {
            inside++;
            break;
        }
        case ')':
        case ']':
        case '>':
        {
            inside--;
            break;
        }
        // case '.':
        case ':':
        {
            if (inside == 0) {
                offset = count + 1;
            }
        }
        default:
        {
            break;
        }
        }
        count++;
    }

    if (offset != std::string::npos) {
        return str.substr(offset);
    } else {
        return str;
    }
}

std::string
doxybook::utils::strip_anchor(std::string const& str) {
    static const std::regex ANCHOR_REGEX(R"(_[a-z0-9]{34,67}$)");
    std::stringstream ss;
    std::regex_replace(
        std::ostreambuf_iterator<char>(ss),
        str.begin(),
        str.end(),
        ANCHOR_REGEX,
        "");
    return ss.str();
}

std::string
doxybook::utils::escape(std::string str) {
    size_t new_size = 0;
    for (auto const& c: str) {
        switch (c) {
        case '<': // "<" (1) -> "&lt;" (4)
        case '>':
        { // ">" (1) -> "&gt;" (4)
            new_size += 4;
            break;
        }
        case '*': // "*" (1) -> "&#42;" (5)
        case '_':
        { // "_" (1) -> "&#95;" (5)
            new_size += 5;
            break;
        }
        default:
        {
            new_size += 1;
            break;
        }
        }
    }

    if (new_size == str.size()) {
        return str;
    }

    std::string ret;
    ret.reserve(new_size);
    for (auto const& c: str) {
        switch (c) {
        case '<':
        {
            ret += "&lt;";
            break;
        }
        case '>':
        {
            ret += "&gt;";
            break;
        }
        case '*':
        {
            ret += "&#42;";
            break;
        }
        case '_':
        {
            ret += "&#95;";
            break;
        }
        default:
        {
            ret += c;
            break;
        }
        }
    }

    return ret;
}

std::vector<std::string>
doxybook::utils::split(std::string const& str, std::string const& delim) {
    std::vector<std::string> tokens;
    size_t last = 0;
    auto pos = str.find(delim);
    while (pos != std::string::npos) {
        tokens.push_back(str.substr(last, pos));
        pos += delim.size();
        last = pos;
        pos = str.find(delim, pos);
    }
    if (last < str.size()) {
        tokens.push_back(str.substr(last));
    }
    return tokens;
}

void
doxybook::utils::create_directory(std::string const& path) {
    auto* dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return;
    }

#ifdef _WIN32
    if (!CreateDirectoryA(path.c_str(), NULL)
        && ERROR_ALREADY_EXISTS != GetLastError())
    {
        throw EXCEPTION(
            "Failed to create directory {} error {}",
            path,
            int(GetLastError()));
    }
#else
    std::filesystem::create_directories(
        std::filesystem::path(path).parent_path());
    auto const err = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (err != 0 && err != EEXIST) {
        throw EXCEPTION("Failed to create directory {} error {}", path, err);
    }
#endif
}
