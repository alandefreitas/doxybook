//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/default_templates.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/utils.hpp>
#include <spdlog/spdlog.h>
#include <fstream>

// clang-format off
static const std::vector<std::string> ALL_VISIBILITIES = {
    "public", "protected"
};
// clang-format on

static const std::string TEMPLATE_META = R"()";

// Like cppreference, we call the modules groups "libraries" because the term
// "modules" now has a specific meaning in C++. In the case of sub-libraries,
// we name the main library name and include the last module as the suffix.
// For instance:
// - Library:
// https://en.cppreference.com/w/cpp/utility#General-purpose_utilities
// - Sub-Library: https://en.cppreference.com/w/cpp/utility/functional
// The breadcrums are later responsible for the relationship between modules
static const std::string TEMPLATE_HEADER =
    R"(---
{% if exists("title") -%}
title: {{title}}
{% else if exists("name") -%}
title: {{name}}
{% endif -%}
{% if exists("summary") -%}
summary: {{summary}}
{% endif -%}
{% include "meta" %}
---

{% if exists("title") -%}
{% if exists("kind") and kind == "group" -%}
{% if exists("moduleBreadcrumbs") -%}
# {{ getOr(first(moduleBreadcrumbs), "title", "") }} Library: {{title}}
{% else -%}
# {{title}} Library
{% endif -%}
{% else -%}
# {{title}}
{% endif -%}
{% else if exists("kind") and kind != "page" -%}
# {{name}} {{title(kind)}} Reference
{% endif %}
)";

// Breadcrumbs with links referring to the module where this symbol is defined.
// This is somewhat similar to the top left links in
// https://en.cppreference.com/w/cpp/utility/functional
// If this is an entity that has a title, the breadcrumbs are followed by it
// so that we also have a reference to the current page.
// We finalize with the header where the symbols is located.
static const std::string TEMPLATE_BREADCRUMBS
    = R"({% if exists("moduleBreadcrumbs") -%}
{%- for module in moduleBreadcrumbs -%}
**[{{module.title}}]({{module.url}})**{% if not loop.is_last or exists("title") %} **/** {% endif -%}
{% endfor %}
{% if exists("title") -%}
{% if exists("url") -%}
**[{{ stripNamespace(title) }}]({{url}})**
{% else %}
{{title}}
{% endif %}
{% endif -%}

{% endif -%}

{% if exists("location") and kind != "namespace" -%}
<sup>Defined in header [`<{{ location.file }}>`]({{ sourceUrl(location.file) }})</sup>

{% endif -%}

)";

// The footer only includes the date. It's not inspired by cppreference
static const std::string TEMPLATE_FOOTER =
    R"(-------------------------------

<sub>Updated on {{date("%F")}}</sub>)";

// Describes the details about the symbol. It attempts to use the same
// structure for all kinds of symbol. Elements are in the same order
// as sections appear in cppreference.
static const std::string TEMPLATE_DETAILS =
    R"({% if exists("brief") and kind != "file" %}{{brief}}
{% endif -%}

{% if exists("templateParamsList") %}
**Template Parameters**

{% for param in templateParamsList %}  * **{{param.name}}** - {{param.text}}
{% endfor %}
{% endif -%}

{% if exists("paramList") %}
**Parameters**: 

{% for param in paramList %}  * **{{param.name}}** {{param.text}}
{% endfor %}
{% endif -%}

{% if exists("returnsList") %}
**Returns**: 

{% for param in returnsList %}  * **{{param.name}}** {{param.text}}
{% endfor %}
{% endif -%}

{% if exists("returns") %}
**Return**: {% if length(returns) == 1 %}{{first(returns)}}{% else %}

{% for item in returns %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("exceptionsList") %}
**Exceptions**: 

{% for param in exceptionsList %}  * **{{param.name}}** {{param.text}}
{% endfor %}
{% endif -%}

{% if exists("deprecated") %}
**Deprecated**:

{{deprecated}}
{% endif -%}

{% if exists("details") %}
{% if kind != "file" %}
**Description**
{% endif %}

{{details}}

{% endif -%}

{% if exists("see") %}
**See Also**: {% if length(see) == 1 %}{{first(see)}}{% else %}

{% for item in see %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("authors") %}
**Author**: {% if length(authors) == 1 %}{{first(authors)}}{% else %}

{% for item in authors %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("version") %}
**Version**: {% if length(version) == 1 %}{{first(version)}}{% else %}

{% for item in version %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("since") %}
**Since**: {% if length(since) == 1 %}{{first(since)}}{% else %}

{% for item in since %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("date") %}
**Date**: {% if length(date) == 1 %}{{first(date)}}{% else %}

{% for item in date %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("note") %}
**Note**: {% if length(note) == 1 %}{{first(note)}}{% else %}

{% for item in note %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("bugs") %}
**Bug**: {% if length(bugs) == 1 %}{{first(bugs)}}{% else %}

{% for item in bugs %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("tests") %}
**Test**: {% if length(tests) == 1 %}{{first(tests)}}{% else %}

{% for item in tests %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("todos") %}
**Todo**: {% if length(todos) == 1 %}{{first(todos)}}{% else %}

{% for item in todos %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("warning") %}
**Warning**: {% if length(warning) == 1 %}{{first(warning)}}{% else %}

{% for item in warning %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("pre") %}
**Precondition**: {% if length(pre) == 1 %}{{first(pre)}}{% else %}

{% for item in pre %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("post") %}
**Postcondition**: {% if length(post) == 1 %}{{first(post)}}{% else %}

{% for item in post %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("copyright") %}
**Copyright**: {% if length(copyright) == 1 %}{{first(copyright)}}{% else %}

{% for item in copyright %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("invariant") %}
**Invariant**: {% if length(invariant) == 1 %}{{first(invariant)}}{% else %}

{% for item in invariant %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("remark") %}
**Remark**: {% if length(remark) == 1 %}{{first(remark)}}{% else %}

{% for item in remark %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("attention") %}
**Attention**: {% if length(attention) == 1 %}{{first(attention)}}{% else %}

{% for item in attention %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("par") %}
{% for item in par %}
{% set parData=splitFirstLine(item) %}
**{{ parData.first }}**:

{{ parData.second }}
{% endfor %}
{% endif -%}

{% if exists("rcs") %}
**Rcs**: {% if length(rcs) == 1 %}{{first(rcs)}}{% else %}

{% for item in rcs %}  * {{item}}
{% endfor %}{% endif %}
{% endif -%}

{% if exists("reimplements") %}
**Reimplements**: [{{reimplements.fullname}}]({{reimplements.url}})

{% endif -%}

{% if exists("reimplementedBy") %}
**Reimplemented by**: {% for impl in reimplementedBy %}[{{impl.fullname}}]({{impl.url}}){% if not loop.is_last %}, {% endif %}{% endfor %}

{% endif -%}

{% if exists("inbody") %}
{{inbody}}

{% endif -%})";

// prepend condition for creating a table of inherited classes
static std::string
createTableIfInherited(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    if (inherited) {
        ss << "{%- if existsIn(base, \"" << key << "\") -%}\n";
        ss << "**" << title << "**"
           << "<sup><span style=\"color:green\">(inherited from "
              "[{{base.name}}]({{base.url}}))</span></sup>\n\n";
    } else {
        ss << "{%- if exists(\"" << key << "\") %}";
        ss << "## " << title << "\n";
    }

    return ss.str();
}

// Create table template for symbols like classes, where we need to strip the
// namespace
static std::string
createTableForClassStripLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    ss << "\n";
    ss << "|                | Name           |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";

    ss << "| {{child.kind}} | ";
    ss << "**[{{last(stripNamespace(child.name))}}]({{child.url}})** ";
    ss << "{% if existsIn(child, \"brief\") %}<br>{{child.brief}}{% endif %} "
          "|\n";

    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

// Create table template for symbols like types
static std::string
createTableForTypeLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    auto title1 = title;
    if (title1.find("Public ") == 0) {
        title1.erase(0, 7);
    }

    ss << "\n";
    ss << "| Member " << title1 << " | Definition           |\n";
    ss << "| -------------- | -------------- |\n";
    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";
    ss << "| **[{{stripNamespace(child.name)}}]({{child.url}})**";
    ss << "| {% if existsIn(child, \"brief\") %}";
    ss << "{{child.brief}}";
    ss << "{% else if existsIn(child, \"type\") %}";
    ss << "{% if child.type == \"__see_below__\" or startsWith(child.type, "
          "\"detail::\") %}";
    ss << "`/* see documentation below */`";
    ss << "{% else %}";
    ss << "`{{child.type}}`";
    ss << "{% endif %}";
    ss << "{% else %}";
    ss << "`{{child.name}}`";
    ss << "{% endif %}";
    ss << "<br> ";
    ss << "<sup><span style=\"color:green\">({{child.kind}})</span></sup>";
    ss << "|\n";
    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

// Create table template for symbols like functions that have overloads
static std::string
createTableForFunctionLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    auto title1 = title;
    if (title1.find("Public ") == 0) {
        title1.erase(0, 7);
    }

    std::string functions_var = (inherited ? "base." : "") + key;

    ss << "{% set overloadSections=groupBy(" << functions_var
       << ", \"section\") %}";

    ss << "{%- for section in overloadSections -%}\n";

    ss << "\n";
    ss << "| ";
    ss << "{% if not isEmpty(at(first(section), \"section\")) %}";
    ss << "{{ at(first(section), \"section\") }}";
    ss << "{% else %}";
    ss << "Member " << title1 << "{% endif %} | Description |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{%- for overloads in groupBy(section, \"name\")"
       << " -%}\n";
    ss << "{%- set child=first(overloads) -%}\n";
    ss << "| "
          // If constructor
          "**[{% if stripNamespace(name) == child.name "
          "%}(constructor)"
          // If destructor
          "{% else if \"~\" + stripNamespace(name) == child.name "
          "%}(destructor)"
          // Else, escaping "|"s
          "{% else %}{{replace(child.name, \"|\",\"\\\\|\")}}{% "
          "endif %}]"
          // Link, escaping "|"s
          "({{replace(child.url, \"|\", \"_1\")}})** ";
    // Properties
    ss << "{% if allOf(overloads, \"const\") %}<span "
          "style=\"color:green\">const</span>{% "
          "endif -%}\n";
    ss << "{% if allOf(overloads, \"override\") %} <span style=\"color:green\">"
          "override</span>{% endif -%}\n";
    ss << "{% if allOf(overloads, \"default\") %} <span "
          "style=\"color:green\">= "
          "default</span>{% endif -%}\n";
    ss << "{% if allOf(overloads, \"deleted\") %} <span style=\"color:red\">= "
          "delete</span>{% endif -%}\n";
    ss << "{% if allOf(overloads, \"pureVirtual\") %} = 0{% endif -%}\n";

    // Description
    // Render brief
    ss << "| {% if existsIn(child, \"brief\") %}"
          "{{replace(child.brief, \"|\", \"\\\\|\")}}<br>{% endif %}"
          // Render properties
          " <sup><span style=\"color:green\">("
          "{% if allOf(overloads, \"virtual\") %}virtual {% endif -%}"
       << "{{ getOr(child, \"kind\", \"\") }}{% if "
          "existsIn(child, \"templateParams\") %} "
          "template{% endif %})"
          "</span></sup> |\n";

    ss << "{% endfor %}\n{% endfor %}\n{% endif -%}\n\n";

    return ss.str();
}

// Create table template for symbols like attributes that only define aliases
static std::string
createTableForAttributeLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    ss << "\n";
    ss << "| Member " << title << "| Description    |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";

    // name
    ss << "| **[{{child.name}}]({{child.url}})** ";
    // description
    ss << "| {% if existsIn(child, \"brief\") %}";
    ss << "{{child.brief}}";
    ss << "{% else if existsIn(child, \"type\") %}";
    ss << "{% if child.typePlain == \"__see_below__\" or startsWith(child.typePlain, \"detail::\") %}";
    ss << "`/* see below */`";
    ss << "{% else %}";
    ss << "{% if child.type != child.typePlain %}{{child.type}}{% else %}`{{ child.typePlain }}`{% endif %}";
    ss << "{% endif %}";
    ss << "{% else %}";
    ss << "{{child.name}}";
    ss << "{% endif %}";
    ss << "<br> ";
    // properties
    ss << "<sup><span style=\"color:green\">(" << visibility << " {{ getOr(child, \"kind\", \"\") }}"
          "{% if existsIn(child, \"templateParams\") %} "
          "template{% endif %}"
          ")</span></sup> |\n";
    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

// Create table template for symbols like friends, that are only links
static std::string
createTableForFriendLike(
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    if (inherited) {
        ss << "{% if existsIn(base, \"" << key << "\") %}";
        ss << "**" << title;
        ss << " inherited from [{{base.name}}]({{base.url}})**\n";
    } else {
        ss << "{% if exists(\"" << key << "\") %}";
        ss << "## " << title << "\n";
    }

    ss << "\n";
    ss << "| " << title << " | Description     |\n";
    ss << "| --------------   | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}";

    ss << "| **[{{child.name}}]({{child.url}})**";
    ss << "| {{ getOr(child, \"brief\", refidBrief(child.refid)) }}";
    ss << "{% if existsIn(child, \"type\") %}";
    ss << "<br><sup><span style=\"color:green\">({{child.visibility}} friend "
          "{{child.type}})</span></sup>";
    ss << " {% endif %} |\n";
    ss << "{% endfor %}\n{% endif -%}\n\n";

    return ss.str();
}

// Create table template for public and protected
template <typename Fn>
static std::string
createForVisibilities(
    Fn& fn,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;
    for (auto const& visibility: ALL_VISIBILITIES) {
        ss << fn(
            visibility,
            doxybook::utils::title(visibility) + " " + title,
            visibility + doxybook::utils::title(key),
            inherited);
    }
    return ss.str();
}

// Create tables templates for each base class
static std::string
createBaseTable() {
    std::stringstream ss;
    ss << "{% for base in baseClasses -%}\n";
    ss << createForVisibilities(
        createTableForClassStripLike,
        "Classes",
        "classes",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(createTableForTypeLike, "Types", "types", true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Slots",
        "slots",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Signals",
        "signals",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Events",
        "events",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Functions",
        "functions",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForAttributeLike,
        "Properties",
        "properties",
        true);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForAttributeLike,
        "Attributes",
        "attributes",
        true);
    ss << createTableForFriendLike("Friends", "friends", true);
    ss << "{% endfor -%}";

    return ss.str();
}

// Tables with the inherited members of a class
static const std::string TEMPLATE_CLASS_MEMBERS_INHERITED_TABLES
    = createBaseTable();

static std::string
createTableForJavaEnumConstants(
    std::string const& title,
    std::string const& key) {
    std::stringstream ss;
    ss << "{%- if exists(\"" << key << "\") %}";
    ss << "## " << title << "\n";
    ss << "\n";
    ss << "| Enum constants | Description    |\n";
    ss << "| -------------- | -------------- |\n";
    ss << "{% for child in " << key << " -%}\n";
    ss << "| **[{{child.name}}]({{child.url}})**";
    ss << "| {% if existsIn(child, \"brief\") %}{{child.brief}}{% endif %} |\n";
    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

// Create table for all direct members of a class
static std::string
createMemberTable() {
    std::stringstream ss;

    ss << createForVisibilities(
        createTableForClassStripLike,
        "Classes",
        "classes",
        false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(createTableForTypeLike, "Types", "types", false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Slots",
        "slots",
        false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Signals",
        "signals",
        false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForFunctionLike,
        "Events",
        "events",
        false);
    ss << "\n\n\n\n";
    ss << createTableForJavaEnumConstants(
        "Enum Constants",
        "publicJavaenumconstants");
    ss << "\n\n\n\n";

    ss << createForVisibilities(
        createTableForFunctionLike,
        "Functions",
        "functions",
        false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForAttributeLike,
        "Properties",
        "properties",
        false);
    ss << "\n\n\n\n";
    ss << createForVisibilities(
        createTableForAttributeLike,
        "Attributes",
        "attributes",
        false);
    ss << "\n\n\n\n";
    ss << createTableForFriendLike("Friends", "friends", false);

    return ss.str();
}

// Table templates with the members of a class
static const std::string TEMPLATE_CLASS_MEMBERS_TABLES = createMemberTable();

// Create table for things that are like packages or namespaces
static std::string
createTableForNamespaceLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    ss << "\n";
    ss << "| Name           | Description    |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";

    ss << "| **[{{child.name}}]({{child.url}})** ";
    ss << "| {% if existsIn(child, \"brief\") %}{{child.brief}}{% endif %} "
          "|\n";

    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

// Table to list and summarize classes in nonclass pages
static std::string
createTableForClassLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    ss << "\n";
    ss << "| Classes        | Description    |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";
    ss << "| **[{{ stripNamespace(child.name) }}]({{child.url}})** "
          "| {{ getOr(child, \"brief\", child.name) }}<br> "
          "<sup><span style=\"color:green\">({{child.kind}})</span></sup> |\n";
    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

static std::string
createTableForDefineLike(
    std::string const& visibility,
    std::string const& title,
    std::string const& key,
    bool const inherited) {
    std::stringstream ss;

    ss << createTableIfInherited(visibility, title, key, inherited);

    ss << "\n";
    ss << "| Macros         | Description    |\n";
    ss << "| -------------- | -------------- |\n";

    ss << "{% for child in " << (inherited ? "base." : "") << key << " -%}\n";

    ss << "| **[{{child.name}}]({{child.url}})** ";
    ss << "{% if existsIn(child, \"type\") %}";
    ss << "({{child.type}})";
    ss << "{% endif %} ";
    ss << "{% if existsIn(child, \"params\") %}";
    ss << "({% for param in child.params %}";
    ss << "{{param.name}}";
    ss << "{% if existsIn(param, \"defval\") %}";
    ss << " = {{param.defval}}";
    ss << "{% endif %}";
    ss << "{% if not loop.is_last %}, {% endif %}";
    ss << "{% endfor %})";
    ss << "{% endif %} ";
    ss << "| {% if existsIn(child, \"brief\") %}";
    ss << "{{child.brief}}";
    ss << "{% endif %} |\n";

    ss << "{% endfor %}\n{% endif -%}\n";

    return ss.str();
}

static std::string
createNonMemberTables() {
    std::stringstream ss;

    // Child groups
    ss << R"({% if exists("groups") %}## Modules

| Modules        | Description    |
| -------------- | -------------- |
{% for child in groups -%}
| **[{{child.title}}]({{child.url}})** | {% if existsIn(child, "brief") %}{{child.brief}}{% endif %} |
{%- endfor %}
{% endif -%})";
    ss << "\n\n";

    ss << R"({% if exists("dirs") %}## Directories

| Directories    | Description    |
| -------------- | -------------- |
{% for child in dirs -%}
| **[{{child.title}}]({{child.url}})** | {% if existsIn(child, "brief") %}<br>{{child.brief}}{% endif %} |
{%- endfor %}
{% endif -%})";
    ss << "\n\n";

    ss << R"({% if exists("files") %}## Files

| Files           | Description    |
| -------------- | -------------- |
{% for child in files -%}
| **[{{child.title}}]({{child.url}})** | {% if existsIn(child, "brief") %}<br>{{child.brief}}{% endif %} |
{%- endfor %}
{% endif -%})";
    ss << "\n\n";

    ss << createTableForNamespaceLike(
        "public",
        R"({% if language == "java" %}Packages{% else %}Namespaces{% endif %})",
        "namespaces",
        false);
    ss << "\n\n";

    ss << createTableForClassLike("public", "Classes", "publicClasses", false);
    ss << "\n\n";

    ss << createTableForTypeLike("public", "Types", "publicTypes", false);
    ss << "\n\n";

    ss << createTableForFunctionLike("public", "Slots", "publicSlots", false);
    ss << "\n\n";

    ss << createTableForFunctionLike("public", "Signals", "publicSignals", false);
    ss << "\n\n";

    ss << createTableForFunctionLike(
        "public",
        "Functions",
        "publicFunctions",
        false);
    ss << "\n\n";

    ss << createTableForAttributeLike(
        "public",
        "Attributes",
        "publicAttributes",
        false);
    ss << "\n\n";

    ss << createTableForDefineLike("public", "Macros", "defines", false);
    ss << "\n\n";

    return ss.str();
}

// Template for the child members of entities that are not classes, such as
// file, group, and any other non-class
static const std::string TEMPLATE_NONCLASS_MEMBERS_TABLES
    = createNonMemberTables();

// This template describes a single child entity with its details on the
// parent's page. For instance, this is used at the end of a class page, after
// the tables, to describe each member function, alias, etc... with its details
static const std::string TEMPLATE_MEMBER_DETAILS =
    R"({% if exists("location") and not exists("hide_location")-%}
<sup>Defined in header [`<{{ location.file }}>`]({{ sourceUrl(location.file) }})</sup>
{% endif -%}

{% if kind in ["function", "slot", "signal", "event"] -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
{% if exists("templateParams") -%}
template <{% for param in templateParams %}{{param.typePlain}} {{param.name}}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %},
{% endif %}{% endfor %}>
{% endif -%}

{% if language == "java" %}{{visibility}} {% endif -%}
{% if static %}static {% endif -%}
{% if inline and language != "csharp" and language != "java" %}inline {% endif -%}
{% if explicit %}explicit {% endif -%}
{% if virtual %}virtual {% endif -%}

{% if exists("typePlain") %}{{typePlain}} {% endif %}{{name}}{% if length(params) > 0 -%}
(
{% for param in params %}    {{param.typePlain}} {{param.name}}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %},{% endif %}
{% endfor -%}
){% else -%}
(){% endif -%}

{% if const %} const{% endif -%}
{% if override %} override{% endif -%}
{% if default %} = default{% endif -%}
{% if deleted %} = delete{% endif -%}
{% if pureVirtual %} = 0{% endif %};
```{% endif -%}

{% if kind == "enum" -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
{% if static %}static {% endif %}{% if const %}const {% endif %}enum {% if strong %}class {% endif %}{{ name }};
```

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
{% for enumvalue in enumvalues %}| {{enumvalue.name}} | {% if existsIn(enumvalue, "initializer") -%}
{{replace(replace(enumvalue.initializer, "= ", ""), "|", "\\|"))}}{% endif -%}
| {{ getIf(enumvalue, "brief") }} {{ getIf(enumvalue, "details") }} |
{% endfor %}
{% endif -%}

{% if kind in ["variable", "property", "enum constant"] -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
{% if static %}static {% endif -%}
{% if exists("typePlain") %}{{typePlain}} {% endif -%}{{name}}{% if exists("initializer") %} {{initializer}}{% endif %};
```{% endif -%}

{% if kind == "typedef" -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
{{definition}};
```{% endif -%}

{% if kind == "using" -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
{% if exists("templateParams") -%}{% set allTemp = implode(templateParams, "typePlain", ", ") + implode(templateParams, "defvalPlain", "= ") %}
template <{% for param in templateParams %}{% if length(allTemp) > 60 %}
    {% endif %}{{param.typePlain}}{% if existsNonEmptyIn(param, "name") %} {{param.name}}{% endif %}{% if existsIn(param, "defvalPlain") %} = {{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %}, {% endif %}{% endfor %}>
{% endif -%}
using {{ name }} = {% if length(typePlain) + length(name) > 60 %}
    {% endif %}{% if typePlain == "__see_below__" or startsWith(typePlain, "detail::") %}/* see below */{% else %}{{ typePlain }}{% endif %};
```{% endif -%}

{% if kind == "friend" -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
friend
{% if exists("typePlain") %}{{typePlain}} {% endif -%}
{{name}}{% if exists("params") -%}
{% if length(params) > 0 -%}
({% for param in params %}{{ trimAll(param.typePlain) }}{% if existsNonEmptyIn(param, "name") %} {{param.name}}{% endif %}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %}, {% endif %}{% endfor -%}){% else if typePlain != "class" -%}
(){% endif %}{% endif %};
```{% endif -%}

{% if kind == "define" -%}
```{% if exists(language) %}{{language}}{% else %}cpp{% endif %}
#define {{name}}{% if exists("params") -%}
(
{% for param in params %}    {{param.name}}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %},
{% endif -%}
{% endfor %}
)
{% else %} {% endif -%}
{% if exists("initializer") %}{{initializer}}{% endif %}
```{% endif %}

{% include "details" -%})";

// This template describes a set of function overloads, similar to cppreference
// which does not include one documentation for each overload. This page is
// equivalent to member_details for this merged documentation.
// For each set of overloads, we merge the data so that repeated keys are
// aggregated and there's a single documentation for all functions:
// - String fields (such as brief) become arrays of strings
// - Object fields (such as params) become merged objects where the same key is
// overload
// - Arrays (such as pars) becomes extended array
// All redundant items are removed. Only unique values are rendered.
// If using this adaptation from doxygen, care must be taken to understand that
// keys and symbols with the same name in two function overloads must represent
// the same concept, or this documentation might look ambiguous.
static const std::string TEMPLATE_MEMBER_OVERLOADS_DETAILS =
    R"*****({% set headers=unique(pluck(pluck(overloads, "location"), "file")) %}
{% if length(headers) > 1 -%}
<sup>Defined in headers {% for header in headers %}[`<{{ header }}>`]({{ sourceUrl(header) }}){% if not loop.is_last %}, {% endif %}{% endfor %}</sup>
{%- else if length(headers) == 1 -%}
<sup>Defined in header [`<{{ first(headers) }}>`]({{ sourceUrl(first(headers)) }})</sup>
{% endif -%}

{% for overload in overloads %}
```{% if existsNonEmptyIn(overload, "language") %}{{overload.language}}{% else %}cpp{% endif %} {% if length(overloads) > 1 %} title="({{ loop.index1 }})" {% endif %}
{% if existsIn(overload, "templateParams") -%}
template <{% for param in overload.templateParams %}{{param.typePlain}}{% if not isEmpty(param.name) %} {{param.name}}{% endif %}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %}, {% endif %}{% endfor %}>
{% endif -%}

{% if overload.language == "java" %}{{visibility}} {% endif -%}
{% if overload.static %}static {% endif -%}
{% if overload.explicit %}explicit {% endif -%}
{% if overload.virtual %}virtual {% endif -%}

{%- if existsIn(overload, "typePlain") -%}
{%- if overload.typePlain in ["__implementation_defined__", "__see_below__", "__see_below__", "auto", "decltype(auto)"] or startsWith(overload.typePlain, "detail::") -%}
/* see return type below */{% else if overload.typePlain in ["decltype(auto) constexpr", "constexpr __see_below__"] or startsWith(overload.typePlain, "constexpr detail::") -%}
constexpr /* see return type below */{% else -%}
{{- overload.typePlain -}}
{%- endif %}
{% endif %}{{overload.name}}{% if length(overload.params) > 0 -%}
({% for param in overload.params %}{% if length(overload.argsString) > 60 %}
    {% endif %}{{ trimAll(param.typePlain) }}{% if not isEmpty(param.name) %} {{param.name}}{% endif %}{% if existsIn(param, "defvalPlain") %} ={{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %}, {% endif %}{% endfor -%}){% else -%}
(){% endif -%}

{% if overload.const %} const{% endif -%}
{% if overload.override %} override{% endif -%}
{% if contains(split(overload.argsString, " "), "noexcept") %} noexcept{% endif -%}
{% if overload.default %} = default{% endif -%}
{% if overload.deleted %} = delete{% endif -%}
{% if overload.pureVirtual %} = 0{% endif %};
```
{% endfor %}

{% set unique_briefs=unique(pluck(overloads, "brief")) %}
{% if not isEmpty(unique_briefs) %}
{% if length(unique_briefs) == 1 %}
{{ first(unique_briefs) }}
{% else %}
{% for overload in overloads %}{{ loop.index1 }}. {% if existsNonEmptyIn(overload, "brief") %}{{ overload.brief }}{% else %}{{ overload.name }}{% endif %}
{% endfor %}
{% endif %}
{% endif %}

{% set templateParamsList=uniqueBy(collapse(pluck(overloads, "templateParamsList")), "name") %}
{% if not isEmpty(templateParamsList) -%}
**Template Parameters**

{% for param in templateParamsList -%}
- **{{ param.name }}**{% if existsNonEmptyIn(param, "text") %} - {{ param.text }}{% endif %}
{% endfor %}
{% endif -%}

{% set paramList=uniqueBy(collapse(pluck(overloads, "paramList")), "name") %}
{% if not isEmpty(paramList) -%}
**Parameters**

{% for param in paramList -%}
- **{{ param.name }}**{% if existsNonEmptyIn(param, "text") %} - {{ param.text }}{% endif %}
{% endfor %}
{% endif -%}

{% set returns=unique(pluck(overloads, "returns")) %}
{% if not isEmpty(returns) -%}
**Return value**

{% if length(returns) == 1 -%}
{% set rs=first(returns) -%}
{% if length(rs) == 1 -%}
{{ first(rs) }}
{% else -%}
{% for r in rs %}- {{ r }}
{% endfor -%}
{% endif -%}
{%- else -%}
{% for rs in returns -%}
- ({{ loop.index1 }}) {% if length(rs) == 1 %}{{ first(rs) }}
{% else %}
{% for r in rs -%}
    - {{ r }}
{% endfor -%}
{% endif -%}
{% endfor -%}
{% endif -%}
{% endif -%}


{% set details=unique(pluck(overloads, "details")) %}
{% if not isEmpty(details) -%}
**Description**

{% if length(details) == 1 -%}
{{ first(details) }}
{%- else -%}
{% for overload in overloads %}
{% if existsNonEmptyIn(overload, "details") %}({{ loop.index1 }}) {{ overload.details }}{% endif %}


{% endfor -%}
{% endif -%}
{% endif -%}

{% set note=unique(pluck(overloads, "note")) %}
{% if not isEmpty(note) -%}
**Notes**

{% if length(note) == 1 -%}
{% set ns=first(note) -%}
{% if length(ns) == 1 -%}
{{ first(ns) }}
{% else -%}
{% for n in ns %}- {{ n }}
{% endfor -%}
{% endif -%}
{%- else -%}
{% for ns in note -%}
- ({{ loop.index1 }}) {% if length(ns) == 1 %}{{ first(ns) }}
{% else %}
{% for n in ns -%}
    - {{ n }}
{% endfor -%}
{% endif -%}
{% endfor -%}
{% endif -%}
{% endif -%}

{% set post=unique(pluck(overloads, "post")) %}
{% if not isEmpty(post) -%}
**Post-Conditions**

{% if length(post) == 1 -%}
{% set postStrs=first(post) -%}
{% if length(postStrs) == 1 -%}
{{ first(postStrs) }}
{% else -%}
{% for postStr in postStrs %}- {{ postStr }}
{% endfor -%}
{% endif -%}
{%- else -%}
{% for postStrs in post -%}
- ({{ loop.index1 }}) {% if length(postStrs) == 1 %}{{ first(postStrs) }}
{% else %}
{% for postStr in postStrs -%}
    - {{ postStr }}
{% endfor -%}
{% endif -%}
{% endfor -%}
{% endif -%}
{% endif -%}

{% set par=parsArrayToObj(pluck(overloads, "par")) %}
{% set parKeys=unique(keys(par)) %}

{% for parKey in parKeys %}
**{{ parKey }}**

{% set uniqueParTexts=unique(pluck(par, parKey)) %}
{% if length(uniqueParTexts) == 1 %}
{{ first(uniqueParTexts) }}
{% else %}
{% for p in par %}{% if existsNonEmptyIn(p, parKey) %}({{ loop.index1 }}) {{ trim(at(p, parKey)) }}

{% endif %}
{% endfor %}
{% endif %}
{% endfor %}

{% if not contains(parKeys, "Exception Safety") %}
{% set argsString=splitAll(unique(pluck(overloads, "argsString")), " ") %}

{% if not isEmpty(argsString) -%}
**Exception Safety**

{% if allContains(argsString, "noexcept") %}
Throws nothing.
{% else if noneContains(argsString, "noexcept") -%}
Basic exception guarantee.
{%- else -%}
{% for overload in overloads -%}
{% if contains(split(overload.argsString, " "), "noexcept") %}
- ({{ loop.index1 }}) Throws nothing.
{% else -%}
- ({{ loop.index1 }}) Basic exception guarantee.
{% endif -%}
{% endfor -%}
{% endif -%}
{% endif -%}
{% endif -%}

{% set uniqueSees=unique(collapse(pluck(overloads, "see"))) %}
{% if not isEmpty(uniqueSees) %}
**See Also**

{% for s in uniqueSees %}- {{ trim(s) }}
{% endfor %}
{% endif %}

)*****";

// The details of members of non classes, such as files and groups
static const std::string TEMPLATE_NONCLASS_MEMBERS_DETAILS =
    R"({% if exists("publicTypes") %}## Types

{% for child in publicTypes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif %}

{% if exists("publicFunctions") %}## Functions

{%- for overloads in groupBy(publicFunctions, "name") -%}
{%- set child=first(overloads) %}{% set child.overloads=overloads %}### {{child.kind}} {{child.name}}

{{ render("member_overloads_details", child) }}
{% endfor %}{% endif %}

{% if exists("publicAttributes") %}## Attributes

{% for child in publicAttributes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif %}
{% if exists("defines") %}## Macros

{% for child in defines %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif %})";

// The documentation details of members of classes
static const std::string TEMPLATE_CLASS_MEMBERS_DETAILS =
    R"({% if exists("publicTypes") %}## Public Types

{% for child in publicTypes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedTypes") %}## Protected Types

{% for child in protectedTypes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicSlots") %}## Public Slots

{% for child in publicSlots %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedSlots") %}## Protected Slots

{% for child in protectedSlots %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicSignals") %}## Public Signals

{% for child in publicSignals %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedSignals") %}## Protected Signals

{% for child in protectedSignals %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicEvents") %}## Public Events

{% for child in publicEvents %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedEvents") %}## Protected Events

{% for child in protectedEvents %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicJavaenumconstants") %}## Enum Constants Documentation

{% for child in publicJavaenumconstants %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicFunctions") %}## Public Functions

{%- for overloads in groupBy(publicFunctions, "name") -%}
{%- set child=first(overloads) %}{% set child.overloads=overloads %}### {{child.kind}} {{child.name}}

{{ render("member_overloads_details", child) }}
{% endfor %}{% endif %}

{% if exists("protectedFunctions") %}## Protected Functions

{%- for overloads in groupBy(protectedFunctions, "name") -%}
{%- set child=first(overloads) %}{% set child.overloads=overloads %}### {{child.kind}} {{child.name}}

{{ render("member_overloads_details", child) }}
{% endfor %}{% endif %}

{% if exists("publicProperties") %}## Public Property

{% for child in publicProperties %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedProperties") %}## Protected Property

{% for child in protectedProperties %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("publicAttributes") %}## Public Attributes

{% for child in publicAttributes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("protectedAttributes") %}## Protected Attributes

{% for child in protectedAttributes %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%}

{% if exists("friends") %}## Friends

{% for child in friends %}### {{child.kind}} {{child.name}}

{{ render("member_details", child) }}
{% endfor %}{% endif -%})";

// Any non-class
static const std::string TEMPLATE_KIND_NONCLASS =
    R"({% include "header" -%}

{% if exists("brief") %}> {{brief}}

{% endif %}

{% if exists("details") %}
{{details}}

{% endif -%}

{% include "breadcrumbs" -%}

{% include "nonclass_members_tables" -%}

{% include "nonclass_members_details" %}

{% include "footer" %})";

// Templates for classes
static const std::string TEMPLATE_KIND_CLASS =
    R"({% include "header" -%}

{% include "breadcrumbs" %}

```cpp
{% if exists("templateParams") -%}{% set allTemp = implode(templateParams, "typePlain", ", ") + implode(templateParams, "defvalPlain", "= ") %}
template <{% for param in templateParams %}{% if length(allTemp) > 60 %}
    {% endif %}{{param.typePlain}}{% if existsNonEmptyIn(param, "name") %} {{param.name}}{% endif %}{% if existsIn(param, "defvalPlain") %} = {{param.defvalPlain}}{% endif -%}
{% if not loop.is_last %}, {% endif -%}
{% endfor %}> {% endif %}
{% if kind == "interface" %}class{% else %}{{kind}}{% endif %} {{ stripNamespace(name) }};
```

{% include "details" %}

{%- if exists("baseClasses") %}**Inherits from** {% for child in baseClasses %}{% if existsIn(child, "url") %}[{{stripNamespace(child.name)}}]({{child.url}}){% else %}`{{child.name}}`{% endif %}{% if not loop.is_last %}, {% endif %}{% endfor %}

{% endif -%}

{%- if exists("derivedClasses") %}**Inherited by** {% for child in derivedClasses %}{% if existsIn(child, "url") %}[{{stripNamespace(child.name)}}]({{child.url}}){% else %}{{child.name}}{% endif %}{% if not loop.is_last %}, {% endif %}{% endfor %}

{% endif -%}

{%- include "class_members_tables" -%}

{% if hasAdditionalMembers %}## Additional inherited members

{% include "class_members_inherited_tables" %}
{% endif -%}

{% include "class_members_details" -%}

{% include "footer" %})";

// Main page for groups/libraries/modules
static const std::string TEMPLATE_KIND_GROUP =
    R"({% include "header" -%}

{% include "breadcrumbs" -%}

{% if exists("brief") %}{{brief}}{% endif %}{% if hasDetails %} [More...](#detailed-description){% endif %}

{% include "nonclass_members_tables" -%}

{% if hasDetails %}## Detailed Description

{% include "details" %}{% endif -%}

{% include "nonclass_members_details" -%}

{% include "footer" -%}
)";

// Main page for files
static const std::string TEMPLATE_KIND_FILE =
    R"({% include "header" -%}

{% if exists("brief") %}> {{brief}}{% endif %}

{% if kind == "file" %}
```cpp
#include <{{title}}>
```{% endif %}

{% include "nonclass_members_tables" -%}

{% if hasDetails %}## Description

{% include "details" %}{% endif -%}

{% include "nonclass_members_details" -%}

{% include "footer" %}
)";

// Main document for doxygen pages
static const std::string TEMPLATE_KIND_PAGE =
    R"({% include "header" %}

{% if exists("details") %}{{details}}{% endif %}

{% include "footer" %}
)";

// Main document for doxygen examples
static const std::string TEMPLATE_KIND_EXAMPLE =
    R"({% include "header" %}

{% if exists("details") %}{{details}}{% endif %}

{% include "footer" %}
)";

// An index of arbitrary entities and their child elements up to the 7-th level
static const std::string TEMPLATE_INDEX =
    R"(| {{ indexName }} |              |
|-----------|--------------|
{%- for child0 in children -%}
| [{{child0.title}}]({{child0.url}}) | {% if existsIn(child0, "brief") %}{{child0.brief}}{% endif %}<br><sup><span style="color:green">({% if child0.kind == "dir" %}directory{% else %}{{child0.kind}}{% endif %})</span></sup>|
{%- if existsIn(child0, "children") %}{% for child1 in child0.children -%}
| [{{last(stripNamespace(child1.title))}}]({{child1.url}}) | {% if existsIn(child1, "brief") %}{{child1.brief}}{% endif %}<br><sup><span style="color:green">({% if child1.kind == "dir" %}directory{% else %}{{child1.kind}}{% endif %})</span></sup> |
{%- if existsIn(child1, "children") %}{% for child2 in child1.children -%}
| [{{last(stripNamespace(child2.title))}}]({{child2.url}}) | {% if existsIn(child2, "brief") %}{{child2.brief}}{% endif %}<br><sup><span style="color:green">({% if child2.kind == "dir" %}directory{% else %}{{child2.kind}}{% endif %})</span></sup> |
{%- if existsIn(child2, "children") %}{% for child3 in child2.children -%}
| [{{last(stripNamespace(child3.title))}}]({{child3.url}}) | {% if existsIn(child3, "brief") %}{{child3.brief}}{% endif %}<br><sup><span style="color:green">({% if child3.kind == "dir" %}directory{% else %}{{child3.kind}}{% endif %})</span></sup> |
{%- if existsIn(child3, "children") %}{% for child4 in child3.children -%}
| [{{last(stripNamespace(child4.title))}}]({{child4.url}}) | {% if existsIn(child4, "brief") %}{{child4.brief}}{% endif %}<br><sup><span style="color:green">({% if child4.kind == "dir" %}directory{% else %}{{child4.kind}}{% endif %})</span></sup> |
{%- if existsIn(child4, "children") %}{% for child5 in child4.children -%}
| [{{last(stripNamespace(child5.title))}}]({{child5.url}}) | {% if existsIn(child5, "brief") %}{{child5.brief}}{% endif %}<br><sup><span style="color:green">({% if child5.kind == "dir" %}directory{% else %}{{child5.kind}}{% endif %})</span></sup> |
{%- if existsIn(child5, "children") %}{% for child6 in child5.children -%}
| [{{last(stripNamespace(child6.title))}}]({{child6.url}}) | {% if existsIn(child6, "brief") %}{{child6.brief}}{% endif %}<br><sup><span style="color:green">({% if child6.kind == "dir" %}directory{% else %}{{child6.kind}}{% endif %})</span></sup> |
{%- if existsIn(child6, "children") %}{% for child7 in child6.children -%}
| [{{last(stripNamespace(child7.title))}}]({{child7.url}}) | {% if existsIn(child7, "brief") %}{{child7.brief}}{% endif %}<br><sup><span style="color:green">({% if child7.kind == "dir" %}directory{% else %}{{child7.kind}}{% endif %})</span></sup> |
{%- endfor %}{% endif %}{% endfor %}{% endif %}{% endfor %}{% endif %}{% endfor %}{% endif %}{% endfor %}{% endif %}{% endfor %}{% endif %}{% endfor %}{% endif %}{% endfor -%}

)";

static const std::string TEMPLATE_INDEX_CLASSES =
    R"({% include "header" %}

{% set indexName="Class" %}
{% include "index" %}

{% include "footer" %}
)";

static const std::string TEMPLATE_INDEX_NAMESPACES =
    R"({% include "header" %}

{% set indexName="Namespace" %}
{% include "index" %}

{% include "footer" %}
)";

static const std::string TEMPLATE_INDEX_GROUPS =
    R"({% include "header" %}

{% set indexName="Library" %}
{% include "index" %}

{% include "footer" %}
)";

static const std::string TEMPLATE_INDEX_FILES =
    R"({% include "header" %}

{% set indexName="File" %}
{% include "index" %}

{% include "footer" %}
)";

static const std::string TEMPLATE_INDEX_PAGES =
    R"({% include "header" %}

{% set indexName="Page" %}
{% include "index" %}

{% include "footer" %}
)";

static const std::string TEMPLATE_INDEX_EXAMPLES =
    R"({% include "header" %}

{% set indexName="Example" %}
{% include "index" %}

{% include "footer" %}
)";

// clang-format off
std::unordered_map<std::string, doxybook::default_template> doxybook::default_templates = {
    {"meta", {
        TEMPLATE_META,
        {}
    }},
    {"header", {
        TEMPLATE_HEADER,
        {"meta"}
    }},
    {"footer", {
        TEMPLATE_FOOTER,
        {}
    }},
    {"details", {
        TEMPLATE_DETAILS,
        {}
    }},
    {"breadcrumbs", {
        TEMPLATE_BREADCRUMBS,
        {}
    }},
    {"member_details", {
        TEMPLATE_MEMBER_DETAILS,
        {"details"}
    }},
    {"member_overloads_details", {
        TEMPLATE_MEMBER_OVERLOADS_DETAILS,
        {"details"}
    }},
    {"class_members_tables", {
        TEMPLATE_CLASS_MEMBERS_TABLES,
        {}
    }},
    {"class_members_inherited_tables", {
        TEMPLATE_CLASS_MEMBERS_INHERITED_TABLES,
        {}
    }},
    {"class_members_details", {
        TEMPLATE_CLASS_MEMBERS_DETAILS,
        {"member_details", "member_overloads_details"}
    }},
    {"nonclass_members_tables", {
        TEMPLATE_NONCLASS_MEMBERS_TABLES,
        {}
    }},
    {"nonclass_members_details", {
        TEMPLATE_NONCLASS_MEMBERS_DETAILS,
        {"member_details", "member_overloads_details"}
    }},
    {"index", {
        TEMPLATE_INDEX,
        {}
    }},
    {"kind_nonclass", {
        TEMPLATE_KIND_NONCLASS,
        {
            "header",
            "breadcrumbs",
            "nonclass_members_tables",
            "nonclass_members_details",
            "footer"
        }
    }},
    {"kind_class",{
        TEMPLATE_KIND_CLASS,
        {
            "header",
            "breadcrumbs",
            "class_members_tables",
            "class_members_inherited_tables",
            "class_members_details",
            "footer"
        }
    }},
    {"kind_group", {
        TEMPLATE_KIND_GROUP,
        {
            "header",
            "breadcrumbs",
            "nonclass_members_tables",
            "nonclass_members_details",
            "footer"
        }
    }},
    {"kind_file", {
        TEMPLATE_KIND_FILE,
        {
            "header",
            "nonclass_members_tables",
            "nonclass_members_details",
            "footer"
        }
    }},
    {"kind_page", {
        TEMPLATE_KIND_PAGE,
        {"header", "details", "footer"}
    }},
    {"kind_example", {
        TEMPLATE_KIND_EXAMPLE,
        {"header", "details", "footer"}
    }},
    {"index_classes", {
        TEMPLATE_INDEX_CLASSES,
        {"header", "index", "footer"}
    }},
    {"index_namespaces", {
        TEMPLATE_INDEX_NAMESPACES,
        {"header", "index", "footer"}
    }},
    {"index_groups", {
        TEMPLATE_INDEX_GROUPS,
        {"header", "index", "footer"}
    }},
    {"index_files", {
        TEMPLATE_INDEX_FILES,
        {"header", "index", "footer"}
    }},
    {"index_pages", {
        TEMPLATE_INDEX_PAGES,
        {"header", "index", "footer"}
    }},
    {"index_examples", {
        TEMPLATE_INDEX_EXAMPLES,
        {"header", "index", "footer"}
    }}
};
// clang-format on

void
doxybook::save_default_templates(std::string const& path) {
    for (auto const& tmpl: default_templates) {
        auto const tmplPath = utils::join(path, tmpl.first + ".tmpl");
        spdlog::info("Creating default template {}", tmplPath);
        std::ofstream file(tmplPath);
        if (!file) {
            throw EXCEPTION("Failed to open file {} for writing", tmplPath);
        }
        file << tmpl.second.src;
    }
}
