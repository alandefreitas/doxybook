#include "ExceptionUtils.hpp"
#include <Doxybook/Config.hpp>
#include <Doxybook/Enums.hpp>
#include <unordered_map>

using KindStrPair = std::pair<std::string, Doxybook::Kind>;
using TypeStrPair = std::pair<std::string, Doxybook::Type>;
using VirtualStrPair = std::pair<std::string, Doxybook::Virtual>;
using VisibilityStrPair = std::pair<std::string, Doxybook::Visibility>;
using FolderCategoryStrPair = std::pair<std::string, Doxybook::FolderCategory>;

// clang-format off
static const std::vector<KindStrPair> KIND_STRS = {
    {"class", Doxybook::Kind::CLASS},
    {"namespace", Doxybook::Kind::NAMESPACE},
    {"struct", Doxybook::Kind::STRUCT},
    {"interface", Doxybook::Kind::INTERFACE},
    {"function", Doxybook::Kind::FUNCTION},
    {"variable", Doxybook::Kind::VARIABLE},
    {"typedef", Doxybook::Kind::TYPEDEF},
    {"using", Doxybook::Kind::USING},
    {"enum", Doxybook::Kind::ENUM},
    {"union", Doxybook::Kind::UNION},
    {"enumvalue", Doxybook::Kind::ENUMVALUE},
    {"dir", Doxybook::Kind::DIR},
    {"file", Doxybook::Kind::FILE},
    {"group", Doxybook::Kind::MODULE},
    {"friend", Doxybook::Kind::FRIEND},
    {"page", Doxybook::Kind::PAGE},
    {"example", Doxybook::Kind::EXAMPLE},
    {"signal", Doxybook::Kind::SIGNAL},
    {"slot", Doxybook::Kind::SLOT},
    {"property", Doxybook::Kind::PROPERTY},
    {"event", Doxybook::Kind::EVENT},
    {"define", Doxybook::Kind::DEFINE},
    {"enum", Doxybook::Kind::JAVAENUM},                  // only for enum->string conversion
    {"enum constant", Doxybook::Kind::JAVAENUMCONSTANT}  // only for enum->string conversion
};

static const std::vector<TypeStrPair> TYPE_STRS = {
    {"attributes", Doxybook::Type::ATTRIBUTES},
    {"classes", Doxybook::Type::CLASSES},
    {"defines", Doxybook::Type::DEFINES},
    {"files", Doxybook::Type::FILES},
    {"dirs", Doxybook::Type::DIRS},
    {"friends", Doxybook::Type::FRIENDS},
    {"functions", Doxybook::Type::FUNCTIONS},
    {"modules", Doxybook::Type::MODULES},
    {"namespaces", Doxybook::Type::NAMESPACES},
    {"types", Doxybook::Type::TYPES},
    {"pages", Doxybook::Type::PAGES},
    {"examples", Doxybook::Type::EXAMPLES},
    {"signals", Doxybook::Type::SIGNALS},
    {"slots", Doxybook::Type::SLOTS},
    {"events", Doxybook::Type::EVENTS},
    {"properties", Doxybook::Type::PROPERTIES},
    {"javaenumconstants", Doxybook::Type::JAVAENUMCONSTANTS}
};

static const std::vector<VirtualStrPair> VIRTUAL_STRS = {
    {"non-virtual", Doxybook::Virtual::NON_VIRTUAL},
    {"virtual", Doxybook::Virtual::VIRTUAL},
    {"pure", Doxybook::Virtual::PURE_VIRTUAL},
    {"pure-virtual", Doxybook::Virtual::PURE_VIRTUAL}
};

static const std::vector<VisibilityStrPair> VISIBILITY_STRS = {
    {"public", Doxybook::Visibility::PUBLIC},
    {"protected", Doxybook::Visibility::PROTECTED},
    {"private", Doxybook::Visibility::PRIVATE},
    {"package", Doxybook::Visibility::PACKAGE}
};

static const std::vector<FolderCategoryStrPair> FOLDER_CATEGORY_STRS = {
    {"modules", Doxybook::FolderCategory::MODULES},
    {"namespaces", Doxybook::FolderCategory::NAMESPACES},
    {"files", Doxybook::FolderCategory::FILES},
    {"examples", Doxybook::FolderCategory::EXAMPLES},
    {"classes", Doxybook::FolderCategory::CLASSES},
    {"pages", Doxybook::FolderCategory::PAGES}
};
// clang-format on

template <typename Enum> struct EnumName { static inline const auto name = "unknown"; };

template <> struct EnumName<Doxybook::Kind> { static inline const auto name = "Kind"; };
template <> struct EnumName<Doxybook::Type> { static inline const auto name = "Type"; };
template <> struct EnumName<Doxybook::Virtual> { static inline const auto name = "Virtual"; };
template <> struct EnumName<Doxybook::Visibility> { static inline const auto name = "Visibility"; };
template <> struct EnumName<Doxybook::FolderCategory> { static inline const auto name = "FolderCategory"; };

template <typename Enum>
static Enum toEnum(const std::vector<std::pair<std::string, Enum>>& pairs, const std::string& str) {
    const auto it = std::find_if(
        pairs.begin(), pairs.end(), [&](const std::pair<std::string, Enum>& pair) { return pair.first == str; });

    if (it == pairs.end()) {
        throw EXCEPTION("String '{}' not recognised as a valid enum of '{}'", str, EnumName<Enum>::name);
    }

    return it->second;
}

template <typename Enum>
static std::string fromEnum(const std::vector<std::pair<std::string, Enum>>& pairs, const Enum value) {
    const auto it = std::find_if(
        pairs.begin(), pairs.end(), [&](const std::pair<std::string, Enum>& pair) { return pair.second == value; });

    if (it == pairs.end()) {
        throw EXCEPTION(
            "Enum '{}' of value '{}' not recognised please contact the author", EnumName<Enum>::name, int(value));
    }

    return it->first;
}

Doxybook::Kind Doxybook::toEnumKind(const std::string& str) {
    return toEnum<Kind>(KIND_STRS, str);
}

std::string Doxybook::toStr(const Kind value) {
    return fromEnum<Kind>(KIND_STRS, value);
}

Doxybook::Virtual Doxybook::toEnumVirtual(const std::string& str) {
    return toEnum<Virtual>(VIRTUAL_STRS, str);
}

std::string Doxybook::toStr(const Virtual value) {
    return fromEnum<Virtual>(VIRTUAL_STRS, value);
}

Doxybook::Visibility Doxybook::toEnumVisibility(const std::string& str) {
    return toEnum<Visibility>(VISIBILITY_STRS, str);
}

std::string Doxybook::toStr(const Visibility value) {
    return fromEnum<Visibility>(VISIBILITY_STRS, value);
}

Doxybook::Type Doxybook::toEnumType(const std::string& str) {
    return toEnum<Type>(TYPE_STRS, str);
}

std::string Doxybook::toStr(const Type value) {
    return fromEnum<Type>(TYPE_STRS, value);
}

Doxybook::FolderCategory Doxybook::toEnumFolderCategory(const std::string& str) {
    return toEnum<FolderCategory>(FOLDER_CATEGORY_STRS, str);
}

std::string Doxybook::toStr(const FolderCategory value) {
    return fromEnum<FolderCategory>(FOLDER_CATEGORY_STRS, value);
}

Doxybook::Type Doxybook::kindToType(const Doxybook::Kind kind) {
    switch (kind) {
        case Kind::DEFINE: {
            return Type::DEFINES;
        }
        case Kind::FRIEND: {
            return Type::FRIENDS;
        }
        case Kind::VARIABLE: {
            return Type::ATTRIBUTES;
        }
        case Kind::FUNCTION: {
            return Type::FUNCTIONS;
        }
        case Kind::ENUMVALUE:
        case Kind::ENUM:
        case Kind::USING:
        case Kind::TYPEDEF: {
            return Type::TYPES;
        }
        case Kind::MODULE: {
            return Type::MODULES;
        }
        case Kind::NAMESPACE: {
            return Type::NAMESPACES;
        }
        case Kind::UNION:
        case Kind::INTERFACE:
        case Kind::STRUCT:
        case Kind::CLASS:
        case Kind::JAVAENUM: {
            return Type::CLASSES;
        }
        case Kind::FILE: {
            return Type::FILES;
        }
        case Kind::DIR: {
            return Type::DIRS;
        }
        case Kind::PAGE: {
            return Type::PAGES;
        }
        case Kind::EXAMPLE: {
            return Type::EXAMPLES;
        }
        case Kind::SIGNAL: {
            return Type::SIGNALS;
        }
        case Kind::SLOT: {
            return Type::SLOTS;
        }
        case Kind::EVENT: {
            return Type::EVENTS;
        }
        case Kind::PROPERTY: {
            return Type::PROPERTIES;
        }
        default: {
            break;
        }
    }
    return Type::NONE;
}

bool Doxybook::isKindStructured(const Kind kind) {
    switch (kind) {
        case Doxybook::Kind::CLASS:
        case Doxybook::Kind::NAMESPACE:
        case Doxybook::Kind::STRUCT:
        case Doxybook::Kind::UNION:
        case Doxybook::Kind::JAVAENUM:
        case Doxybook::Kind::INTERFACE: {
            return true;
        }
        default: {
            return false;
        }
    }
}

bool Doxybook::isKindLanguage(const Kind kind) {
    switch (kind) {
        case Doxybook::Kind::DEFINE:
        case Doxybook::Kind::CLASS:
        case Doxybook::Kind::NAMESPACE:
        case Doxybook::Kind::STRUCT:
        case Doxybook::Kind::UNION:
        case Doxybook::Kind::INTERFACE:
        case Doxybook::Kind::ENUM:
        case Doxybook::Kind::FUNCTION:
        case Doxybook::Kind::TYPEDEF:
        case Doxybook::Kind::USING:
        case Doxybook::Kind::FRIEND:
        case Doxybook::Kind::VARIABLE:
        case Doxybook::Kind::SIGNAL:
        case Doxybook::Kind::SLOT:
        case Doxybook::Kind::PROPERTY:
        case Doxybook::Kind::EVENT:
        case Doxybook::Kind::JAVAENUM:
        case Doxybook::Kind::JAVAENUMCONSTANT: {
            return true;
        }
        default: {
            return false;
        }
    }
}

bool Doxybook::isKindFile(const Kind kind) {
    switch (kind) {
        case Doxybook::Kind::DIR:
        case Doxybook::Kind::FILE: {
            return true;
        }
        default: {
            return false;
        }
    }
}

std::string Doxybook::typeFolderCategoryToFolderName(const Config& config, FolderCategory type) {
    if (!config.useFolders)
        return "";

    switch (type) {
        case FolderCategory::MODULES: {
            return config.folderGroupsName;
        }
        case FolderCategory::CLASSES: {
            return config.folderClassesName;
        }
        case FolderCategory::NAMESPACES: {
            return config.folderNamespacesName;
        }
        case FolderCategory::FILES: {
            return config.folderFilesName;
        }
        case FolderCategory::PAGES: {
            return config.folderRelatedPagesName;
        }
        case FolderCategory::EXAMPLES: {
            return config.folderExamplesName;
        }
        default: {
            throw EXCEPTION("FolderCategory {} not recognised please contant the author!", int(type));
        }
    }
}

std::string Doxybook::typeToFolderName(const Config& config, const Type type) {
    if (!config.useFolders)
        return "";

    switch (type) {
        case Type::MODULES: {
            return config.folderGroupsName;
        }
        case Type::CLASSES: {
            return config.folderClassesName;
        }
        case Type::NAMESPACES: {
            return config.folderNamespacesName;
        }
        case Type::DIRS:
        case Type::FILES: {
            return config.folderFilesName;
        }
        case Type::PAGES: {
            return config.folderRelatedPagesName;
        }
        case Type::EXAMPLES: {
            return config.folderExamplesName;
        }
        default: {
            throw EXCEPTION("Type {} not recognised please contant the author!", int(type));
        }
    }
}

std::string Doxybook::typeToIndexName(const Config& config, const FolderCategory type) {
    switch (type) {
        case FolderCategory::MODULES: {
            return config.indexInFolders && config.useFolders ? config.folderGroupsName + "/" + config.indexGroupsName
                                                              : config.indexGroupsName;
        }
        case FolderCategory::CLASSES: {
            return config.indexInFolders && config.useFolders ? config.folderClassesName + "/" + config.indexClassesName
                                                              : config.indexClassesName;
        }
        case FolderCategory::NAMESPACES: {
            return config.indexInFolders && config.useFolders
                       ? config.folderNamespacesName + "/" + config.indexNamespacesName
                       : config.indexNamespacesName;
        }
        case FolderCategory::FILES: {
            return config.indexInFolders && config.useFolders ? config.folderFilesName + "/" + config.indexFilesName
                                                              : config.indexFilesName;
        }
        case FolderCategory::PAGES: {
            return config.indexInFolders && config.useFolders
                       ? config.folderRelatedPagesName + "/" + config.indexRelatedPagesName
                       : config.indexRelatedPagesName;
        }
        case FolderCategory::EXAMPLES: {
            return config.indexInFolders && config.useFolders
                       ? config.folderExamplesName + "/" + config.indexExamplesName
                       : config.indexExamplesName;
        }
        default: {
            throw EXCEPTION("Type {} not recognised please contant the author!", int(type));
        }
    }
}

std::string Doxybook::typeToIndexTemplate(const Config& config, const FolderCategory type) {
    switch (type) {
        case FolderCategory::MODULES: {
            return config.templateIndexGroups;
        }
        case FolderCategory::CLASSES: {
            return config.templateIndexClasses;
        }
        case FolderCategory::NAMESPACES: {
            return config.templateIndexNamespaces;
        }
        case FolderCategory::FILES: {
            return config.templateIndexFiles;
        }
        case FolderCategory::PAGES: {
            return config.templateIndexRelatedPages;
        }
        case FolderCategory::EXAMPLES: {
            return config.templateIndexExamples;
        }
        default: {
            throw EXCEPTION("Type {} not recognised please contant the author!", int(type));
        }
    }
}

std::string Doxybook::typeToIndexTitle(const Config& config, const FolderCategory type) {
    switch (type) {
        case FolderCategory::MODULES: {
            return config.indexGroupsTitle;
        }
        case FolderCategory::CLASSES: {
            return config.indexClassesTitle;
        }
        case FolderCategory::NAMESPACES: {
            return config.indexNamespacesTitle;
        }
        case FolderCategory::FILES: {
            return config.indexFilesTitle;
        }
        case FolderCategory::PAGES: {
            return config.indexRelatedPagesTitle;
        }
        case FolderCategory::EXAMPLES: {
            return config.indexExamplesTitle;
        }
        default: {
            throw EXCEPTION("Type {} not recognised please contant the author!", int(type));
        }
    }
}
