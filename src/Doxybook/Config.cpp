#include "ExceptionUtils.hpp"
#include <Doxybook/Config.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

class ConfigArg {
public:
    template <typename T> ConfigArg(T Doxybook::Config::*ref, const std::string& key) : key(std::move(key)) {
        loadFunc = [=](const ConfigArg& self, Doxybook::Config& config, const nlohmann::json& json) {
            try {
                if (json.contains(self.key)) {
                    config.*ref = json.at(self.key).get<T>();
                }
            } catch (std::exception& e) {
                throw EXCEPTION("Failed to get config value {} error: {}", self.key, e.what());
            }
        };
        saveFunc = [=](const ConfigArg& self, const Doxybook::Config& config, nlohmann::json& json) {
            json[self.key] = config.*ref;
        };
    }

    std::string key;
    std::function<void(const ConfigArg&, Doxybook::Config& config, const nlohmann::json&)> loadFunc;
    std::function<void(const ConfigArg&, const Doxybook::Config& config, nlohmann::json&)> saveFunc;
};

static const std::vector<ConfigArg> CONFIG_ARGS = {
    ConfigArg(&Doxybook::Config::baseUrl, "baseUrl"),
    ConfigArg(&Doxybook::Config::fileExt, "fileExt"),
    ConfigArg(&Doxybook::Config::linkSuffix, "linkSuffix"),
    ConfigArg(&Doxybook::Config::linkLowercase, "linkLowercase"),
    ConfigArg(&Doxybook::Config::linkAndInlineCodeAsHTML, "linkAndInlineCodeAsHTML"),
    ConfigArg(&Doxybook::Config::copyImages, "copyImages"),
    ConfigArg(&Doxybook::Config::sort, "sort"),
    ConfigArg(&Doxybook::Config::useFolders, "useFolders"),
    ConfigArg(&Doxybook::Config::imagesFolder, "imagesFolder"),
    ConfigArg(&Doxybook::Config::mainPageName, "mainPageName"),
    ConfigArg(&Doxybook::Config::mainPageInRoot, "mainPageInRoot"),
    ConfigArg(&Doxybook::Config::folderClassesName, "folderClassesName"),
    ConfigArg(&Doxybook::Config::folderFilesName, "folderFilesName"),
    ConfigArg(&Doxybook::Config::folderGroupsName, "folderGroupsName"),
    ConfigArg(&Doxybook::Config::folderNamespacesName, "folderNamespacesName"),
    ConfigArg(&Doxybook::Config::folderRelatedPagesName, "folderRelatedPagesName"),
    ConfigArg(&Doxybook::Config::folderExamplesName, "folderExamplesName"),
    ConfigArg(&Doxybook::Config::indexInFolders, "indexInFolders"),
    ConfigArg(&Doxybook::Config::indexClassesName, "indexClassesName"),
    ConfigArg(&Doxybook::Config::indexFilesName, "indexFilesName"),
    ConfigArg(&Doxybook::Config::indexGroupsName, "indexGroupsName"),
    ConfigArg(&Doxybook::Config::indexNamespacesName, "indexNamespacesName"),
    ConfigArg(&Doxybook::Config::indexRelatedPagesName, "indexRelatedPagesName"),
    ConfigArg(&Doxybook::Config::indexExamplesName, "indexExamplesName"),
    ConfigArg(&Doxybook::Config::templateIndexClasses, "templateIndexClasses"),
    ConfigArg(&Doxybook::Config::templateIndexFiles, "templateIndexFiles"),
    ConfigArg(&Doxybook::Config::templateIndexGroups, "templateIndexGroups"),
    ConfigArg(&Doxybook::Config::templateIndexNamespaces, "templateIndexNamespaces"),
    ConfigArg(&Doxybook::Config::templateIndexRelatedPages, "templateIndexRelatedPages"),
    ConfigArg(&Doxybook::Config::templateIndexExamples, "templateIndexExamples"),
    ConfigArg(&Doxybook::Config::templateKindGroup, "templateKindGroup"),
    ConfigArg(&Doxybook::Config::templateKindClass, "templateKindClass"),
    ConfigArg(&Doxybook::Config::templateKindDir, "templateKindDir"),
    ConfigArg(&Doxybook::Config::templateKindPage, "templateKindPage"),
    ConfigArg(&Doxybook::Config::templateKindInterface, "templateKindInterface"),
    ConfigArg(&Doxybook::Config::templateKindFile, "templateKindFile"),
    ConfigArg(&Doxybook::Config::templateKindNamespace, "templateKindNamespace"),
    ConfigArg(&Doxybook::Config::templateKindStruct, "templateKindStruct"),
    ConfigArg(&Doxybook::Config::templateKindUnion, "templateKindUnion"),
    ConfigArg(&Doxybook::Config::templateKindExample, "templateKindExample"),
    ConfigArg(&Doxybook::Config::indexClassesTitle, "indexClassesTitle"),
    ConfigArg(&Doxybook::Config::indexNamespacesTitle, "indexNamespacesTitle"),
    ConfigArg(&Doxybook::Config::indexGroupsTitle, "indexGroupsTitle"),
    ConfigArg(&Doxybook::Config::indexRelatedPagesTitle, "indexRelatedPagesTitle"),
    ConfigArg(&Doxybook::Config::indexFilesTitle, "indexFilesTitle"),
    ConfigArg(&Doxybook::Config::indexExamplesTitle, "indexExamplesTitle"),
    ConfigArg(&Doxybook::Config::filesFilter, "filesFilter"),
    ConfigArg(&Doxybook::Config::foldersToGenerate, "foldersToGenerate"),
    ConfigArg(&Doxybook::Config::formulaInlineStart, "formulaInlineStart"),
    ConfigArg(&Doxybook::Config::formulaInlineEnd, "formulaInlineEnd"),
    ConfigArg(&Doxybook::Config::formulaBlockStart, "formulaBlockStart"),
    ConfigArg(&Doxybook::Config::formulaBlockEnd, "formulaBlockEnd"),
    ConfigArg(&Doxybook::Config::replaceUnderscoresInAnchors, "replaceUnderscoresInAnchors"),
};

void Doxybook::loadConfig(Config& config, const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw EXCEPTION("Failed to open file {} for reading", path);
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    try {
        const auto json = nlohmann::json::parse(str);

        for (const auto& arg : CONFIG_ARGS) {
            arg.loadFunc(arg, config, json);
        }
    } catch (std::exception& e) {
        throw EXCEPTION("Failed to pase config error {}", e.what());
    }
}

void Doxybook::loadConfigData(Config& config, const std::string& src) {
    try {
        const auto json = nlohmann::json::parse(src);

        for (const auto& arg : CONFIG_ARGS) {
            arg.loadFunc(arg, config, json);
        }
    } catch (std::exception& e) {
        throw EXCEPTION("Failed to pase config error {}", e.what());
    }
}

void Doxybook::saveConfig(Config& config, const std::string& path) {
    spdlog::info("Creating default config {}", path);
    std::ofstream file(path);
    if (!file) {
        throw EXCEPTION("Failed to open file {} for writing", path);
    }

    nlohmann::json json;
    for (const auto& arg : CONFIG_ARGS) {
        arg.saveFunc(arg, config, json);
    }

    file << json.dump(2);
}
