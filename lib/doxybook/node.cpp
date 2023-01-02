//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/node.hpp>
#include <doxybook/text_printer.hpp>
#include <doxybook/utils.hpp>
#include <doxybook/xml_text_parser.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_map>

class doxybook::node::Temp {
public:
    xml_text_parser::node brief;
};

static std::shared_ptr<doxybook::node>
findInCache(doxybook::node_cache_map& cache, std::string const& ref_id) {
    auto const found = cache.find(ref_id);
    if (found != cache.end()) {
        return found->second;
    } else {
        return nullptr;
    }
}

static std::shared_ptr<doxybook::node>
findOrCreate(
    std::string const& inputDir,
    doxybook::node_cache_map& cache,
    std::string const& ref_id,
    bool const isGroupOrFile,
    bool const allow_undocumented_macros) {
    auto found = findInCache(cache, ref_id);
    if (found) {
        if (found->is_empty()) {
            return doxybook::node::parse(
                cache,
                inputDir,
                found,
                isGroupOrFile,
                allow_undocumented_macros);
        } else {
            return found;
        }
    } else {
        return doxybook::node::parse(
            cache,
            inputDir,
            ref_id,
            isGroupOrFile,
            allow_undocumented_macros);
    }
}

std::shared_ptr<doxybook::node>
doxybook::node::parse(
    node_cache_map& cache,
    std::string const& inputDir,
    std::string const& refid,
    bool const isGroupOrFile,
    bool const allow_undocumented_macros) {
    assert(!refid.empty());
    auto const ptr = std::make_shared<node>(refid);
    return parse(cache, inputDir, ptr, isGroupOrFile, allow_undocumented_macros);
}

std::shared_ptr<doxybook::node>
doxybook::node::parse(
    node_cache_map& cache,
    std::string const& inputDir,
    std::shared_ptr<doxybook::node> const& ptr,
    bool const isGroupOrFile,
    bool const allow_undocumented_macros) {
    auto const ref_idPath = utils::join(inputDir, ptr->refid_ + ".xml");
    spdlog::info("Loading {}", ref_idPath);
    xml xml(ref_idPath);

    auto root = assert_child(xml, "doxygen");
    auto compounddef = assert_child(root, "compounddef");

    ptr->xml_path_ = ref_idPath;
    ptr->name_ = assert_child(compounddef, "compoundname").get_text();
    ptr->language_ = utils::normalize_language(
        compounddef.get_attr("language", ""));
    auto kind = to_enum_kind(compounddef.get_attr("kind"));
    ptr->kind_ = (ptr->language_ == "java" && kind == kind::ENUM) ?
                     kind::JAVAENUM :
                     kind;
    ptr->empty_ = false;
    cache.insert(std::make_pair(ptr->refid_, ptr));

    // Inner members such as functions
    auto sectiondef = compounddef.first_child_element("sectiondef");
    while (sectiondef) {
        auto memberdef = sectiondef.first_child_element("memberdef");
        while (memberdef) {
            auto const childKindStr = memberdef.get_attr("kind");
            auto const childRefid = memberdef.get_attr("id");
            auto const found = findInCache(cache, childRefid);
            auto const child = found ? found :
                                       node::parse(memberdef, childRefid);
            auto const definition = memberdef.first_child_element("definition");
            if (definition) {
                auto const defStr = definition.get_text();
                if (defStr.find("using ") == 0) {
                    child->kind_ = kind::USING;
                }
            }
            child->language_ = ptr->language_;
            auto sectiondefheader = sectiondef.first_child_element("header");
            if (sectiondefheader && sectiondefheader.has_text()) {
                child->section_ = sectiondefheader.get_text();
            }

            // Doxygen outputs Java enum values as variables with empty <type>
            auto typeElement = memberdef.first_child_element("type");
            bool hasTypeDefined = typeElement && typeElement.has_text();
            if (ptr->kind_ == kind::JAVAENUM && child->kind_ == kind::VARIABLE
                && !hasTypeDefined)
            {
                child->kind_ = kind::JAVAENUMCONSTANT;
                child->type_ = type::JAVAENUMCONSTANTS;
            }

            if (allow_undocumented_macros || child->kind_ != kind::DEFINE
                || !child->brief_.empty())
            {
                ptr->children_.push_back(child);
            }

            if (isGroupOrFile) {
                // Only update child's parent if this is a group and the member
                // has just been created (not in cache)
                if (!found) {
                    child->parent_ = ptr.get();
                }
            } else {
                // Only update child's parent if we are not processing
                // directories
                if (is_kind_language(ptr->kind_)
                    && is_kind_language(child->kind_))
                {
                    child->parent_ = ptr.get();
                }
            }
            memberdef = memberdef.next_sibling_element("memberdef");
        }
        sectiondef = sectiondef.next_sibling_element("sectiondef");
    }

    // A helper lambda to go through different sections and process children
    auto innerProcess = [&](xml::element& parent, std::string const& name) {
        parent.all_child_elements(name, [&](xml::element& e) {
            const auto childRefid = e.get_attr("refid");
            auto child = findOrCreate(
                inputDir,
                cache,
                childRefid,
                isGroupOrFile,
                allow_undocumented_macros);
            if (allow_undocumented_macros || child->kind_ != kind::DEFINE
                || !child->brief_.empty())
            {
                ptr->children_.push_back(child);
            }

            // Only update child's parent if we are not processing directories
            if (!isGroupOrFile
                || (isGroupOrFile && child->kind_ == kind::MODULE)
                || (isGroupOrFile && child->kind_ == kind::FILE)
                || (isGroupOrFile && child->kind_ == kind::DIR))
            {
                child->parent_ = ptr.get();
            }
        });
    };

    if (!isGroupOrFile) {
        ptr->parse_inheritance_info(compounddef);
    }

    ptr->parse_base_info(compounddef);

    auto parseSafely = [&](std::string const& innerName) {
        try {
            innerProcess(compounddef, innerName);
        }
        catch (std::exception& e) {
            spdlog::warn(
                "Failed to parse inner member of {} error: {}",
                innerName,
                e.what());
        }
    };

    parseSafely("innerclass");
    parseSafely("innerstruct");
    parseSafely("innernamespace");
    if (isGroupOrFile) {
        parseSafely("innergroup");
        parseSafely("innerdir");
        parseSafely("innerfile");
    }

    return ptr;
}

std::shared_ptr<doxybook::node>
doxybook::node::parse(xml::element& memberdef, std::string const& ref_id) {
    assert(!ref_id.empty());

    auto ptr = std::make_shared<node>(ref_id);
    ptr->name_ = assert_child(memberdef, "name").get_text();

    auto childQualifiedName = memberdef.first_child_element("qualifiedname");
    if (childQualifiedName) {
        ptr->qualified_name_ = childQualifiedName.get_text();
    } else {
        ptr->qualified_name_ = ptr->name_;
    }

    ptr->kind_ = to_enum_kind(memberdef.get_attr("kind"));
    ptr->empty_ = true;
    ptr->parse_base_info(memberdef);

    if (ptr->kind_ == kind::ENUM) {
        auto enumvalue = memberdef.first_child_element("enumvalue");
        while (enumvalue) {
            auto value = std::make_shared<node>(enumvalue.get_attr("id"));
            value->name_ = enumvalue.first_child_element("name").get_text();
            value->kind_ = kind::ENUMVALUE;
            value->empty_ = false;
            value->parent_ = ptr.get();
            value->parse_base_info(enumvalue);
            value->parse_base_info(enumvalue);
            ptr->children_.push_back(value);
            enumvalue = enumvalue.next_sibling_element("enumvalue");
        }
    }
    return ptr;
}

doxybook::xml::element
doxybook::node::assert_child(xml const& xml, std::string const& name) {
    auto child = xml.first_child_element(name);
    if (!child) {
        throw EXCEPTION(
            "Unable to find <{}> element in root element file {}",
            name,
            xml.get_path());
    }
    return child;
}

doxybook::xml::element
doxybook::node::assert_child(xml::element const& xml, std::string const& name) {
    auto child = xml.first_child_element(name);
    if (!child) {
        throw EXCEPTION(
            "Unable to find <{}> element in element <{}> line {} file {}",
            name,
            xml.get_name(),
            xml.get_line(),
            xml.get_document().get_path());
    }
    return child;
}

doxybook::node::node(std::string const& ref_id)
    : temp_(new Temp)
    , refid_(ref_id) {}

doxybook::node::~node() = default;

void
doxybook::node::parse_base_info(xml::element const& element) {
    auto const briefdescription = element.first_child_element(
        "briefdescription");
    if (briefdescription) {
        temp_->brief = xml_text_parser::parse_paras(briefdescription);
    } else {
        temp_->brief.type = xml_text_parser::node::type::PARAS;
    }
    visibility_ = to_enum_visibility(element.get_attr("prot", "public"));
    virt_ = to_enum_virtual(element.get_attr("virt", "non-virtual"));

    auto const title = element.first_child_element("title");
    if (title) {
        this->title_ = title.get_text();
    } else {
        this->title_ = this->name_;
    }

    type_ = kind_to_type(kind_);
}

void
doxybook::node::parse_inheritance_info(xml::element const& element) {
    element.all_child_elements("basecompoundref", [&](xml::element& e) {
        class_reference base;
        base.refid = e.get_attr("refid", "");
        base.name = e.get_text();
        base.virt = to_enum_virtual(e.get_attr("virt"));
        base.prot = to_enum_visibility(e.get_attr("prot"));
        base_classes_.push_back(base);
    });

    element.all_child_elements("derivedcompoundref", [&](xml::element& e) {
        class_reference derived;
        derived.refid = e.get_attr("refid", "");
        derived.name = e.get_text();
        derived.virt = to_enum_virtual(e.get_attr("virt"));
        derived.prot = to_enum_visibility(e.get_attr("prot"));
        derived_classes_.push_back(derived);
    });
}

std::string
doxybook::node::anchorMaker(const struct config& config, node const& node) {
    if (!node.is_structured() && node.kind_ != kind::MODULE) {
        return "#" + utils::to_lower(to_str(node.kind_)) + "-"
               + utils::safe_anchor_id(
                   node.name_,
                   config.replaceUnderscoresInAnchors);
    } else {
        return std::string("");
    }
};

std::string
doxybook::node::urlFolderMaker(const struct config& config, node const& node) {
    if (config.use_folders) {
        return config.base_url + type_to_folder_name(config, node.type_) + "/";
    } else {
        return config.base_url;
    }
};

std::string
doxybook::node::urlMaker(const struct config& config, node const& node) {
    switch (node.kind_) {
    case kind::STRUCT:
    case kind::CLASS:
    case kind::NAMESPACE:
    case kind::MODULE:
    case kind::DIR:
    case kind::FILE:
    case kind::PAGE:
    case kind::INTERFACE:
    case kind::EXAMPLE:
    case kind::UNION:
    case kind::JAVAENUM:
    {
        if (node.refid_ == config.main_page_name) {
            if (config.main_page_in_root) {
                return config.base_url;
            } else {
                return urlFolderMaker(config, node);
            }
        }
        return urlFolderMaker(config, node) + utils::strip_anchor(node.refid_)
               + config.link_suffix + anchorMaker(config, node);
    }
    case kind::ENUMVALUE:
    {
        auto const n = node.parent_->parent_;
        return urlFolderMaker(config, *n) + utils::strip_anchor(n->refid_)
               + config.link_suffix + anchorMaker(config, node);
    }
    default:
    {
        auto* n = node.parent_;
        if (node.group_) {
            n = node.group_;
        }
        return urlFolderMaker(config, *n) + utils::strip_anchor(n->refid_)
               + config.link_suffix + anchorMaker(config, node);
    }
    }
};

void
doxybook::node::finalize(
    config const& config,
    text_printer const& plainPrinter,
    text_printer const& markdownPrinter,
    node_cache_map const& cache) {
    // Sort children
    if (config.sort) {
        children_.sort([](std::shared_ptr<doxybook::node> const& a,
                          std::shared_ptr<doxybook::node> const& b) {
            return a->get_name() < b->get_name();
        });
    }

    // Fix group linking
    if (!group_ && refid_.find("group__") == 0) {
        auto const it = cache.find(utils::strip_anchor(refid_));
        if (it != cache.end() && it->second->get_kind() == kind::MODULE
            && it->second.get() != this)
        {
            group_ = it->second.get();
        }
    }

    if (temp_) {
        brief_ = markdownPrinter.print(temp_->brief);
        summary_ = plainPrinter.print(temp_->brief);
        temp_.reset();

        anchor_ = anchorMaker(config, *this);
        // can't create url for concept yet because it's a compound element with
        // no valid parent
        if (kind_ != kind::CONCEPT) {
            url_ = urlMaker(config, *this);
            if (config.link_lowercase) {
                url_ = utils::to_lower(url_);
            }
        }

        auto const findOrNull = [&](std::string const& ref_id) -> node const* {
            const auto it = cache.find(ref_id);
            if (it == cache.end()) {
                return nullptr;
            }
            return it->second.get();
        };

        for (auto& klass: base_classes_) {
            if (!klass.refid.empty()) {
                klass.ptr = findOrNull(klass.refid);
                if (!klass.ptr) {
                    klass.refid.clear();
                }
            }
        }

        for (auto& klass: derived_classes_) {
            if (!klass.refid.empty()) {
                klass.ptr = findOrNull(klass.refid);
                if (!klass.ptr) {
                    klass.refid.clear();
                }
            }
        }
    }

    base_classes_ = get_all_base_classes(cache);
}

doxybook::node::load_data_result
doxybook::node::load_data(
    config const& config,
    text_printer const& plainPrinter,
    text_printer const& markdownPrinter,
    node_cache_map const& cache) const {
    spdlog::info("Parsing {}", xml_path_);
    xml xml(xml_path_);

    auto root = assert_child(xml, "doxygen");
    auto compounddef = assert_child(root, "compounddef");

    auto data
        = load_data(config, plainPrinter, markdownPrinter, cache, compounddef);

    std::unordered_map<std::string, node::data> childrenData;

    auto sectiondef = compounddef.first_child_element("sectiondef");
    while (sectiondef) {
        auto memberdef = sectiondef.first_child_element("memberdef");
        while (memberdef) {
            auto const childRefid = memberdef.get_attr("id");
            std::shared_ptr<doxybook::node> childPtr;
            try {
                childPtr = this->find_child(childRefid);
            }
            catch (...) {
                memberdef = memberdef.next_sibling_element("memberdef");
                continue;
            }

            auto const it
                = childrenData
                      .insert(std::make_pair(
                          childPtr.get()->get_refid(),
                          load_data(
                              config,
                              plainPrinter,
                              markdownPrinter,
                              cache,
                              memberdef)))
                      .first;

            if (childPtr->kind_ == kind::TYPEDEF
                || childPtr->kind_ == kind::VARIABLE
                || childPtr->kind_ == kind::CONCEPT)
            {
                it->second.type += it->second.args_string;
                it->second.type_plain += it->second.args_string;
            }

            if (childPtr->kind_ == kind::ENUM) {
                auto enumvalue = memberdef.first_child_element("enumvalue");
                while (enumvalue) {
                    auto const enumvalueRefid = enumvalue.get_attr("id");
                    auto const enumvaluePtr = childPtr->find_child(
                        enumvalueRefid);
                    childrenData.insert(
                        std::make_pair<std::string, doxybook::node::data>(
                            std::string(enumvaluePtr.get()->get_refid()),
                            load_data(
                                config,
                                plainPrinter,
                                markdownPrinter,
                                cache,
                                enumvalue)));
                    enumvalue = enumvalue.next_sibling_element("enumvalue");
                }
            }

            memberdef = memberdef.next_sibling_element("memberdef");
        }
        sectiondef = sectiondef.next_sibling_element("sectiondef");
    }

    // load children data for concepts
    for (auto& c: children_) {
        if (c->kind_ != kind::CONCEPT) {
            continue;
        }
        auto const childRefid = c->refid_;
        class xml concept_xml(c->xml_path_);
        auto concept_root = assert_child(concept_xml, "doxygen");
        auto concept_compounddef = assert_child(concept_root, "compounddef");
        auto const it
            = childrenData
                  .insert(std::make_pair(
                      childRefid,
                      load_data(
                          config,
                          plainPrinter,
                          markdownPrinter,
                          cache,
                          concept_compounddef)))
                  .first;

        it->second.type += it->second.args_string;
        it->second.type_plain += it->second.args_string;
    }

    return { data, childrenData };
}

std::string_view
trim(std::string_view str) {
    auto p1 = str.find_first_not_of(" \n\r\t");
    if (p1 == std::string::npos) {
        p1 = 0;
    }
    auto p2 = str.find_last_not_of(" \n\r\t");
    if (p2 == std::string::npos) {
        p2 = str.size();
    } else {
        ++p2;
    }
    return str.substr(p1, p2 - p1);
};

doxybook::node::data
doxybook::node::load_data(
    config const& /*config*/,
    text_printer const& plainPrinter,
    text_printer const& markdownPrinter,
    node_cache_map const& cache,
    xml::element const& element) const {
    data data;

    bool is_concept = element.get_attr("kind", "") == "concept";
    data.is_abstract = element.get_attr("abstract", "no") == "yes";
    data.is_static = element.get_attr("static", "no") == "yes";
    data.is_strong = element.get_attr("strong", "no") == "yes";
    data.is_const = element.get_attr("const", "no") == "yes";
    data.is_explicit = element.get_attr("explicit", "no") == "yes";
    data.is_inline = element.get_attr("inline", "no") == "yes";

    auto locationElement = element.first_child_element("location");
    if (locationElement) {
        data.location.file = locationElement.get_attr("file", "");
        data.location.line = std::stoi(locationElement.get_attr("line", "0"));
        data.location.column = std::stoi(
            locationElement.get_attr("column", "0"));
        data.location.body_file = locationElement.get_attr("bodyfile", "");
        data.location.body_start = std::stoi(
            locationElement.get_attr("bodystart", "0"));
        data.location.body_end = std::stoi(
            locationElement.get_attr("bodyend", "0"));
    }

    auto argsString = element.first_child_element("argsstring");
    if (argsString && argsString.has_text()) {
        data.args_string = argsString.get_text();
    }
    auto definition = element.first_child_element("definition");
    if (definition && definition.has_text()) {
        data.definition = definition.get_text();
    }
    auto requiresclause = element.first_child_element("requiresclause");
    if (requiresclause && requiresclause.has_text()) {
        data.requiresclause = trim(requiresclause.get_text());
    }
    auto initializer = element.first_child_element("initializer");
    if (initializer) {
        data.initializer = plainPrinter.print(
            xml_text_parser::parse_para(initializer));
        if (is_concept && !data.initializer.empty()) {
            // find the namespace we should remove from the concept initializer
            std::string ns;
            if (kind_ == kind::NAMESPACE) {
                ns = name_;
            } else {
                std::string id = element.get_attr("id", "");
                if (!id.empty()) {
                    auto it = cache.find(id);
                    if (it != cache.end()
                        && it->second->parent_->kind_ == kind::NAMESPACE)
                    {
                        ns = it->second->parent_->name_;
                    }
                }
            }
            std::string r = "concept " + ns + "::";
            auto pos = data.initializer.find(r);
            if (pos != std::string::npos) {
                data.initializer.erase(pos + 8, ns.size() + 2);
            }
            // remove consecutive spaces since we're here
            std::size_t k = 1;
            for (std::size_t i = 1; i < data.initializer.size(); ++i) {
                if (data.initializer[i] == ' '
                    && data.initializer[i - 1] == ' ')
                {
                    continue;
                }
                data.initializer[k++] = data.initializer[i];
            }
            data.initializer.resize(k);
        }
    }

    auto const argsstring = element.first_child_element("argsstring");
    if (argsstring) {
        data.args_string = markdownPrinter.print(
            xml_text_parser::parse_para(argsstring));
        data.is_default = data.args_string.find("=default")
                          != std::string::npos;
        data.is_deleted = data.args_string.find("=delete") != std::string::npos;
        data.is_override = data.args_string.find(" override")
                           != std::string::npos;
    }

    auto const detaileddescription
        = assert_child(element, "detaileddescription");
    auto detailsParas = xml_text_parser::parse_paras(detaileddescription);
    if (kind_ != kind::PAGE) {
        for (auto& para: detailsParas.children) {
            for (auto it = para.children.begin(); it != para.children.end();) {
                switch (it->type) {
                case xml_text_parser::node::type::SIMPLESEC:
                {
                    if (it->extra == "see") {
                        data.see.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "return") {
                        data.returns.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "author") {
                        data.authors.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "authors") {
                        data.authors.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "version") {
                        data.version.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "since") {
                        data.since.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "date") {
                        data.date.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "note") {
                        data.note.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "warning") {
                        data.warning.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "pre") {
                        data.pre.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "post") {
                        data.post.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "copyright") {
                        data.copyright.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "invariant") {
                        data.invariant.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "remark") {
                        data.remark.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "attention") {
                        data.attention.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "par") {
                        data.par.push_back(markdownPrinter.print(*it));
                    } else if (it->extra == "rcs") {
                        data.rcs.push_back(markdownPrinter.print(*it));
                    }
                    it = para.children.erase(it);
                    break;
                }
                case xml_text_parser::node::type::XREFSECT:
                {
                    if (it->children.size() == 2
                        && it->children[0].type
                               == xml_text_parser::node::type::XREFTITLE
                        && it->children[1].type
                               == xml_text_parser::node::type::XREFDESCRIPTION)
                    {
                        if (it->extra == "bug") {
                            data.bugs.push_back(
                                markdownPrinter.print(it->children[1]));
                        } else if (it->extra == "test") {
                            data.tests.push_back(
                                markdownPrinter.print(it->children[1]));
                        } else if (it->extra == "todo") {
                            data.todos.push_back(
                                markdownPrinter.print(it->children[1]));
                        } else if (it->extra == "deprecated") {
                            data.deprecated = markdownPrinter.print(
                                it->children[1]);
                        }
                        it = para.children.erase(it);
                    }
                    break;
                }
                case xml_text_parser::node::type::PARAMETERLIST:
                {
                    auto const kind = it->extra;
                    std::vector<node::parameter_list_item>* dst = nullptr;
                    if (kind == "param") {
                        dst = &data.param_list;
                    } else if (kind == "exception") {
                        dst = &data.exceptions_list;
                    } else if (kind == "retval") {
                        dst = &data.returns_list;
                    } else if (kind == "templateparam") {
                        dst = &data.template_params_list;
                    } else {
                        break;
                    }

                    for (auto const& parameteritem: it->children) {
                        bool const is_valid_parameter_item
                            = parameteritem.children.size() == 2
                              && parameteritem.children[0].type
                                     == xml_text_parser::node::type::
                                         PARAMETERNAMELIST
                              && parameteritem.children[1].type
                                     == xml_text_parser::node::type::
                                         PARAMETERDESCRIPTION;
                        if (is_valid_parameter_item) {
                            parameter_list_item item;
                            item.name = markdownPrinter.print(
                                parameteritem.children[0]);
                            item.text = markdownPrinter.print(
                                parameteritem.children[1]);
                            dst->push_back(std::move(item));
                        }
                    }
                    it = para.children.erase(it);
                    break;
                }
                default:
                {
                    ++it;
                    break;
                }
                }
            }
        }
    }

    data.details = markdownPrinter.print(detailsParas);
    auto const inbodydescription = element.first_child_element(
        "inbodydescription");
    if (inbodydescription) {
        data.in_body = markdownPrinter.print(
            xml_text_parser::parse_paras(inbodydescription));
    }

    if (auto const includes = element.first_child_element("includes")) {
        if (includes.get_attr("local", "no") == "no") {
            data.includes = "<" + includes.get_text() + ">";
        } else {
            data.includes = "\"" + includes.get_text() + "\"";
        }
    }

    if (auto const templateparamlist = element.first_child_element(
            "templateparamlist"))
    {
        auto param = templateparamlist.first_child_element("param");
        while (param) {
            auto const type = param.first_child_element("type");
            if (!type) {
                continue;
            }

            auto const declname = param.first_child_element("declname");
            auto const defval = param.first_child_element("defval");
            struct param templateParam;
            if (declname) {
                templateParam.name = declname.get_text();
            }
            templateParam.type = markdownPrinter.print(
                xml_text_parser::parse_para(type));
            templateParam.type_plain = plainPrinter.print(
                xml_text_parser::parse_para(type));
            if (defval) {
                templateParam.def_val = markdownPrinter.print(
                    xml_text_parser::parse_para(defval));
                templateParam.def_val_plain = plainPrinter.print(
                    xml_text_parser::parse_para(defval));
            }
            if (!data.template_params.empty()) {
                data.template_params_string += ", ";
            }
            data.template_params_string += templateParam.type_plain;
            data.template_params_string += ' ';
            data.template_params_string += templateParam.name;
            if (!templateParam.def_val_plain.empty()) {
                data.template_params_string += " = ";
                data.template_params_string += templateParam.def_val_plain;
            }
            data.template_params.push_back(std::move(templateParam));
            param = param.next_sibling_element("param");
        }
    }

    if (auto const type = element.first_child_element("type")) {
        auto const typeParas = xml_text_parser::parse_para(type);
        data.type = markdownPrinter.print(typeParas);
        data.type_plain = plainPrinter.print(typeParas);
        if (data.type.find("friend ") == 0) {
            data.type = data.type.substr(7);
        }
        if (data.type_plain.find("friend ") == 0) {
            data.type_plain = data.type_plain.substr(7);
        }

        if (this->kind_ == kind::TYPEDEF || this->kind_ == kind::VARIABLE
            || this->kind_ == kind::CONCEPT)
        {
            data.type += data.args_string;
            data.type_plain += data.args_string;
        }
    }

    // workaround for a bug in doxygen, which includes
    // part of the requiresclause in the type
    // requires '<>::value' 'void'
    // becomes:
    // requires '<>' and type '::value void'
    if (!data.requiresclause.empty() && !data.type.empty()
        && !data.type_plain.empty())
    {
        std::string_view typesv(data.type);
        std::string_view type_plainsv(data.type_plain);
        if (typesv.substr(0, 2) == "::" && type_plainsv.substr(0, 2) == "::") {
            auto pend1 = typesv.find(' ');
            auto pend2 = type_plainsv.find(' ');
            if (pend1 != std::string_view::npos
                && pend2 != std::string_view::npos)
            {
                // move prefix to requiresclause
                std::string_view prefix = typesv.substr(0, pend1);
                data.requiresclause += prefix;
                data.type = trim(typesv.substr(pend1));
                data.type_plain = trim(type_plainsv.substr(pend2));
            }
        }
    }

    auto param = element.first_child_element("param");
    while (param) {
        struct param p;
        auto const paramType = param.first_child_element("type");
        auto const name = param.first_child_element("declname");
        auto const defname = param.first_child_element("defname");
        auto const defval = param.first_child_element("defval");
        auto const arr = param.first_child_element("array");
        if (paramType) {
            auto const typeParas = xml_text_parser::parse_para(paramType);
            p.type = markdownPrinter.print(typeParas);
            p.type_plain = plainPrinter.print(typeParas);
        }
        if (name) {
            p.name = markdownPrinter.print(xml_text_parser::parse_para(name));
        } else if (defname) {
            p.name = markdownPrinter.print(
                xml_text_parser::parse_para(defname));
        }
        if (arr) {
            p.name += arr.get_text();
        }
        if (defval) {
            auto const defvalParas = xml_text_parser::parse_para(defval);
            p.def_val = markdownPrinter.print(defvalParas);
            p.def_val_plain = plainPrinter.print(defvalParas);
        }
        param = param.next_sibling_element("param");
        data.params.push_back(std::move(p));
    }

    if (auto reimplements = element.first_child_element("reimplements")) {
        auto const ref_id = reimplements.get_attr("refid", "");
        if (!ref_id.empty()) {
            data.reimplements = cache.at(ref_id).get();
        }
    }

    if (auto reimplementedby = element.first_child_element("reimplementedby")) {
        while (reimplementedby) {
            auto const ref_id = reimplementedby.get_attr("refid", "");
            if (!ref_id.empty()) {
                data.reimplemented_by.push_back(cache.at(ref_id).get());
            }
            reimplementedby = reimplementedby.next_sibling_element(
                "reimplementedby");
        }
    }

    if (auto const programlisting = element.first_child_element(
            "programlisting"))
    {
        data.program_listing = plainPrinter.print(
            xml_text_parser::parse_paras(programlisting),
            language_);
    }

    return data;
}

std::shared_ptr<doxybook::node>
doxybook::node::find_child(std::string const& ref_id) const {
    for (auto const& ptr: children_) {
        if (ptr->refid_ == ref_id) {
            return ptr;
        }
    }

    throw EXCEPTION("Refid {} not found in {}", ref_id, this->refid_);
}

std::shared_ptr<doxybook::node>
doxybook::node::find(std::string const& ref_id) const {
    auto test = find_recursively(ref_id);
    if (!test) {
        throw EXCEPTION("Refid {} not found in {}", ref_id, this->refid_);
    }
    return test;
}

std::shared_ptr<doxybook::node>
doxybook::node::find_recursively(std::string const& ref_id) const {
    for (auto it = children_.begin(); it != children_.end(); ++it) {
        if (it->get()->refid_ == ref_id) {
            return *it;
        }
        auto test = it->get()->find_recursively(ref_id);
        if (test) {
            return test;
        }
    }
    return nullptr;
}

std::vector<doxybook::node::class_reference>
doxybook::node::get_all_base_classes(node_cache_map const& cache) {
    std::list<class_reference> newTemp;
    for (auto& base: base_classes_) {
        newTemp.push_back(base);
    }

    for (auto& base: newTemp) {
        if (!base.refid.empty() && !base.ptr) {
            auto found = cache.at(base.refid);
            base.ptr = found.get();
        }

        if (base.ptr) {
            for (auto const& newBase:
                 const_cast<node*>(base.ptr)->get_all_base_classes(cache))
            {
                auto test = std::find_if(
                    newTemp.begin(),
                    newTemp.end(),
                    [&](class_reference& e) {
                    return e.refid == newBase.refid;
                    });

                if (test == newTemp.end()) {
                    newTemp.push_back(newBase);
                }
            }
        }
    }

    std::vector<class_reference> result;
    for (auto& base: newTemp) {
        result.push_back(base);
    }
    return result;
}
