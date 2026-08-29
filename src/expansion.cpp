#include "expansion.h"
#include "token.h"

#include <cstdlib>
#include <cctype>

std::string expandVariables(const std::string& input) {
    std::string result;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (c != '$') {
            result += c;
            continue;
        }

        if (i + 1 >= input.size()) {
            result += '$';
            continue;
        }

        // Variable names start with a letter or underscore.
        char next = input[i + 1];

        if (!std::isalpha(static_cast<unsigned char>(next)) &&
            next != '_') {
            result += '$';
            continue;
        }

        size_t start = i + 1;
        size_t j = start;

        while (j < input.size() &&
               (std::isalnum(static_cast<unsigned char>(input[j])) ||
                input[j] == '_')) {
            ++j;
        }

        std::string name = input.substr(start, j - start);

        const char* value = std::getenv(name.c_str());

        if (value != nullptr) {
            result += value;
        }

        i = j - 1;
    }

    return result;
}
