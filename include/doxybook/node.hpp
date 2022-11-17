//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_NODE_HPP
#define DOXYBOOK_NODE_HPP

#include <doxybook/enums.hpp>
#include <doxybook/xml.hpp>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace doxybook {
    class text_printer;
    class node;
    struct config;

    /// A map of nodes associated to a string
    using node_cache_map = std::
        unordered_map<std::string, std::shared_ptr<node>>;

    /// A doxygen node
    class node {
    public:
        /// A reference to a class
        /**
         * These are usually used to represent base and derived classes
         */
        struct class_reference {
            std::string name;
            std::string refid;
            visibility prot;
            virtual_category virt;
            node const* ptr{ nullptr };
        };

        /// Source code location
        struct source_location {
            std::string file;
            int line{ 0 };
            int column{ 0 };
            std::string body_file;
            int body_start{ 0 };
            int body_end{ 0 };
        };

        /// A parameter
        /**
         * This is used for parameters and template parameters.
         */
        struct param {
            std::string type;
            std::string type_plain;
            std::string name;
            std::string def_val;
            std::string def_val_plain;
        };

        /// An item in a list of parameters
        /**
         * These could be used for parameters, return values, template
         * parameters, and exceptions.
         */
        struct parameter_list_item {
            std::string name;
            std::string text;
        };

        /// The data in a doxygen node
        struct data {
            std::vector<class_reference> base_classes;
            std::string definition;
            std::string args_string;
            std::string initializer;
            std::vector<class_reference> derived_classes;
            bool is_abstract{ false };
            bool is_static{ false };
            bool is_const{ false };
            bool is_explicit{ false };
            bool is_strong{ false };
            bool is_inline{ false };
            bool is_default{ false };
            bool is_deleted{ false };
            bool is_override{ false };
            source_location location;
            std::string details;
            std::string in_body;
            std::string includes;
            std::string type;
            std::string type_plain;
            std::string deprecated;
            std::vector<param> params;
            std::vector<param> template_params;
            std::vector<std::string> see;
            std::vector<std::string> returns;
            std::vector<std::string> authors;
            std::vector<std::string> version;
            std::vector<std::string> since;
            std::vector<std::string> date;
            std::vector<std::string> note;
            std::vector<std::string> warning;
            std::vector<std::string> pre;
            std::vector<std::string> post;
            std::vector<std::string> copyright;
            std::vector<std::string> invariant;
            std::vector<std::string> remark;
            std::vector<std::string> attention;
            std::vector<std::string> par;
            std::vector<std::string> rcs;
            std::vector<std::string> bugs;
            std::vector<std::string> tests;
            std::vector<std::string> todos;
            std::vector<node::parameter_list_item> param_list;
            std::vector<node::parameter_list_item> returns_list;
            std::vector<node::parameter_list_item> template_params_list;
            std::vector<node::parameter_list_item> exceptions_list;
            node const* reimplements{ nullptr };
            std::vector<node const*> reimplemented_by;
            std::string program_listing;
        };

        /// Parse root xml objects (classes, structs, etc)
        static std::shared_ptr<node>
        parse(
            node_cache_map& cache,
            std::string const& input_dir,
            std::string const& refid,
            bool is_group_or_file,
            bool const allow_undocumented_macros);

        /// Parse objects under the specified node
        static std::shared_ptr<node>
        parse(
            node_cache_map& cache,
            std::string const& input_dir,
            std::shared_ptr<node> const& ptr,
            bool is_group_or_file,
            bool const allow_undocumented_macros);

        /// Parse member xml objects (functions, enums, etc)
        static std::shared_ptr<node>
        parse(xml::element& member_def, std::string const& ref_id);

        /// Constructor
        /**
         * The constructor will only store the refid and an empty temporary
         * node.
         *
         * @param refid Node id
         */
        explicit node(std::string const& refid);

        /// Destructor
        ~node();

        /// Find a node by refid
        std::shared_ptr<node>
        find(std::string const& refid) const;

        /// Find an immediate child node
        std::shared_ptr<node>
        find_child(std::string const& refid) const;

        /// Check if node represents a structured type
        bool
        is_structured() const {
            return is_kind_structured(kind_);
        }

        /// Check if node represents a language feature
        bool
        is_language() const {
            return is_kind_language(kind_);
        }

        /// Check if node represents a file or directory
        bool
        is_file_or_dir() const {
            return is_kind_file(kind_);
        }

        /// Return the kind of node
        kind
        get_kind() const {
            return kind_;
        }

        /// Return the node language
        std::string
        get_language() const {
            return language_;
        }

        /// Return the node type
        type
        get_type() const {
            return type_;
        }

        /// Return the node refid
        std::string const&
        get_refid() const {
            return refid_;
        }

        /// Return the qualified name
        std::string const&
        get_qualified_name() const {
            return qualified_name_;
        }

        /// Return the node name
        std::string const&
        get_name() const {
            return name_;
        }

        /// Return the node parent
        node const*
        get_parent() const {
            return parent_;
        }

        /// Return the node group
        node const*
        get_group() const {
            return group_;
        }

        /// Check if the node is empty
        bool
        is_empty() const {
            return empty_;
        }

        /// Return all child nodes
        std::list<std::shared_ptr<node>> const&
        get_children() const {
            return children_;
        }

        /// Return the node xml_path
        std::string const&
        get_xml_path() const {
            return xml_path_;
        }

        /// Return the node brief
        std::string const&
        get_brief() const {
            return brief_;
        }

        /// Return the node summary
        std::string const&
        get_summary() const {
            return summary_;
        }

        /// Return the node title
        std::string const&
        get_title() const {
            return title_;
        }

        /// Return the node visibility
        visibility
        get_visibility() const {
            return visibility_;
        }

        /// Return the node virtual category
        virtual_category
        get_virtual() const {
            return virt_;
        }

        /// Return the node base classes
        std::vector<class_reference> const&
        get_base_classes() const {
            return base_classes_;
        }

        /// Return the node derived classes
        std::vector<class_reference> const&
        get_derived_classes() const {
            return derived_classes_;
        }

        /// Return the node url
        std::string const&
        get_url() const {
            return url_;
        }

        /// Return the node anchor
        std::string const&
        get_anchor() const {
            return anchor_;
        }

        /// Print the node contents to text and markdown
        void
        finalize(
            config const& config,
            text_printer const& plain_printer,
            text_printer const& markdown_printer,
            node_cache_map const& cache);

        /// The result of loading the node internal data
        using load_data_result = std::
            tuple<data, std::unordered_map<std::string, data>>;

        /// Load the node data and its child nodes
        load_data_result
        load_data(
            config const& config,
            text_printer const& plain_printer,
            text_printer const& markdown_printer,
            node_cache_map const& cache) const;

        friend class doxygen;

    private:
        class Temp;
        data
        load_data(
            config const& config,
            text_printer const& plain_printer,
            text_printer const& markdown_printer,
            node_cache_map const& cache,
            xml::element const& element) const;

        std::vector<class_reference>
        get_all_base_classes(node_cache_map const& cache);

        std::unique_ptr<Temp> temp_;
        kind kind_{ kind::INDEX };
        type type_{ type::NONE };
        std::string language_;
        std::string refid_;
        std::string name_;
        std::string qualified_name_;
        std::string brief_;
        std::string summary_;
        std::string title_;
        node* parent_{ nullptr };
        node* group_{ nullptr };
        std::list<std::shared_ptr<node>> children_;
        bool empty_{ true };
        std::string xml_path_;
        std::vector<class_reference> base_classes_;
        std::vector<class_reference> derived_classes_;
        visibility visibility_{ visibility::PUBLIC };
        virtual_category virt_{ virtual_category::NON_VIRTUAL };
        std::string url_;
        std::string anchor_;

        void
        parse_base_info(xml::element const& element);

        void
        parse_inheritance_info(xml::element const& element);

        std::shared_ptr<node>
        find_recursively(std::string const& refid) const;

        static xml::element
        assert_child(xml::element const& xml, std::string const& name);

        static xml::element
        assert_child(xml const& xml, std::string const& name);
    };
} // namespace doxybook

#endif