//
// Copyright (c) 2021 Matus Novak (@matusnovak)
// Copyright (c) 2022 alandefreitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//

#ifndef DOXYBOOK_RENDERER_HPP
#define DOXYBOOK_RENDERER_HPP

#include <doxybook/config.hpp>
#include <doxybook/doxygen.hpp>
#include <doxybook/json_converter.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace inja {
    struct Template;
    class Environment;
} // namespace inja

namespace doxybook {
    /// Render inja templates with the specified configuration
    class renderer {
    public:
        /// Constructor
        explicit renderer(
            config const& config,
            doxygen const& doxygen,
            json_converter const& json_converter,
            std::optional<std::string> const& templates_path = std::nullopt);
        ~renderer();

        /// Destructor
        void
        render(
            std::string const& name,
            std::string const& path,
            nlohmann::json const& data) const;

        /// Render template
        /**
         * @param name template name
         * @param data data as json
         * @return
         */
        std::string
        render(std::string const& name, nlohmann::json const& data) const;

    private:
        config const& config_;
        doxygen const& doxygen_;
        json_converter const& json_converter_;
        std::unique_ptr<inja::Environment> env_;
        std::unordered_map<std::string, std::unique_ptr<inja::Template>>
            templates_;
    };
} // namespace doxybook

#endif