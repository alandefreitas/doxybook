//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_DEFAULT_TEMPLATES_HPP
#define DOXYBOOK_DEFAULT_TEMPLATES_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace doxybook {
    /// Describe the default template for a page
    struct default_template {
        /// The template source
        std::string src;

        /// Files on which the template depends
        std::vector<std::string> dependencies;
    };

    /// A map with all the default templates
    /**
     * Unless template files are provided, these templates are used.
     */
    extern std::unordered_map<std::string, default_template> default_templates;

    /// Save default templates
    /**
     * This function stores all the default templates to files. The user
     * can edit these templates to come up with new templates.
     */
    void
    save_default_templates(std::string const& path);
} // namespace doxybook

#endif