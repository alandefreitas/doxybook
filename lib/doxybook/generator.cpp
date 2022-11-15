//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/exception_utils.hpp>
#include <doxybook/doxygen.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/generator.hpp>
#include <doxybook/path.hpp>
#include <doxybook/renderer.hpp>
#include <doxybook/utils.hpp>
#include <filesystem>
#include <fstream>
#include <inja/inja.hpp>
#include <spdlog/spdlog.h>

std::string
doxybook::generator::kind_to_template_name(const kind kind) {
    using namespace doxybook;
    switch (kind) {
    case kind::STRUCT:
        return config_.template_kind_struct;
    case kind::INTERFACE:
        return config_.template_kind_interface;
    case kind::UNION:
        return config_.template_kind_union;
    case kind::CLASS:
        return config_.template_kind_class;
    case kind::NAMESPACE:
        return config_.template_kind_namespace;
    case kind::MODULE:
        return config_.template_kind_group;
    case kind::DIR:
        return config_.template_kind_dir;
    case kind::FILE:
        return config_.template_kind_file;
    case kind::PAGE:
        return config_.template_kind_page;
    case kind::EXAMPLE:
        return config_.template_kind_example;
    case kind::JAVAENUM:
        return config_.template_kind_java_enum;
    default:
    {
        throw EXCEPTION(
            "Unrecognised kind {} please contant the author!",
            int(kind));
    }
    }
}

doxybook::generator::generator(
    const class config& config,
    const class doxygen& doxygen,
    const class json_converter& jc,
    std::optional<std::string> const& templatesPath)
    : config_(config)
    , doxygen_(doxygen)
    , json_converter_(jc)
    , renderer_(config, doxygen, jc, templatesPath) {}

void
doxybook::generator::summary(
    std::string const& inputFile,
    std::string const& outputFile,
    std::vector<summary_section> const& sections) {
    std::ifstream input(inputFile);
    if (!input) {
        throw EXCEPTION("File {} failed to open for reading", inputFile);
    }

    std::ofstream output(outputFile);
    if (!output) {
        throw EXCEPTION("File {} failed to open for writing", outputFile);
    }

    static auto const compare = [](char const* a, char const* b) {
        while (*a && *b) {
            if (*a++ != *b++) {
                return false;
            }
        }
        return true;
    };

    std::string tmpl(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());
    auto offset = tmpl.size();
    size_t indent = 0;
    for (size_t i = 0; i < tmpl.size(); i++) {
        auto const& c = tmpl[i];
        if (compare(&tmpl[i], "{{doxygen}}")) {
            offset = i;
            break;
        }
        if (c == ' ') {
            indent++;
        } else {
            indent = 0;
        }
    }

    std::stringstream ss;

    for (auto const& section: sections) {
        auto const name = type_to_index_title(config_, section.type);
        auto const path = type_to_index_name(config_, section.type) + "."
                          + config_.file_extension;
        ss << std::string(indent, ' ') << "* [" << name << "](" << path
           << ")\n";
        summary_recursive(
            ss,
            indent + 2,
            name,
            doxygen_.get_index(),
            section.filter,
            section.skip);
    }

    output << tmpl.substr(0, offset);

    output << ss.str().substr(indent);

    if (offset + ::strlen("{{doxygen}}") < tmpl.size()) {
        output << tmpl.substr(offset + ::strlen("{{doxygen}}"));
    }
}

void
doxybook::generator::summary_recursive(
    std::stringstream& ss,
    int const indent,
    std::string const& folderName,
    node const& node,
    filter_set const& filter,
    filter_set const& skip) {
    for (auto const& child: node.get_children()) {
        if (child->get_kind() == kind::PAGE
            && child->get_refid() == config_.main_page_name)
        {
            continue;
        }
        if (filter.find(child->get_kind()) != filter.end()) {
            if (skip.find(child->get_kind()) == skip.end()
                && should_include(*child))
            {
                ss << std::string(indent, ' ') << "* [" << child->get_name()
                   << "](" << folderName << "/" << child->get_refid()
                   << ".md)\n";
            }
            summary_recursive(ss, indent, folderName, *child, filter, skip);
        }
    }
}

void
doxybook::generator::print_recursively(
    doxybook::node const& parent,
    doxybook::generator::filter_set const& filter,
    const ::doxybook::generator::filter_set& skip) {
    for (auto const& child: parent.get_children()) {
        if (filter.find(child->get_kind()) != filter.end()) {
            if (skip.find(child->get_kind()) == skip.end()
                && should_include(*child))
            {
                nlohmann::json data = json_converter_.get_as_json(*child);

                std::string path;
                if (child->get_kind() == kind::PAGE
                    && child->get_refid() == config_.main_page_name)
                {
                    path = child->get_refid() + "." + config_.file_extension;
                } else if (config_.use_folders) {
                    path = path::join(
                        type_to_folder_name(config_, child->get_type()),
                        child->get_refid() + "." + config_.file_extension);
                } else {
                    path = child->get_refid() + "." + config_.file_extension;
                }

                renderer_.render(
                    kind_to_template_name(child->get_kind()),
                    path,
                    data);
            }
            print_recursively(*child, filter, skip);
        }
    }
}

void
doxybook::generator::json_recursively(
    node const& parent,
    filter_set const& filter,
    filter_set const& skip) {
    for (auto const& child: parent.get_children()) {
        if (filter.find(child->get_kind()) != filter.end()) {
            if (skip.find(child->get_kind()) == skip.end()
                && should_include(*child))
            {
                nlohmann::json data = json_converter_.get_as_json(*child);

                auto const path = path::
                    join(config_.output_dir, child->get_refid() + ".json");

                spdlog::info("Rendering {}", path);
                std::ofstream file(path);
                if (!file) {
                    throw EXCEPTION("File {} failed to open for writing", path);
                }

                file << data.dump(2);
            }
            json_recursively(*child, filter, skip);
        }
    }
}

void
doxybook::generator::print(filter_set const& filter, filter_set const& skip) {
    print_recursively(doxygen_.get_index(), filter, skip);
}

void
doxybook::generator::json(filter_set const& filter_, filter_set const& skip) {
    json_recursively(doxygen_.get_index(), filter_, skip);
}

void
doxybook::generator::manifest() {
    auto data = manifest_recursively(doxygen_.get_index());
    auto const path = path::join(config_.output_dir, "manifest.json");

    spdlog::info("Rendering {}", path);
    std::ofstream file(path);
    if (!file) {
        throw EXCEPTION("File {} failed to open for writing", path);
    }

    file << data.dump(2);
}

nlohmann::json
doxybook::generator::manifest_recursively(node const& node) {
    auto ret = nlohmann::json::array();
    for (auto const& child: node.get_children()) {
        if (!should_include(*child)) {
            continue;
        }

        nlohmann::json data;
        data["kind"] = to_str(child->get_kind());
        data["name"] = child->get_name();
        if (child->get_kind() == kind::MODULE) {
            data["title"] = child->get_title();
        }
        data["url"] = child->get_url();

        ret.push_back(std::move(data));

        auto test = manifest_recursively(*child);
        if (!test.empty()) {
            ret.back()["children"] = std::move(test);
        }
    }
    return ret;
}

void
doxybook::generator::print_index(
    const folder_category type,
    filter_set const& filter_,
    filter_set const& skip) {
    auto const path = type_to_index_name(config_, type) + "." + config_.file_extension;

    nlohmann::json data;
    data["children"]
        = build_index_recursively(doxygen_.get_index(), filter_, skip);
    data["title"] = type_to_index_title(config_, type);
    data["name"] = type_to_index_title(config_, type);
    renderer_.render(type_to_index_template(config_, type), path, data);
}

nlohmann::json
doxybook::generator::build_index_recursively(
    node const& node,
    filter_set const& filter,
    const ::doxybook::generator::filter_set& skip) {
    auto json = nlohmann::json::array();
    std::vector<const class node*> sorted;
    sorted.reserve(node.get_children().size());

    for (auto const& child: node.get_children()) {
        if (filter.find(child->get_kind()) != filter.end()
            && should_include(*child))
        {
            sorted.push_back(child.get());
        }
    }

    std::sort(
        sorted.begin(),
        sorted.end(),
        [](const class node* a, const class node* b) -> bool {
            return a->get_name() < b->get_name();
        });

    for (auto const& child: sorted) {
        auto data = json_converter_.convert(*child);

        auto test = build_index_recursively(*child, filter, skip);
        if (!test.empty()) {
            data["children"] = std::move(test);
        }

        json.push_back(std::move(data));
    }

    return json;
}

bool
doxybook::generator::should_include(node const& node) {
    switch (node.get_kind()) {
    case kind::FILE:
    {
        if (config_.files_filter.empty()) {
            return true;
        }

        auto const ext = std::filesystem::path(node.get_name())
                             .extension()
                             .string();
        auto const found = std::
            find(config_.files_filter.begin(), config_.files_filter.end(), ext);

        return found != config_.files_filter.end();
    }
    default:
    {
        return true;
    }
    }
}
