#include "ExceptionUtils.hpp"
#include "tinyxml2/tinyxml2.h"
#include <Doxybook/Exception.hpp>
#include <Doxybook/Xml.hpp>

Doxybook::Xml::Node::Node(tinyxml2::XMLNode* ptr) : ptr(ptr) {
}

Doxybook::Xml::Node Doxybook::Xml::Node::nextSibling() const {
    return Node(ptr->NextSibling());
}

Doxybook::Xml::Node Doxybook::Xml::Node::firstChild() const {
    return Node(ptr->FirstChild());
}

bool Doxybook::Xml::Node::hasText() const {
    return ptr->Value() != nullptr;
}

std::string Doxybook::Xml::Node::getText() const {
    return ptr->Value();
}

bool Doxybook::Xml::Node::isElement() const {
    return ptr->ToElement() != nullptr;
}

Doxybook::Xml::Element Doxybook::Xml::Node::asElement() const {
    return Element(ptr->ToElement());
}

Doxybook::Xml::Element::Element(tinyxml2::XMLElement* ptr) : ptr(ptr) {
}

void Doxybook::Xml::Element::allChildElements(const std::string& name, const ElementCallback& callback) const {
    auto found = firstChildElement(name);
    while (found) {
        callback(found);
        found = found.nextSiblingElement(name);
    }
}

Doxybook::Xml::Element Doxybook::Xml::Element::nextSiblingElement() const {
    return Element(ptr->NextSiblingElement());
}

Doxybook::Xml::Node Doxybook::Xml::Element::nextSibling() const {
    return Node(ptr->NextSibling());
}

Doxybook::Xml::Element Doxybook::Xml::Element::nextSiblingElement(const std::string& name) const {
    return Element(ptr->NextSiblingElement(name.c_str()));
}

Doxybook::Xml::Node Doxybook::Xml::Element::firstChild() const {
    return Node(ptr->FirstChild());
}

Doxybook::Xml::Element Doxybook::Xml::Element::firstChildElement() const {
    return Element(ptr->FirstChildElement());
}

Doxybook::Xml::Element Doxybook::Xml::Element::firstChildElement(const std::string& name) const {
    return Element(ptr->FirstChildElement(name.empty() ? nullptr : name.c_str()));
}

std::string Doxybook::Xml::Element::getAttr(const std::string& name) const {
    const auto str = ptr->Attribute(name.c_str());
    if (str == nullptr)
        throw EXCEPTION("Attribute {} does not exist in element {}", name, ptr->Name());
    return str;
}

std::string Doxybook::Xml::Element::getAttr(const std::string& name, const std::string& defaultValue) const {
    const auto str = ptr->Attribute(name.c_str());
    if (str == nullptr)
        return defaultValue;
    return str;
}

std::string Doxybook::Xml::Element::getName() const {
    return ptr->Name();
}

bool Doxybook::Xml::Element::hasText() const {
    return ptr->GetText() != nullptr;
}

std::string Doxybook::Xml::Element::getText() const {
    return ptr->GetText();
}

Doxybook::Xml::Node Doxybook::Xml::Element::asNode() const {
    return Node(ptr);
}

int Doxybook::Xml::Element::getLine() const {
    return ptr->GetLineNum();
}

const Doxybook::Xml& Doxybook::Xml::Element::getDocument() const {
    auto xml = reinterpret_cast<const Xml*>(ptr->GetDocument()->GetUserData());
    return *xml;
}

Doxybook::Xml::Xml(const std::string& path) : doc(new tinyxml2::XMLDocument) {
    this->path = path;
    const auto err = doc->LoadFile(path.c_str());
    if (err != tinyxml2::XMLError::XML_SUCCESS) {
        throw EXCEPTION("{}", doc->ErrorStr());
    }
    doc->SetUserData(this);
}

Doxybook::Xml::~Xml() = default;

Doxybook::Xml::Element Doxybook::Xml::firstChildElement(const std::string& name) const {
    return Element(doc->FirstChildElement(name.c_str()));
}
