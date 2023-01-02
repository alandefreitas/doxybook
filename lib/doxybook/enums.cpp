//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/config.hpp>
#include <doxybook/enums.hpp>
#include <doxybook/exception_utils.hpp>
#include <unordered_map>

using kind_str_pair = std::pair<std::string, doxybook::kind>;
using type_str_pair = std::pair<std::string, doxybook::type>;
using virtual_str_pair = std::pair<std::string, doxybook::virtual_category>;
using visibility_str_pair = std::pair<std::string, doxybook::visibility>;
using folder_category_str_pair = std::
    pair<std::string, doxybook::folder_category>;

static const std::vector<kind_str_pair> KIND_STRS = {
    {        "class",doxybook::kind::CLASS                     },
    {    "namespace", doxybook::kind::NAMESPACE},
    {       "struct",    doxybook::kind::STRUCT},
    {    "interface", doxybook::kind::INTERFACE},
    {     "function",  doxybook::kind::FUNCTION},
    {     "variable",  doxybook::kind::VARIABLE},
    {      "concept",   doxybook::kind::CONCEPT},
    {      "typedef",   doxybook::kind::TYPEDEF},
    {        "using",     doxybook::kind::USING},
    {         "enum",      doxybook::kind::ENUM},
    {        "union",     doxybook::kind::UNION},
    {    "enumvalue", doxybook::kind::ENUMVALUE},
    {          "dir",       doxybook::kind::DIR},
    {         "file",      doxybook::kind::FILE},
    {        "group",    doxybook::kind::MODULE},
    {       "friend",    doxybook::kind::FRIEND},
    {         "page",      doxybook::kind::PAGE},
    {      "example",   doxybook::kind::EXAMPLE},
    {       "signal",    doxybook::kind::SIGNAL},
    {         "slot",      doxybook::kind::SLOT},
    {     "property",  doxybook::kind::PROPERTY},
    {        "event",     doxybook::kind::EVENT},
    {       "define",    doxybook::kind::DEFINE},
    {         "enum",  doxybook::kind::JAVAENUM}, // only for enum->string conversion
    {"enum constant",
     doxybook::kind::JAVAENUMCONSTANT          }  // only for enum->string conversion
};

static const std::vector<type_str_pair> TYPE_STRS = {
    {       "attributes",        doxybook::type::ATTRIBUTES},
    {          "classes",           doxybook::type::CLASSES},
    {          "defines",           doxybook::type::DEFINES},
    {            "files",             doxybook::type::FILES},
    {             "dirs",              doxybook::type::DIRS},
    {          "friends",           doxybook::type::FRIENDS},
    {        "functions",         doxybook::type::FUNCTIONS},
    {          "modules",           doxybook::type::MODULES},
    {       "namespaces",        doxybook::type::NAMESPACES},
    {            "types",             doxybook::type::TYPES},
    {            "pages",             doxybook::type::PAGES},
    {         "examples",          doxybook::type::EXAMPLES},
    {          "signals",           doxybook::type::SIGNALS},
    {            "slots",             doxybook::type::SLOTS},
    {           "events",            doxybook::type::EVENTS},
    {       "properties",        doxybook::type::PROPERTIES},
    {"javaenumconstants", doxybook::type::JAVAENUMCONSTANTS}
};

static const std::vector<virtual_str_pair> VIRTUAL_STRS = {
    { "non-virtual",  doxybook::virtual_category::NON_VIRTUAL},
    {     "virtual",      doxybook::virtual_category::VIRTUAL},
    {        "pure", doxybook::virtual_category::PURE_VIRTUAL},
    {"pure-virtual", doxybook::virtual_category::PURE_VIRTUAL}
};

static const std::vector<visibility_str_pair> VISIBILITY_STRS = {
    {   "public",    doxybook::visibility::PUBLIC},
    {"protected", doxybook::visibility::PROTECTED},
    {  "private",   doxybook::visibility::PRIVATE},
    {  "package",   doxybook::visibility::PACKAGE}
};

static const std::vector<folder_category_str_pair> FOLDER_CATEGORY_STRS = {
    {   "modules",    doxybook::folder_category::MODULES},
    {"namespaces", doxybook::folder_category::NAMESPACES},
    {     "files",      doxybook::folder_category::FILES},
    {  "examples",   doxybook::folder_category::EXAMPLES},
    {   "classes",    doxybook::folder_category::CLASSES},
    {     "pages",      doxybook::folder_category::PAGES}
};

template <typename Enum>
struct EnumName {
    inline static auto const name = "unknown";
};

template <>
struct EnumName<doxybook::kind> {
    inline static auto const name = "Kind";
};
template <>
struct EnumName<doxybook::type> {
    inline static auto const name = "Type";
};
template <>
struct EnumName<doxybook::virtual_category> {
    inline static auto const name = "Virtual";
};
template <>
struct EnumName<doxybook::visibility> {
    inline static auto const name = "Visibility";
};
template <>
struct EnumName<doxybook::folder_category> {
    inline static auto const name = "FolderCategory";
};

template <typename Enum>
static Enum
to_enum(
    std::vector<std::pair<std::string, Enum>> const& pairs,
    std::string const& str) {
    auto const it = std::find_if(
        pairs.begin(),
        pairs.end(),
        [&](std::pair<std::string, Enum> const& pair) {
        return pair.first == str;
        });

    if (it == pairs.end()) {
        throw EXCEPTION(
            "String '{}' not recognised as a valid enum of '{}'",
            str,
            EnumName<Enum>::name);
    }

    return it->second;
}

template <typename Enum>
static std::string
from_enum(
    std::vector<std::pair<std::string, Enum>> const& pairs,
    const Enum value) {
    auto const it = std::find_if(
        pairs.begin(),
        pairs.end(),
        [&](std::pair<std::string, Enum> const& pair) {
        return pair.second == value;
        });

    if (it == pairs.end()) {
        throw EXCEPTION(
            "Enum '{}' of value '{}' not recognised please contact the author",
            EnumName<Enum>::name,
            int(value));
    }

    return it->first;
}

doxybook::kind
doxybook::to_enum_kind(std::string const& str) {
    return to_enum<kind>(KIND_STRS, str);
}

std::string
doxybook::to_str(const kind value) {
    return from_enum<kind>(KIND_STRS, value);
}

doxybook::virtual_category
doxybook::to_enum_virtual(std::string const& str) {
    return to_enum<virtual_category>(VIRTUAL_STRS, str);
}

std::string
doxybook::to_str(const virtual_category value) {
    return from_enum<virtual_category>(VIRTUAL_STRS, value);
}

doxybook::visibility
doxybook::to_enum_visibility(std::string const& str) {
    return to_enum<visibility>(VISIBILITY_STRS, str);
}

std::string
doxybook::to_str(const visibility value) {
    return from_enum<visibility>(VISIBILITY_STRS, value);
}

doxybook::type
doxybook::to_enum_type(std::string const& str) {
    return to_enum<type>(TYPE_STRS, str);
}

std::string
doxybook::to_str(const type value) {
    return from_enum<type>(TYPE_STRS, value);
}

doxybook::folder_category
doxybook::to_enum_folder_category(std::string const& str) {
    return to_enum<folder_category>(FOLDER_CATEGORY_STRS, str);
}

std::string
doxybook::to_str(const folder_category value) {
    return from_enum<folder_category>(FOLDER_CATEGORY_STRS, value);
}

doxybook::type
doxybook::kind_to_type(const doxybook::kind kind) {
    switch (kind) {
    case kind::DEFINE:
    {
        return type::DEFINES;
    }
    case kind::FRIEND:
    {
        return type::FRIENDS;
    }
    case kind::VARIABLE:
    {
        return type::ATTRIBUTES;
    }
    case kind::CONCEPT:
    {
        return type::ATTRIBUTES;
    }
    case kind::FUNCTION:
    {
        return type::FUNCTIONS;
    }
    case kind::ENUMVALUE:
    case kind::ENUM:
    case kind::USING:
    case kind::TYPEDEF:
    {
        return type::TYPES;
    }
    case kind::MODULE:
    {
        return type::MODULES;
    }
    case kind::NAMESPACE:
    {
        return type::NAMESPACES;
    }
    case kind::UNION:
    case kind::INTERFACE:
    case kind::STRUCT:
    case kind::CLASS:
    case kind::JAVAENUM:
    {
        return type::CLASSES;
    }
    case kind::FILE:
    {
        return type::FILES;
    }
    case kind::DIR:
    {
        return type::DIRS;
    }
    case kind::PAGE:
    {
        return type::PAGES;
    }
    case kind::EXAMPLE:
    {
        return type::EXAMPLES;
    }
    case kind::SIGNAL:
    {
        return type::SIGNALS;
    }
    case kind::SLOT:
    {
        return type::SLOTS;
    }
    case kind::EVENT:
    {
        return type::EVENTS;
    }
    case kind::PROPERTY:
    {
        return type::PROPERTIES;
    }
    default:
    {
        break;
    }
    }
    return type::NONE;
}

bool
doxybook::is_kind_structured(const kind kind) {
    switch (kind) {
    case doxybook::kind::CLASS:
    case doxybook::kind::NAMESPACE:
    case doxybook::kind::STRUCT:
    case doxybook::kind::UNION:
    case doxybook::kind::JAVAENUM:
    case doxybook::kind::INTERFACE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool
doxybook::is_kind_language(const kind kind) {
    switch (kind) {
    case doxybook::kind::DEFINE:
    case doxybook::kind::CLASS:
    case doxybook::kind::NAMESPACE:
    case doxybook::kind::STRUCT:
    case doxybook::kind::UNION:
    case doxybook::kind::INTERFACE:
    case doxybook::kind::ENUM:
    case doxybook::kind::FUNCTION:
    case doxybook::kind::TYPEDEF:
    case doxybook::kind::USING:
    case doxybook::kind::FRIEND:
    case doxybook::kind::VARIABLE:
    case doxybook::kind::CONCEPT:
    case doxybook::kind::SIGNAL:
    case doxybook::kind::SLOT:
    case doxybook::kind::PROPERTY:
    case doxybook::kind::EVENT:
    case doxybook::kind::JAVAENUM:
    case doxybook::kind::JAVAENUMCONSTANT:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool
doxybook::is_kind_file(const kind kind) {
    switch (kind) {
    case doxybook::kind::DIR:
    case doxybook::kind::FILE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

std::string
doxybook::type_folder_category_to_folder_name(
    config const& config,
    folder_category type) {
    if (!config.use_folders) {
        return "";
    }

    switch (type) {
    case folder_category::MODULES:
    {
        return config.folder_groups_name;
    }
    case folder_category::CLASSES:
    {
        return config.folder_classes_name;
    }
    case folder_category::NAMESPACES:
    {
        return config.folder_namespaces_name;
    }
    case folder_category::FILES:
    {
        return config.folder_files_name;
    }
    case folder_category::PAGES:
    {
        return config.folder_related_pages_name;
    }
    case folder_category::EXAMPLES:
    {
        return config.folder_examples_name;
    }
    default:
    {
        throw EXCEPTION("folder_category {} not recognised!", int(type));
    }
    }
}

std::string
doxybook::type_to_folder_name(config const& config, const type type) {
    if (!config.use_folders) {
        return "";
    }

    switch (type) {
    case type::MODULES:
    {
        return config.folder_groups_name;
    }
    case type::CLASSES:
    {
        return config.folder_classes_name;
    }
    case type::NAMESPACES:
    {
        return config.folder_namespaces_name;
    }
    case type::DIRS:
    case type::FILES:
    {
        return config.folder_files_name;
    }
    case type::PAGES:
    {
        return config.folder_related_pages_name;
    }
    case type::EXAMPLES:
    {
        return config.folder_examples_name;
    }
    default:
    {
        throw EXCEPTION(
            "Type {} not recognised please contant the author!",
            int(type));
    }
    }
}

std::string
doxybook::type_to_index_name(config const& config, const folder_category type) {
    switch (type) {
    case folder_category::MODULES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_groups_name + "/" + config.index_groups_name :
                   config.index_groups_name;
    }
    case folder_category::CLASSES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_classes_name + "/"
                       + config.index_classes_name :
                   config.index_classes_name;
    }
    case folder_category::NAMESPACES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_namespaces_name + "/"
                       + config.index_namespaces_name :
                   config.index_namespaces_name;
    }
    case folder_category::FILES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_files_name + "/" + config.index_files_name :
                   config.index_files_name;
    }
    case folder_category::PAGES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_related_pages_name + "/"
                       + config.index_related_pages_name :
                   config.index_related_pages_name;
    }
    case folder_category::EXAMPLES:
    {
        return config.index_in_folders && config.use_folders ?
                   config.folder_examples_name + "/"
                       + config.index_examples_name :
                   config.index_examples_name;
    }
    default:
    {
        throw EXCEPTION(
            "Type {} not recognised please contant the author!",
            int(type));
    }
    }
}

std::string
doxybook::type_to_index_template(
    config const& config,
    const folder_category type) {
    switch (type) {
    case folder_category::MODULES:
    {
        return config.template_index_groups;
    }
    case folder_category::CLASSES:
    {
        return config.template_index_classes;
    }
    case folder_category::NAMESPACES:
    {
        return config.template_index_namespaces;
    }
    case folder_category::FILES:
    {
        return config.template_index_files;
    }
    case folder_category::PAGES:
    {
        return config.template_index_related_pages;
    }
    case folder_category::EXAMPLES:
    {
        return config.template_index_examples;
    }
    default:
    {
        throw EXCEPTION(
            "Type {} not recognised please contant the author!",
            int(type));
    }
    }
}

std::string
doxybook::type_to_index_title(config const& config, const folder_category type) {
    switch (type) {
    case folder_category::MODULES:
    {
        return config.index_groups_title;
    }
    case folder_category::CLASSES:
    {
        return config.index_classes_title;
    }
    case folder_category::NAMESPACES:
    {
        return config.index_namespaces_title;
    }
    case folder_category::FILES:
    {
        return config.index_files_title;
    }
    case folder_category::PAGES:
    {
        return config.index_related_pages_title;
    }
    case folder_category::EXAMPLES:
    {
        return config.index_examples_title;
    }
    default:
    {
        throw EXCEPTION(
            "Type {} not recognised please contant the author!",
            int(type));
    }
    }
}
