//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_CONFIG_HPP
#define DOXYBOOK_CONFIG_HPP

#include <doxybook/enums.hpp>
#include <string>

namespace doxybook {
    /// Configuration for the @ref doxygen and @ref generator classes
    struct config {
        /// @name Output layout
        /// @{

        /// Where to store the output files?
        std::string output_dir;

        /// Generate extra JSON for each rendered template
        bool debug_template_json{ false };

        /// Put all files into categorized folders
        bool use_folders{ true };

        /// Whether we should allow undocumented macros
        bool undocumented_macros{ false };

        /// Put index files into the respective subdirectories
        /**
         * (Hugo/Learn) needs that
         */
        bool index_in_folders{ false };

        /// Main page should be located in the root directory
        bool main_page_in_root{ false };

        /// Name of the mainpage / indexpage
        std::string main_page_name{ "indexpage" };

        /// The base URL to prepend all links with
        std::string base_url{ "" };

        /// The extension for markdown files
        std::string file_extension{ "md" };

        /// The suffix to end links with
        std::string link_suffix{ ".md" };

        /// Replace underscores with hyphens in anchors
        bool replaceUnderscoresInAnchors{ true };

        ///@}

        /// @name Generator options
        /// @{

        /// Sort symbols alphabetically
        bool sort{ false };

        /// Copy images from the Doxygen xml dir
        bool copy_images{ true };

        /// Where to copy images
        std::string images_folder{ "images" };

        /// Convert all refids and folder names to lowercase
        bool link_lowercase{ false };

        /// Output links/code as \<a>/\<code> tags instead of Markdown.
        bool link_and_inline_code_as_html{ false };

        /// @}

        /// @name Folder names
        /// @{

        /// The modules folder name
        std::string folder_groups_name{ "libraries" };

        /// The classes folder name
        std::string folder_classes_name{ "classes" };

        /// The files folder name
        std::string folder_files_name{ "files" };

        /// The pages folder name
        std::string folder_related_pages_name{ "pages" };

        /// The namespaces folder name
        std::string folder_namespaces_name{ "namespaces" };

        /// The examples folder name
        std::string folder_examples_name{ "examples" };

        /// @}

        /// @name Index file names
        /// @{

        /// The groups index file name
        std::string index_groups_name{ "index_groups" };

        /// The classes index file name
        std::string index_classes_name{ "index_classes" };

        /// The files index file name
        std::string index_files_name{ "index_files" };

        /// The relatedPages index file name
        std::string index_related_pages_name{ "index_pages" };

        /// The namespaces index file name
        std::string index_namespaces_name{ "index_namespaces" };

        /// The examples index file name
        std::string index_examples_name{ "index_examples" };

        /// @}

        /// @name Template file names for symbol types
        /// @{

        /// The template file we should use for classes
        std::string template_kind_class{ "kind_class" };

        /// The template file we should use for structs
        std::string template_kind_struct{ "kind_class" };

        /// The template file we should use for unions
        std::string template_kind_union{ "kind_class" };

        /// The template file we should use for interfaces
        std::string template_kind_interface{ "kind_class" };

        /// The template file we should use for java enums
        std::string template_kind_java_enum{ "kind_class" };

        /// The template file we should use for namespaces
        std::string template_kind_namespace{ "kind_nonclass" };

        /// The template file we should use for groups
        std::string template_kind_group{ "kind_nonclass" };

        /// The template file we should use for files
        std::string template_kind_file{ "kind_file" };

        /// The template file we should use for dirs
        std::string template_kind_dir{ "kind_file" };

        /// The template file we should use for pages
        std::string template_kind_page{ "kind_page" };

        /// The template file we should use for examples
        std::string template_kind_example{ "kind_page" };

        /// @}

        /// @name Template file names for indexes
        /// @{

        /// The template file we should we for the class index
        std::string template_index_classes{ "index_classes" };

        /// The template file we should we for the namespace index
        std::string template_index_namespaces{ "index_namespaces" };

        /// The template file we should we for the group index
        std::string template_index_groups{ "index_groups" };

        /// The template file we should we for the file index
        std::string template_index_files{ "index_files" };

        /// The template file we should we for the related page index
        std::string template_index_related_pages{ "index_pages" };

        /// The template file we should we for the example index
        std::string template_index_examples{ "index_examples" };

        /// @}

        /// @name Index titles
        /// @{

        /// The title for classes in index pages
        std::string index_classes_title{ "Classes" };

        /// The title for namespaces in index pages
        std::string index_namespaces_title{ "Namespaces" };

        /// The title for groups in index pages
        std::string index_groups_title{ "Libraries" };

        /// The title for files in index pages
        std::string index_files_title{ "Files" };

        /// The title for relatedPages in index pages
        std::string index_related_pages_title{ "Pages" };

        /// The title for examples in index pages
        std::string index_examples_title{ "Examples" };

        /// @}

        /// @name Filters
        /// @{

        /// The source files allowed in the output?
        /**
         * An empty list means all files are allowed
         */
        std::vector<std::string> files_filter{};

        /// Folders we should generate
        std::vector<folder_category> folders_to_generate{
            folder_category::MODULES,    folder_category::CLASSES,
            folder_category::FILES,      folder_category::PAGES,
            folder_category::NAMESPACES, folder_category::EXAMPLES,
        };

        /// @}

        /// @name Latex formulas
        /// @{

        /// Token for latex formulas inline start
        std::string formulaInlineStart{ "\\(" };

        /// Token for latex formulas inline end
        std::string formulaInlineEnd{ "\\)" };

        /// Token for latex formulas block start
        std::string formulaBlockStart{ "\\[" };

        /// Token for latex formulas block end
        std::string formulaBlockEnd{ "\\]" };

        /// @}
    };

    /// Load configuration from a path
    void
    load_config(config& config, std::string const& path);

    /// Load configuration from a json string
    void
    load_config_data(config& config, std::string_view src);

    /// Save configuration to a path
    void
    save_config(config& config, std::string const& path);

} // namespace doxybook

#endif