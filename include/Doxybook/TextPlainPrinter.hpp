#pragma once
#include "TextPrinter.hpp"

namespace Doxybook {
    class TextPlainPrinter : public TextPrinter {
    public:
        explicit TextPlainPrinter(const Config& config, const Doxygen& doxygen)
            : TextPrinter(config, doxygen) {

        }

        std::string print(const XmlTextParser::Node& node, const std::string& language) const override;

    private:
        void print(std::stringstream& ss, const XmlTextParser::Node& node) const;
    };
}
