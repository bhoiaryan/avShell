#include "expansion.h"

#include <cctype>
#include <cstdlib>

std::string expandToken(
    const Token& token,
    int lastExitStatus
) {

    if (token.parts.empty()) {
        return token.value;
    }
    std::string result;

    for (const auto& part : token.parts) {

        // Single-quoted text is literal.
        if (part.quote == QuoteType::Single) {
            result += part.value;
            continue;
        }

        const std::string& text = part.value;

        for (size_t i = 0; i < text.size(); ++i) {
            char c = text[i];

            if (c != '$') {
                result += c;
                continue;
            }

            // '$' at the end.
            if (i + 1 >= text.size()) {
                result += '$';
                continue;
            }

            char next = text[i + 1];

            // Special variable: $?
            if (next == '?') {
                result += std::to_string(lastExitStatus);
                ++i;
                continue;
            }

            // Not a valid variable name.
            if (!std::isalpha(
                    static_cast<unsigned char>(next)) &&
                next != '_') {

                result += '$';
                continue;
            }

            size_t start = i + 1;
            size_t j = start;

            while (j < text.size() &&
                   (std::isalnum(
                        static_cast<unsigned char>(text[j])) ||
                    text[j] == '_')) {

                ++j;
            }

            std::string name =
                text.substr(start, j - start);

            const char* value =
                std::getenv(name.c_str());

            if (value != nullptr) {
                result += value;
            }

            i = j - 1;
        }
    }

    return result;
}
