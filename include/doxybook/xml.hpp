//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_XML_HPP
#define DOXYBOOK_XML_HPP

#include <functional>
#include <memory>
#include <string>

namespace tinyxml2 {
    class XMLNode;
    class XMLElement;
    class XMLDocument;
} // namespace tinyxml2

namespace doxybook {
    /// Represents and wraps an xml node
    class xml {
    public:
        class element;

        using element_callback = std::function<void(element&)>;

        /// An xml node
        class node {
        public:
            /// Constructor
            node() = default;

            /// Construct from a tinyxml node
            explicit node(tinyxml2::XMLNode* ptr);

            /// Destructor
            ~node() = default;

            /// Get next node
            node
            next_sibling() const;

            /// Get first child node
            node
            first_child() const;

            /// Check if node has text
            bool
            has_text() const;

            /// Get node text
            std::string
            get_text() const;

            /// Check if this is an element node
            bool
            is_element() const;

            /// Get node as an element
            element
            as_element() const;

            /// Check if node is valid
            operator bool() const {
                return ptr != nullptr;
            }

        private:
            tinyxml2::XMLNode* ptr{ nullptr };
        };

        /// The data of an element nodes
        class element {
        public:
            /// Constructor
            element() = default;

            /// Constructor from tinyxml element node
            explicit element(tinyxml2::XMLElement* ptr);

            /// Destructor
            ~element() = default;

            /// Execute callback for all child element with a given name
            void
            all_child_elements(
                std::string const& name,
                element_callback const& callback) const;

            /// Get as generic node
            node
            as_node() const;

            /// Get next sibling element
            element
            next_sibling_element() const;

            /// Get next sibling node
            node
            next_sibling() const;

            /// Get next sibling element with the specified name
            element
            next_sibling_element(std::string const& name) const;

            /// Get first child node
            node
            first_child() const;

            /// Get first child element node
            element
            first_child_element() const;

            /// Get first child element with the specified name
            element
            first_child_element(std::string const& name) const;

            /// Get line number in xml file
            int
            get_line() const;

            /// Get reference to document
            xml const&
            get_document() const;

            /// Get node attribute
            std::string
            get_attr(std::string const& name) const;

            /// Get node attribute or default value
            std::string
            get_attr(std::string const& name, std::string const& default_value)
                const;

            /// Get node name
            std::string
            get_name() const;

            /// Check if node has text
            bool
            has_text() const;

            /// Get node text
            std::string
            get_text() const;

            /// Check if element is valid
            operator bool() const {
                return ptr != nullptr;
            }

        private:
            tinyxml2::XMLElement* ptr{ nullptr };
        };

        /// Constructor
        explicit xml(std::string const& path);

        /// Destructor
        ~xml();

        /// Get first child element with the specified name
        element
        first_child_element(std::string const& name) const;

        /// Get document path
        std::string const&
        get_path() const {
            return path_;
        }

    private:
        std::unique_ptr<tinyxml2::XMLDocument> doc_;
        std::string path_;
    };
} // namespace doxybook

#endif