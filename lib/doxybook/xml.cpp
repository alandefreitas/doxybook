//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#include <doxybook/exception_utils.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/xml.hpp>
#include "tinyxml2/tinyxml2.h"

doxybook::xml::node::node(tinyxml2::XMLNode* ptr) : ptr(ptr) {}

doxybook::xml::node
doxybook::xml::node::next_sibling() const {
    return node(ptr->NextSibling());
}

doxybook::xml::node
doxybook::xml::node::first_child() const {
    return node(ptr->FirstChild());
}

bool
doxybook::xml::node::has_text() const {
    return ptr->Value() != nullptr;
}

std::string
doxybook::xml::node::get_text() const {
    return ptr->Value();
}

bool
doxybook::xml::node::is_element() const {
    return ptr->ToElement() != nullptr;
}

doxybook::xml::element
doxybook::xml::node::as_element() const {
    return element(ptr->ToElement());
}

doxybook::xml::element::element(tinyxml2::XMLElement* ptr) : ptr(ptr) {}

void
doxybook::xml::element::all_child_elements(
    std::string const& name,
    element_callback const& callback) const {
    auto found = first_child_element(name);
    while (found) {
        callback(found);
        found = found.next_sibling_element(name);
    }
}

doxybook::xml::element
doxybook::xml::element::next_sibling_element() const {
    return element(ptr->NextSiblingElement());
}

doxybook::xml::node
doxybook::xml::element::next_sibling() const {
    return node(ptr->NextSibling());
}

doxybook::xml::element
doxybook::xml::element::next_sibling_element(std::string const& name) const {
    return element(ptr->NextSiblingElement(name.c_str()));
}

doxybook::xml::node
doxybook::xml::element::first_child() const {
    return node(ptr->FirstChild());
}

doxybook::xml::element
doxybook::xml::element::first_child_element() const {
    return element(ptr->FirstChildElement());
}

doxybook::xml::element
doxybook::xml::element::first_child_element(std::string const& name) const {
    return element(
        ptr->FirstChildElement(name.empty() ? nullptr : name.c_str()));
}

std::string
doxybook::xml::element::get_attr(std::string const& name) const {
    auto const str = ptr->Attribute(name.c_str());
    if (str == nullptr) {
        throw EXCEPTION(
            "Attribute {} does not exist in element {}",
            name,
            ptr->Name());
    }
    return str;
}

std::string
doxybook::xml::element::get_attr(
    std::string const& name,
    std::string const& defaultValue) const {
    auto const str = ptr->Attribute(name.c_str());
    if (str == nullptr) {
        return defaultValue;
    }
    return str;
}

std::string
doxybook::xml::element::get_name() const {
    return ptr->Name();
}

bool
doxybook::xml::element::has_text() const {
    return ptr->GetText() != nullptr;
}

std::string
doxybook::xml::element::get_text() const {
    return ptr->GetText();
}

doxybook::xml::node
doxybook::xml::element::as_node() const {
    return node(ptr);
}

int
doxybook::xml::element::get_line() const {
    return ptr->GetLineNum();
}

doxybook::xml const&
doxybook::xml::element::get_document() const {
    auto xml = reinterpret_cast<const class xml*>(
        ptr->GetDocument()->GetUserData());
    return *xml;
}

doxybook::xml::xml(std::string const& path) : doc_(new tinyxml2::XMLDocument) {
    this->path_ = path;
    auto const err = doc_->LoadFile(path.c_str());
    if (err != tinyxml2::XMLError::XML_SUCCESS) {
        throw EXCEPTION("{}", doc_->ErrorStr());
    }
    doc_->SetUserData(this);
}

doxybook::xml::~xml() = default;

doxybook::xml::element
doxybook::xml::first_child_element(std::string const& name) const {
    return element(doc_->FirstChildElement(name.c_str()));
}
