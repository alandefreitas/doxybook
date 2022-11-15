//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_ENUMS_HPP
#define DOXYBOOK_ENUMS_HPP

#include <nlohmann/json.hpp>
#include <string>

namespace doxybook {
    struct config;

    /// The kind of a symbol in a doxygen xml file
    enum class kind
    {
        INDEX,
        DEFINE,
        CLASS,
        NAMESPACE,
        STRUCT,
        INTERFACE,
        FUNCTION,
        VARIABLE,
        TYPEDEF,
        USING,
        FRIEND,
        ENUM,
        ENUMVALUE,
        UNION,
        DIR,
        FILE,
        MODULE,
        PAGE,
        EXAMPLE,
        SIGNAL,
        SLOT,
        PROPERTY,
        EVENT,
        JAVAENUM,
        JAVAENUMCONSTANT
    };

    /// Types of symbol visibility
    enum class visibility
    {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        PACKAGE
    };

    /// Types of virtual functions
    enum class virtual_category
    {
        NON_VIRTUAL,
        VIRTUAL,
        PURE_VIRTUAL
    };

    /// Doxygen types
    enum class type
    {
        NONE,
        DEFINES,
        FUNCTIONS,
        NAMESPACES,
        CLASSES,
        ATTRIBUTES,
        TYPES,
        DIRS,
        FILES,
        MODULES,
        FRIENDS,
        PAGES,
        EXAMPLES,
        SIGNALS,
        SLOTS,
        EVENTS,
        PROPERTIES,
        JAVAENUMCONSTANTS
    };

    /// Types of folder category
    enum class folder_category
    {
        CLASSES,
        NAMESPACES,
        MODULES,
        PAGES,
        FILES,
        EXAMPLES
    };

    /// Convert a string to a doxygen kind
    extern kind
    to_enum_kind(std::string const& str);

    /// Convert a string to a doxygen type
    extern type
    to_enum_type(std::string const& str);

    /// Convert a string to a doxygen visibility type
    extern visibility
    to_enum_visibility(std::string const& str);

    /// Convert a string to a doxygen virtual category
    extern virtual_category
    to_enum_virtual(std::string const& str);

    /// Convert a string to a doxygen folder category
    extern folder_category
    to_enum_folder_category(std::string const& str);

    /// Convert a kind to a string
    extern std::string
    to_str(kind value);

    /// Convert a type to a string
    extern std::string
    to_str(type value);

    /// Convert a visibility to a string
    extern std::string
    to_str(visibility value);

    /// Convert a virtual_category to a string
    extern std::string
    to_str(virtual_category value);

    /// Convert a folder_category to a string
    extern std::string
    to_str(folder_category value);

    /// Convert a kind to a type
    extern type
    kind_to_type(kind kind);

    /// Determine if kind is a language feature
    extern bool
    is_kind_language(kind kind);

    /// Determine if kind is a structured type
    extern bool
    is_kind_structured(kind kind);

    /// Determine if kind is a file or directory
    extern bool
    is_kind_file(kind kind);

    /// Determine the appropriate folder name for a folder category
    /**
     * Get the appropriate folder name in the configuration file
     * for the specified folder category.
     *
     * Not all types have corresponding folder categories.
     *
     * @return The folder name
     */
    extern std::string
    type_folder_category_to_folder_name(
        config const& config,
        folder_category type);

    /// Determine the appropriate folder name for a type
    /**
     * Get the appropriate folder name in the configuration file
     * for the specified type.
     *
     * Not all types have corresponding folder categories.
     *
     * @return The folder name
     */
    extern std::string
    type_to_folder_name(config const& config, type type);

    /// Determine the appropriate index file name for a folder category
    /**
     * Get the appropriate index file name in the configuration file
     * for the specified folder category.
     *
     * Not all types have corresponding folder categories.
     *
     * @return The folder name
     */
    extern std::string
    type_to_index_name(config const& config, folder_category type);

    /// Determine the appropriate index template file name for a folder category
    /**
     * Get the appropriate template file name in the configuration file
     * for the specified folder category.
     *
     * Not all types have corresponding folder categories.
     *
     * @return The folder name
     */
    extern std::string
    type_to_index_template(config const& config, folder_category type);

    /// Determine the appropriate index title name for a folder category
    /**
     * Get the appropriate index title name in the configuration file
     * for the specified folder category.
     *
     * Not all types have corresponding folder categories.
     *
     * @return The folder name
     */
    extern std::string
    type_to_index_title(config const& config, folder_category type);

    /// Convert a visibility type to a json string
    inline void
    to_json(nlohmann::json& j, visibility const& p) {
        j = to_str(p);
    }

    /// Convert a json string to a visibility type
    inline void
    from_json(nlohmann::json const& j, visibility& p) {
        p = to_enum_visibility(j.get<std::string>());
    }

    /// Convert a folder category to a json string
    inline void
    to_json(nlohmann::json& j, folder_category const& p) {
        j = to_str(p);
    }

    /// Convert a json string to a folder category
    inline void
    from_json(nlohmann::json const& j, folder_category& p) {
        p = to_enum_folder_category(j.get<std::string>());
    }
} // namespace doxybook

#endif