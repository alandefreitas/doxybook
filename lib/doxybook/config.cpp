//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/config.hpp>
#include <doxybook/exception_utils.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fstream>

class config_arg {
public:
    template <typename T>
    config_arg(T doxybook::config::*ref, std::string const& key)
        : key(std::move(key)) {
        loadFunc =
            [=](config_arg const& self,
                doxybook::config& config,
                nlohmann::json const& json) {
            try {
                if (json.contains(self.key)) {
                    config.*ref = json.at(self.key).get<T>();
                }
            }
            catch (std::exception& e) {
                throw EXCEPTION(
                    "Failed to get config value {} error: {}",
                    self.key,
                    e.what());
            }
        };
        saveFunc =
            [=](config_arg const& self,
                doxybook::config const& config,
                nlohmann::json& json) {
            json[self.key] = config.*ref;
        };
    }

    std::string key;
    std::function<
        void(config_arg const&, doxybook::config& config, nlohmann::json const&)>
        loadFunc;
    std::function<
        void(config_arg const&, doxybook::config const& config, nlohmann::json&)>
        saveFunc;
};

static const std::vector<config_arg> CONFIG_ARGS = {
    config_arg(&doxybook::config::base_url, "baseUrl"),
    config_arg(&doxybook::config::file_extension, "fileExt"),
    config_arg(&doxybook::config::link_suffix, "linkSuffix"),
    config_arg(&doxybook::config::link_lowercase, "linkLowercase"),
    config_arg(
        &doxybook::config::link_and_inline_code_as_html,
        "linkAndInlineCodeAsHTML"),
    config_arg(&doxybook::config::copy_images, "copyImages"),
    config_arg(&doxybook::config::sort, "sort"),
    config_arg(&doxybook::config::use_folders, "useFolders"),
    config_arg(&doxybook::config::undocumented_macros, "undocumentedMacros"),
    config_arg(&doxybook::config::images_folder, "imagesFolder"),
    config_arg(&doxybook::config::main_page_name, "mainPageName"),
    config_arg(&doxybook::config::main_page_in_root, "mainPageInRoot"),
    config_arg(&doxybook::config::folder_classes_name, "folderClassesName"),
    config_arg(&doxybook::config::folder_files_name, "folderFilesName"),
    config_arg(&doxybook::config::folder_groups_name, "folderGroupsName"),
    config_arg(&doxybook::config::folder_namespaces_name, "folderNamespacesName"),
    config_arg(
        &doxybook::config::folder_related_pages_name,
        "folderRelatedPagesName"),
    config_arg(&doxybook::config::folder_examples_name, "folderExamplesName"),
    config_arg(&doxybook::config::index_in_folders, "indexInFolders"),
    config_arg(&doxybook::config::index_classes_name, "indexClassesName"),
    config_arg(&doxybook::config::index_files_name, "indexFilesName"),
    config_arg(&doxybook::config::index_groups_name, "indexGroupsName"),
    config_arg(&doxybook::config::index_namespaces_name, "indexNamespacesName"),
    config_arg(
        &doxybook::config::index_related_pages_name,
        "indexRelatedPagesName"),
    config_arg(&doxybook::config::index_examples_name, "indexExamplesName"),
    config_arg(&doxybook::config::template_index_classes, "templateIndexClasses"),
    config_arg(&doxybook::config::template_index_files, "templateIndexFiles"),
    config_arg(&doxybook::config::template_index_groups, "templateIndexGroups"),
    config_arg(
        &doxybook::config::template_index_namespaces,
        "templateIndexNamespaces"),
    config_arg(
        &doxybook::config::template_index_related_pages,
        "templateIndexRelatedPages"),
    config_arg(
        &doxybook::config::template_index_examples,
        "templateIndexExamples"),
    config_arg(&doxybook::config::template_kind_group, "templateKindGroup"),
    config_arg(&doxybook::config::template_kind_class, "templateKindClass"),
    config_arg(&doxybook::config::template_kind_dir, "templateKindDir"),
    config_arg(&doxybook::config::template_kind_page, "templateKindPage"),
    config_arg(
        &doxybook::config::template_kind_interface,
        "templateKindInterface"),
    config_arg(&doxybook::config::template_kind_file, "templateKindFile"),
    config_arg(
        &doxybook::config::template_kind_namespace,
        "templateKindNamespace"),
    config_arg(&doxybook::config::template_kind_struct, "templateKindStruct"),
    config_arg(&doxybook::config::template_kind_union, "templateKindUnion"),
    config_arg(&doxybook::config::template_kind_example, "templateKindExample"),
    config_arg(&doxybook::config::index_classes_title, "indexClassesTitle"),
    config_arg(&doxybook::config::index_namespaces_title, "indexNamespacesTitle"),
    config_arg(&doxybook::config::index_groups_title, "indexGroupsTitle"),
    config_arg(
        &doxybook::config::index_related_pages_title,
        "indexRelatedPagesTitle"),
    config_arg(&doxybook::config::index_files_title, "indexFilesTitle"),
    config_arg(&doxybook::config::index_examples_title, "indexExamplesTitle"),
    config_arg(&doxybook::config::files_filter, "filesFilter"),
    config_arg(&doxybook::config::folders_to_generate, "foldersToGenerate"),
    config_arg(&doxybook::config::formulaInlineStart, "formulaInlineStart"),
    config_arg(&doxybook::config::formulaInlineEnd, "formulaInlineEnd"),
    config_arg(&doxybook::config::formulaBlockStart, "formulaBlockStart"),
    config_arg(&doxybook::config::formulaBlockEnd, "formulaBlockEnd"),
    config_arg(
        &doxybook::config::replaceUnderscoresInAnchors,
        "replaceUnderscoresInAnchors"),
};

void
doxybook::load_config(config& config, std::string const& path) {
    std::ifstream file(path);
    if (!file) {
        throw EXCEPTION("Failed to open file {} for reading", path);
    }

    std::string
        str((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
    try {
        auto const json = nlohmann::json::parse(str);

        for (auto const& arg: CONFIG_ARGS) {
            arg.loadFunc(arg, config, json);
        }
    }
    catch (std::exception& e) {
        throw EXCEPTION("Failed to pase config error {}", e.what());
    }
}

void
doxybook::load_config_data(config& config, std::string_view src) {
    try {
        auto const json = nlohmann::json::parse(src);

        for (auto const& arg: CONFIG_ARGS) {
            arg.loadFunc(arg, config, json);
        }
    }
    catch (std::exception& e) {
        throw EXCEPTION("Failed to pase config error {}", e.what());
    }
}

void
doxybook::save_config(config& config, std::string const& path) {
    spdlog::info("Creating default config {}", path);
    std::ofstream file(path);
    if (!file) {
        throw EXCEPTION("Failed to open file {} for writing", path);
    }

    nlohmann::json json;
    for (auto const& arg: CONFIG_ARGS) {
        arg.saveFunc(arg, config, json);
    }

    file << json.dump(2);
}
