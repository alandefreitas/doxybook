#pragma once
#include <string>
#include "XmlTextParser.hpp"
#include "Config.hpp"
#include "Node.hpp"

namespace Doxybook {
    class Doxygen;

    class TextPrinter {
    public:
        explicit TextPrinter(const Config& config, const Doxygen& doxygen)
            : config(config),
              doxygen(doxygen) {

        }
        virtual ~TextPrinter() = default;

        virtual std::string print(const XmlTextParser::Node& node, const std::string& language = "cpp") const = 0;

    protected:
        const Config& config;
        const Doxygen& doxygen;
    };
}
