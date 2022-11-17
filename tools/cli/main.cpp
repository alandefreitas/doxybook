#include <doxybook/default_templates.hpp>
#include <doxybook/doxygen.hpp>
#include <doxybook/generator.hpp>
#include <doxybook/path.hpp>
#include <doxybook/text_markdown_printer.hpp>
#include <doxybook/text_plain_printer.hpp>
#include <doxybook/utils.hpp>
#include <spdlog/spdlog.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#ifdef __GNUC__
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#    pragma GCC diagnostic ignored "-Wuninitialized"
#endif
#include <cxxopts.hpp>
#ifdef __GNUC__
#    pragma GCC diagnostic pop
#endif

#define DOXYBOOK_MACRO_TO_STRING(a)     DOXYBOOK_MACRO_TO_STRING_AUX(a)
#define DOXYBOOK_MACRO_TO_STRING_AUX(a) #a

#ifdef VERSION
static const std::string version = DOXYBOOK_MACRO_TO_STRING(VERSION);
#else
static const std::string version = "unknown";
#endif

#ifdef VERSION_HASH
static const std::string version_hash = DOXYBOOK_MACRO_TO_STRING(VERSION_HASH);
#else
static const std::string version_hash = "unknown";
#endif

#undef DOXYBOOK_MACRO_TO_STRING
#undef DOXYBOOK_MACRO_TO_STRING_AUX

using namespace doxybook;

static const generator::filter_set INDEX_CLASS_FILTER = {
    kind::NAMESPACE, kind::CLASS, kind::INTERFACE,
    kind::STRUCT,    kind::UNION, kind::JAVAENUM
};

static const generator::filter_set INDEX_CLASS_FILTER_SKIP = {
    kind::NAMESPACE
};

static const generator::filter_set INDEX_NAMESPACES_FILTER = {
    kind::NAMESPACE
};

static const generator::filter_set INDEX_MODULES_FILTER = { kind::MODULE };

static const generator::filter_set INDEX_FILES_FILTER = {
    kind::DIR,
    kind::FILE
};

static const generator::filter_set LANGUAGE_FILTER = {
    kind::NAMESPACE, kind::CLASS,  kind::INTERFACE, kind::STRUCT,
    kind::UNION,     kind::MODULE, kind::JAVAENUM
};

static const generator::filter_set INDEX_PAGES_FILTER = { kind::PAGE };

static const generator::filter_set INDEX_EXAMPLES_FILTER = { kind::EXAMPLE };

int
main(int argc, char* argv[]) {
    spdlog::set_pattern("%^[%l]%$ %v");

    cxxopts::Options options("doxybook", "Doxygen XML to Markdown (or JSON)");

    options.add_options()("h, help", "Shows this help message.")(
        "v, version",
        "Shows the version.")(
        "q, quiet",
        "Run in quiet mode, no stdout, display only errors and warnings to "
        "stderr.",
        cxxopts::value<bool>()->default_value("false"))(
        "i, input",
        "Path to the generated Doxygen XML folder. Must contain index.xml!",
        cxxopts::value<std::string>())(
        "o, output",
        "Path to the target folder where to generate markdown files.",
        cxxopts::value<std::string>())(
        "j, json",
        "Generate JSON only, no markdown, into the output path. This will also "
        "generate index.json.")(
        "c, config",
        "Optional path to a config json file.",
        cxxopts::value<std::string>())(
        "config-data",
        "Optional json data to override config.",
        cxxopts::value<std::string>())(
        "t, templates",
        "Optional path to a folder with templates.",
        cxxopts::value<std::string>())(
        "generate-config",
        "Generate config file given a path to the destination json file",
        cxxopts::value<std::string>())(
        "generate-templates",
        "Generate template files given a path to a target folder.",
        cxxopts::value<std::string>())(
        "d, debug-templates",
        "Debug templates. This will create JSON for each generated template.")(
        "summary-input",
        "Path to the summary input file. This file must contain "
        "\"{{doxygen}}\" string.",
        cxxopts::value<std::string>())(
        "summary-output",
        "Where to generate summary file. This file will be created. Not a "
        "directory!",
        cxxopts::value<std::string>())(
        "example",
        "Example usage:\n"
        "    doxybook --generate-config doxybook.json\n"
        "    doxybook -i ./doxygen/xml -o ./docs/content -c doxybook.json\n"
        "\n");

    try {
        config c;

        auto args = options.parse(argc, argv);

        if (args["quiet"].as<bool>()) {
            spdlog::set_level(spdlog::level::off);
        }

        if (args["help"].as<bool>()) {
            if (args.count("output")) {
                auto p = std::filesystem::path(
                    args["output"].as<std::string>());
                std::filesystem::create_directories(p.parent_path());
                std::ofstream fout(p);
                if (fout.good()) {
                    fout << options.help();
                } else {
                    return EXIT_FAILURE;
                }
            } else {
                std::cout << options.help() << std::endl;
            }
            return EXIT_SUCCESS;
        }

        else if (args["version"].as<bool>())
        {
            std::cout << version;
            std::cout << "-";
            std::cout << version_hash;
            return EXIT_SUCCESS;
        }

        else if (args.count("generate-config"))
        {
            save_config(c, args["generate-config"].as<std::string>());
            return EXIT_SUCCESS;
        }

        else if (args.count("generate-templates"))
        {
            save_default_templates(
                args["generate-templates"].as<std::string>());
            return EXIT_SUCCESS;
        }

        else if (args.count("output"))
        {
            if (!args.count("input")) {
                std::cout << "You need to provide input path!" << std::endl;
                std::cout << options.help();
                return EXIT_FAILURE;
            }

            if (args.count("config")) {
                load_config(c, args["config"].as<std::string>());
            }

            if (args.count("config-data")) {
                load_config_data(c, args["config-data"].as<std::string>());
            }

            if (args.count("debug-templates")) {
                c.debug_template_json = true;
            }

            if (args.count("json")) {
                c.use_folders = false;
                c.images_folder = "";
            }

            c.output_dir = args["output"].as<std::string>();

            doxygen d(c);
            std::string s = args["input"].as<std::string>();
            text_markdown_printer markdown_printer(c, s, d);
            text_plain_printer plain_printer(c, d);
            json_converter conv(c, d, plain_printer, markdown_printer);

            std::optional<std::string> templates_path;
            if (args.count("templates")) {
                templates_path = args["templates"].as<std::string>();
            }

            generator g(c, d, conv, templates_path);

            auto const should_generate = [&](const folder_category category) {
                return std::find(
                           c.folders_to_generate.begin(),
                           c.folders_to_generate.end(),
                           category)
                       != c.folders_to_generate.end();
            };

            if (c.use_folders) {
                static const std::array<folder_category, 6> ALL_GROUPS = {
                    folder_category::CLASSES, folder_category::NAMESPACES,
                    folder_category::FILES,   folder_category::MODULES,
                    folder_category::PAGES,   folder_category::EXAMPLES,
                };
                for (auto const& g: ALL_GROUPS) {
                    if (should_generate(g)) {
                        auto dir = path::join(
                            c.output_dir,
                            type_folder_category_to_folder_name(c, g));
                        utils::create_directory(dir);
                    }
                }
                if (!c.images_folder.empty()) {
                    utils::create_directory(
                        path::join(c.output_dir, c.images_folder));
                }
            }

            spdlog::info("Loading...");
            d.load(args["input"].as<std::string>());
            spdlog::info("Finalizing...");
            d.finalize(plain_printer, markdown_printer);
            spdlog::info("Rendering...");

            if (args.count("json")) {
                g.json(LANGUAGE_FILTER, {});
                g.json(INDEX_FILES_FILTER, {});
                g.json(INDEX_PAGES_FILTER, {});

                g.manifest();
            } else {
                if (args.count("summary-input") && args.count("summary-output"))
                {
                    std::vector<generator::summary_section> sections;
                    if (should_generate(folder_category::CLASSES)) {
                        sections.push_back(
                            { folder_category::CLASSES,
                              INDEX_CLASS_FILTER,
                              INDEX_CLASS_FILTER_SKIP });
                    }
                    if (should_generate(folder_category::NAMESPACES)) {
                        sections.push_back(
                            { folder_category::NAMESPACES,
                              INDEX_NAMESPACES_FILTER,
                              {} });
                    }
                    if (should_generate(folder_category::MODULES)) {
                        sections.push_back(
                            { folder_category::MODULES,
                              INDEX_MODULES_FILTER,
                              {} });
                    }
                    if (should_generate(folder_category::FILES)) {
                        sections.push_back(
                            { folder_category::FILES, INDEX_FILES_FILTER, {} });
                    }
                    if (should_generate(folder_category::PAGES)) {
                        sections.push_back(
                            { folder_category::PAGES, INDEX_PAGES_FILTER, {} });
                    }
                    if (should_generate(folder_category::EXAMPLES)) {
                        sections.push_back(
                            { folder_category::EXAMPLES,
                              INDEX_EXAMPLES_FILTER,
                              {} });
                    }

                    g.summary(
                        args["summary-input"].as<std::string>(),
                        args["summary-output"].as<std::string>(),
                        sections);
                }

                generator::filter_set language_filter;
                if (should_generate(folder_category::CLASSES)) {
                    language_filter.insert(kind::CLASS);
                    language_filter.insert(kind::STRUCT);
                    language_filter.insert(kind::UNION);
                    language_filter.insert(kind::INTERFACE);
                    language_filter.insert(kind::JAVAENUM);
                }
                if (should_generate(folder_category::NAMESPACES)) {
                    language_filter.insert(kind::NAMESPACE);
                }
                if (should_generate(folder_category::MODULES)) {
                    language_filter.insert(kind::MODULE);
                }
                if (!language_filter.empty()) {
                    g.print(language_filter, {});
                }

                if (should_generate(folder_category::FILES)) {
                    g.print(INDEX_FILES_FILTER, {});
                }
                if (should_generate(folder_category::PAGES)) {
                    g.print(INDEX_PAGES_FILTER, {});
                }
                if (should_generate(folder_category::EXAMPLES)) {
                    g.print(INDEX_EXAMPLES_FILTER, {});
                }

                if (should_generate(folder_category::CLASSES)) {
                    g.print_index(
                        folder_category::CLASSES,
                        INDEX_CLASS_FILTER,
                        {});
                }
                if (should_generate(folder_category::NAMESPACES)) {
                    g.print_index(
                        folder_category::NAMESPACES,
                        INDEX_NAMESPACES_FILTER,
                        {});
                }
                if (should_generate(folder_category::MODULES)) {
                    g.print_index(
                        folder_category::MODULES,
                        INDEX_MODULES_FILTER,
                        {});
                }
                if (should_generate(folder_category::FILES)) {
                    g.print_index(
                        folder_category::FILES,
                        INDEX_FILES_FILTER,
                        {});
                }
                if (should_generate(folder_category::PAGES)) {
                    g.print_index(
                        folder_category::PAGES,
                        INDEX_PAGES_FILTER,
                        {});
                }
                if (should_generate(folder_category::EXAMPLES)) {
                    g.print_index(
                        folder_category::EXAMPLES,
                        INDEX_EXAMPLES_FILTER,
                        {});
                }
            }
        } else {
            std::cout << options.help() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
    catch (std::exception& e) {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }
}
