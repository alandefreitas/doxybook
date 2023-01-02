//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/doxygen.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/json_converter.hpp>
#include <doxybook/utils.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <unordered_set>

static bool
is_function_type(const doxybook::type type) {
    switch (type) {
    case doxybook::type::FUNCTIONS:
    case doxybook::type::FRIENDS:
    case doxybook::type::SIGNALS:
    case doxybook::type::SLOTS:
    case doxybook::type::EVENTS:
        return true;
    default:
        return false;
    }
}

doxybook::json_converter::json_converter(
    const ::doxybook::config& config,
    const ::doxybook::doxygen& doxygen,
    text_printer const& plainPrinter,
    text_printer const& markdownPrinter)
    : config_(config)
    , doxygen_(doxygen)
    , plain_printer_(plainPrinter)
    , markdown_printer_(markdownPrinter) {}

nlohmann::json
doxybook::json_converter::convert(std::vector<std::string> const& vec) const {
    nlohmann::json json = nlohmann::json::array();
    for (auto const& item: vec) {
        json.push_back(item);
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(node::class_reference const& klass) const {
    nlohmann::json json;
    if (!klass.refid.empty()) {
        json["refid"] = klass.refid;
    }
    json["name"] = klass.name;
    json["visibility"] = to_str(klass.prot);
    json["virtual"] = to_str(klass.virt);
    json["external"] = klass.ptr == nullptr;
    if (klass.ptr) {
        json["url"] = klass.ptr->get_url();
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(
    std::vector<node::class_reference> const& item) const {
    nlohmann::json json = nlohmann::json::array();
    for (auto const& base: item) {
        json.push_back(convert(base));
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(node::source_location const& location) const {
    nlohmann::json json;
    json["file"] = location.file;
    json["line"] = location.line;
    json["column"] = location.column;
    if (location.body_start > 0) {
        json["bodyStart"] = location.body_start;
    }
    if (location.body_end > 0) {
        json["bodyEnd"] = location.body_end;
    }
    if (!location.body_file.empty()) {
        json["bodyFile"] = location.body_file;
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(node::param const& param) const {
    nlohmann::json json;
    json["type"] = param.type;
    json["typePlain"] = param.type_plain;
    json["name"] = param.name;
    if (!param.def_val.empty()) {
        json["defval"] = param.def_val;
    }
    if (!param.def_val_plain.empty()) {
        json["defvalPlain"] = param.def_val_plain;
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(node const& node) const {
    nlohmann::json json;
    if (node.get_kind() == kind::FILE) {
        if (node.get_parent()->get_kind() == kind::DIR) {
            json["name"] = node.get_parent()->get_name() + "/"
                           + node.get_name();
            json["title"] = json["name"];
        } else {
            json["name"] = node.get_name();
            json["title"] = json["name"];
        }
    } else {
        json["name"] = node.get_name();
        json["title"] = node.get_title();
        if (node.get_qualified_name().empty()) {
            json["qualifiedname"] = node.get_name();
        } else {
            json["qualifiedname"] = node.get_qualified_name();
        }
    }
    if (!node.is_structured() && node.get_kind() != kind::MODULE
        && node.get_kind() != kind::DEFINE && node.get_kind() != kind::FILE
        && node.get_kind() != kind::DIR)
    {
        json["fullname"] = node.get_parent()->get_name()
                           + "::" + node.get_name();
    } else {
        json["fullname"] = json["name"];
    }
    json["refid"] = node.get_refid();
    json["url"] = node.get_url();
    json["anchor"] = node.get_anchor();
    json["section"] = node.get_section();
    json["visibility"] = to_str(node.get_visibility());
    if (is_function_type(node.get_type())) {
        json["virtual"] = node.get_virtual() == virtual_category::VIRTUAL
                          || node.get_virtual()
                                 == virtual_category::PURE_VIRTUAL;
        json["pureVirtual"] = node.get_virtual()
                              == virtual_category::PURE_VIRTUAL;
    }
    if (!node.get_brief().empty()) {
        json["brief"] = utils::replace_newline(node.get_brief());
    }
    if (!node.get_summary().empty()) {
        json["summary"] = node.get_summary();
    }
    json["language"] = node.get_language();
    json["kind"] = to_str(node.get_kind());
    json["language"] = node.get_language();
    json["category"] = to_str(node.get_type());
    if (!node.get_base_classes().empty()) {
        json["baseClasses"] = convert(node.get_base_classes());
    }
    if (!node.get_derived_classes().empty()) {
        json["derivedClasses"] = convert(node.get_derived_classes());
    }

    // language specific fixups
    if (node.get_language() == "java") {
        json["name"] = utils::namespace_to_package(json["name"]);
        json["fullname"] = utils::namespace_to_package(json["fullname"]);
        json["title"] = utils::namespace_to_package(json["title"]);

        if (node.get_kind() == kind::NAMESPACE) {
            json["kind"] = "package";
        }
    }

    return json;
}

nlohmann::json
doxybook::json_converter::convert(
    node::parameter_list_item const& parameterItem) const {
    nlohmann::json json;
    json["name"] = parameterItem.name;
    json["text"] = parameterItem.text;
    return json;
}

nlohmann::json
doxybook::json_converter::convert(
    std::vector<node::parameter_list_item> const& parameterList) const {
    nlohmann::json json = nlohmann::json::array();
    for (auto const& item: parameterList) {
        json.push_back(convert(item));
    }
    return json;
}

nlohmann::json
doxybook::json_converter::convert(node const& node, node::data const& data)
    const {
    nlohmann::json json;
    if (!data.details.empty()) {
        json["details"] = data.details;
    }
    if (!data.in_body.empty()) {
        json["inbody"] = data.in_body;
    }
    if (!data.includes.empty()) {
        json["includes"] = data.includes;
    }
    if (!data.requiresclause.empty()) {
        json["requiresclause"] = data.requiresclause;
    }
    if (!data.type.empty()) {
        json["type"] = data.type;
    }
    json["definition"] = data.definition;
    if (!data.initializer.empty()) {
        json["initializer"] = data.initializer;
    }
    if (!data.type_plain.empty()) {
        json["typePlain"] = data.type_plain;
    }
    if (!data.see.empty()) {
        json["see"] = convert(data.see);
    }
    if (!data.returns.empty()) {
        json["returns"] = data.returns;
    }
    if (!data.authors.empty()) {
        json["authors"] = convert(data.authors);
    }
    if (!data.version.empty()) {
        json["version"] = data.version;
    }
    if (!data.since.empty()) {
        json["since"] = data.since;
    }
    if (!data.date.empty()) {
        json["date"] = data.date;
    }
    if (!data.note.empty()) {
        json["note"] = data.note;
    }
    if (!data.warning.empty()) {
        json["warning"] = data.warning;
    }
    if (!data.pre.empty()) {
        json["pre"] = data.pre;
    }
    if (!data.post.empty()) {
        json["post"] = data.post;
    }
    if (!data.copyright.empty()) {
        json["copyright"] = data.copyright;
    }
    if (!data.invariant.empty()) {
        json["invariant"] = data.invariant;
    }
    if (!data.remark.empty()) {
        json["remark"] = data.remark;
    }
    if (!data.attention.empty()) {
        json["attention"] = data.attention;
    }
    if (!data.par.empty()) {
        json["par"] = data.par;
    }
    if (!data.rcs.empty()) {
        json["rcs"] = data.rcs;
    }
    if (!data.todos.empty()) {
        json["todos"] = data.todos;
    }
    if (!data.bugs.empty()) {
        json["bugs"] = data.bugs;
    }
    if (!data.tests.empty()) {
        json["tests"] = data.tests;
    }
    if (!data.deprecated.empty()) {
        json["deprecated"] = data.deprecated;
    }
    if (node.get_kind() != kind::ENUMVALUE) {
        json["static"] = data.is_static;
        json["abstract"] = data.is_abstract;
        json["const"] = data.is_const;
        json["explicit"] = data.is_explicit;
        json["strong"] = data.is_strong;
        json["inline"] = data.is_inline;
        json["override"] = data.is_override;
    }
    if (is_function_type(node.get_type())) {
        json["argsString"] = data.args_string;
        json["default"] = data.is_default;
        json["deleted"] = data.is_deleted;
        json["params"] = nlohmann::json::array();
        for (auto const& param: data.params) {
            json["params"].push_back(convert(param));
        }
    }
    if (node.get_type() == type::DEFINES && !data.params.empty()) {
        json["params"] = nlohmann::json::array();
        for (auto const& param: data.params) {
            json["params"].push_back(convert(param));
        }
    }
    if (!data.template_params.empty()) {
        json["templateParams"] = nlohmann::json::array();
        for (auto const& param: data.template_params) {
            json["templateParams"].push_back(convert(param));
        }
        json["templateParamsString"] = data.template_params_string;
    }
    if (data.reimplements) {
        json["reimplements"] = convert(*data.reimplements);
    }
    if (!data.reimplemented_by.empty()) {
        auto arr = nlohmann::json::array();
        for (auto const& reimplementedBy: data.reimplemented_by) {
            arr.push_back(convert(*reimplementedBy));
        }
        json["reimplementedBy"] = std::move(arr);
    }
    if (!data.program_listing.empty()) {
        json["programlisting"] = data.program_listing;
    }
    if (!data.location.file.empty()) {
        json["location"] = convert(data.location);
    }
    if (!data.returns_list.empty()) {
        json["returnsList"] = convert(data.returns_list);
    }
    if (!data.exceptions_list.empty()) {
        json["exceptionsList"] = convert(data.exceptions_list);
    }
    if (!data.template_params_list.empty()) {
        json["templateParamsList"] = convert(data.template_params_list);
    }
    if (!data.param_list.empty()) {
        json["paramList"] = convert(data.param_list);
    }
    json["hasDetails"]
        = !data.details.empty() || !data.template_params.empty()
          || !data.in_body.empty() || !data.returns_list.empty()
          || !data.exceptions_list.empty() || !data.template_params_list.empty()
          || !data.param_list.empty() || !data.see.empty()
          || !data.returns.empty() || !data.bugs.empty() || !data.tests.empty()
          || !data.todos.empty() || !data.authors.empty()
          || !data.version.empty() || !data.since.empty() || !data.date.empty()
          || !data.note.empty() || !data.warning.empty() || !data.pre.empty()
          || !data.post.empty() || !data.copyright.empty()
          || !data.invariant.empty() || !data.remark.empty()
          || !data.attention.empty() || !data.par.empty() || !data.rcs.empty()
          || !data.deprecated.empty();
    return json;
}

nlohmann::json
doxybook::json_converter::get_as_json(node const& node) const {
    doxybook::node::load_data_result r = node.load_data(
        config_,
        plain_printer_,
        markdown_printer_,
        doxygen_.get_cache());
    node::data& data = std::get<0>(r);
    std::unordered_map<std::string, node::data>& childrenDataMap = std::get<1>(
        r);

    nlohmann::json json = convert(node);
    nlohmann::json dataJson = convert(node, data);
    json.insert(dataJson.begin(), dataJson.end());
    if (node.get_parent() != nullptr) {
        if (node.get_parent()->get_kind() != kind::INDEX) {
            std::list<const class node*> list;
            auto parent = node.get_parent();
            while (parent != nullptr) {
                list.push_front(parent);
                parent = parent->get_parent();
                if (parent && parent->get_kind() == kind::INDEX) {
                    parent = nullptr;
                }
            }
            nlohmann::json breadcrumbs = nlohmann::json::array();
            for (auto const& ptr: list) {
                breadcrumbs.push_back(convert(*ptr));
            }
            json["parentBreadcrumbs"] = std::move(breadcrumbs);
            json["parent"] = convert(*node.get_parent());
        } else {
            json["parent"] = nullptr;
        }
    }

    if (node.get_group() != nullptr) {
        std::list<const class node*> list;
        auto group = node.get_group();
        while (group != nullptr) {
            list.push_front(group);
            group = group->get_group();
            if (group && group->get_kind() == kind::INDEX) {
                group = nullptr;
            }
        }
        nlohmann::json breadcrumbs = nlohmann::json::array();
        for (auto const& ptr: list) {
            breadcrumbs.push_back(convert(*ptr));
        }
        json["module"] = convert(*node.get_group());
        json["moduleBreadcrumbs"] = std::move(breadcrumbs);
    }

    static const std::array<visibility, 3> ALL_VISIBILITIES = {
        visibility::PUBLIC,
        visibility::PROTECTED,
        visibility::PRIVATE
    };

    if (!node.get_children().empty()) {
        // Find all unique groups (for example, public attributes)
        std::unordered_set<type> uniqueTypes;
        std::unordered_map<type, std::list<std::shared_ptr<doxybook::node>>>
            children;
        for (auto const& child: node.get_children()) {
            auto it = children.find(child->get_type());
            if (it == children.end()) {
                it = children
                         .insert(std::make_pair(
                             child->get_type(),
                             std::list<std::shared_ptr<doxybook::node>>{}))
                         .first;
            }
            it->second.push_back(child);
            uniqueTypes.insert(child->get_type());
        }

        // public, protected, private...
        for (auto const& visibility: ALL_VISIBILITIES) {
            // attributes, functions, classes...
            for (auto const& type: uniqueTypes) {
                auto const key = to_str(visibility)
                                 + utils::title(to_str(type));
                auto arr = nlohmann::json::array();
                auto const range = children.find(type);
                for (auto const& child: range->second) {
                    if (!child->is_structured()
                        && child->get_kind() != kind::MODULE
                        && child->get_kind() != kind::DIR
                        && child->get_kind() != kind::FILE)
                    {
                        try {
                            auto it = childrenDataMap.find(
                                child.get()->get_refid());
                            if (it == childrenDataMap.end()) {
                                throw EXCEPTION(
                                    "Child {} not found in data map",
                                    child.get()->get_refid());
                            }
                            auto const& childData = it->second;
                            if (child->get_visibility() == visibility) {
                                auto childJson = convert(*child);
                                auto childDataJson = convert(*child, childData);
                                childJson.insert(
                                    childDataJson.begin(),
                                    childDataJson.end());

                                if (child->get_kind() == kind::ENUM) {
                                    auto enumvalues = nlohmann::json::array();
                                    for (auto const& enumvalue:
                                         child->get_children())
                                    {
                                        auto enumvalueJson = convert(
                                            *enumvalue);
                                        auto const eit = childrenDataMap.find(
                                            enumvalue.get()->get_refid());
                                        if (eit == childrenDataMap.end()) {
                                            throw EXCEPTION(
                                                "Child {} not found in data "
                                                "map",
                                                child.get()->get_refid());
                                        }
                                        auto const& enumvalueData = eit->second;
                                        auto enumvalueDataJson = convert(
                                            *enumvalue,
                                            enumvalueData);
                                        enumvalueJson.insert(
                                            enumvalueDataJson.begin(),
                                            enumvalueDataJson.end());
                                        enumvalues.push_back(
                                            std::move(enumvalueJson));
                                    }
                                    childJson["enumvalues"] = std::move(
                                        enumvalues);
                                }

                                arr.push_back(std::move(childJson));
                            }
                        }
                        catch (std::out_of_range& e) {
                            (void) e;
                            throw EXCEPTION(
                                "Refid {} this should never happen please "
                                "contact the author! Error: {}",
                                child->get_refid(),
                                e.what());
                        }
                    } else {
                        if (child->get_visibility() == visibility) {
                            arr.push_back(convert(*child));
                        }
                    }
                }

                if (!arr.empty()) {
                    if (type == type::FRIENDS) {
                        json["friends"] = std::move(arr);
                    } else if (type == type::NAMESPACES) {
                        json["namespaces"] = std::move(arr);
                    } else if (type == type::MODULES) {
                        json["groups"] = std::move(arr);
                    } else if (type == type::DIRS) {
                        json["dirs"] = std::move(arr);
                    } else if (type == type::FILES) {
                        json["files"] = std::move(arr);
                    } else if (type == type::DEFINES) {
                        json["defines"] = std::move(arr);
                    } else {
                        json[key] = std::move(arr);
                    }
                }
            }
        }
    }

    auto const alreadyExists = [&](std::string const& name) -> bool {
        for (const auto& child: node.get_children()) {
            if (child->get_name() == name) {
                return true;
            }
        }
        return false;
    };

    auto hasAdditionalMembers = false;
    if (!node.get_base_classes().empty()) {
        for (auto& base: json["baseClasses"]) {
            if (base["refid"].empty()) {
                continue;
            }

            try {
                auto const baseNode = doxygen_.get_cache().at(base["refid"]);
                auto [baseData, baseChildrenDataMap] = baseNode->load_data(
                    config_,
                    plain_printer_,
                    markdown_printer_,
                    doxygen_.get_cache());

                // Get unique types of this base class
                std::unordered_set<type> baseUniqueTypes;
                std::unordered_map<
                    type,
                    std::list<std::shared_ptr<doxybook::node>>>
                    baseChildren;
                for (auto const& child: baseNode->get_children()) {
                    if (alreadyExists(child->get_name())) {
                        continue;
                    }

                    auto it = baseChildren.find(child->get_type());
                    if (it == baseChildren.end()) {
                        it = baseChildren
                                 .insert(std::make_pair(
                                     child->get_type(),
                                     std::list<
                                         std::shared_ptr<doxybook::node>>{}))
                                 .first;
                    }

                    it->second.push_back(child);
                    baseUniqueTypes.insert(child->get_type());
                }

                // public, protected, private...
                for (auto const& visibility: ALL_VISIBILITIES) {
                    // attributes, functions, classes...
                    for (auto const& type: baseUniqueTypes) {
                        auto const key = to_str(visibility)
                                         + utils::title(to_str(type));
                        auto arr = nlohmann::json::array();
                        auto const range = baseChildren.find(type);
                        for (auto const& child: range->second) {
                            if (alreadyExists(child->get_name())) {
                                continue;
                            }

                            if (!child->is_structured()
                                && child->get_kind() != kind::MODULE)
                            {
                                try {
                                    auto const it = baseChildrenDataMap.find(
                                        child.get()->get_refid());
                                    if (it == baseChildrenDataMap.end()) {
                                        throw EXCEPTION(
                                            "Child {} not found in data map",
                                            child.get()->get_refid());
                                    }
                                    auto const& childData = it->second;
                                    if (child->get_visibility() == visibility) {
                                        auto childJson = convert(*child);
                                        auto childDataJson
                                            = convert(*child, childData);
                                        childJson.insert(
                                            childDataJson.begin(),
                                            childDataJson.end());

                                        if (child->get_kind() == kind::ENUM) {
                                            auto enumvalues = nlohmann::json::
                                                array();
                                            for (auto const& enumvalue:
                                                 child->get_children())
                                            {
                                                auto enumvalueJson = convert(
                                                    *enumvalue);
                                                auto const eit
                                                    = baseChildrenDataMap.find(
                                                        enumvalue.get()
                                                            ->get_refid());
                                                if (eit
                                                    == baseChildrenDataMap.end())
                                                {
                                                    throw EXCEPTION(
                                                        "Child {} not found in "
                                                        "data map",
                                                        child.get()
                                                            ->get_refid());
                                                }
                                                auto const& enumvalueData
                                                    = it->second;
                                                auto enumvalueDataJson = convert(
                                                    *enumvalue,
                                                    enumvalueData);
                                                enumvalueJson.insert(
                                                    enumvalueDataJson.begin(),
                                                    enumvalueDataJson.end());
                                                enumvalues.push_back(
                                                    std::move(enumvalueJson));
                                            }
                                            childJson["enumvalues"] = std::move(
                                                enumvalues);
                                        }

                                        arr.push_back(std::move(childJson));
                                    }
                                }
                                catch (std::out_of_range& e) {
                                    (void) e;
                                    throw EXCEPTION(
                                        "Refid {} this should never happen "
                                        "please contact the author!",
                                        child->get_refid());
                                }
                            } else {
                                if (child->get_visibility() == visibility) {
                                    arr.push_back(convert(*child));
                                }
                            }
                        }

                        if (!arr.empty()) {
                            hasAdditionalMembers = true;
                            if (type == type::FRIENDS) {
                                base["friends"] = std::move(arr);
                            } else if (type == type::NAMESPACES) {
                                base["namespaces"] = std::move(arr);
                            } else if (type == type::MODULES) {
                                base["groups"] = std::move(arr);
                            } else {
                                base[key] = std::move(arr);
                            }
                        }
                    }
                }
            }
            catch (std::out_of_range& e) {
                (void) e;
                throw EXCEPTION(
                    "Refid {} this should never happen please contact the "
                    "author!",
                    base["refid"].get<std::string>());
            }
            catch (std::exception& e) {
                throw EXCEPTION(
                    "Something went wrong while processing base class {} of {} "
                    "error {}",
                    base["refid"].get<std::string>(),
                    node.get_refid(),
                    e.what());
            }
        }
    }
    json["hasAdditionalMembers"] = hasAdditionalMembers;

    return json;
}
