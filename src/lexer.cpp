#include "lexer.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string current;

    enum class State {
        Normal,
        SingleQuote,
        DoubleQuote
    };

    State state = State::Normal;

    auto flushWord = [&]() {
        if (!current.empty()) {
            tokens.push_back({TokenType::Word, current});
            current.clear();
        }
    };

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (state == State::Normal) {
            if (c == '\'') {
                state = State::SingleQuote;
            } else if (c == '"') {
                state = State::DoubleQuote;
            } else if (c == '\\') {
                if (i + 1 < input.size()) {
                    ++i;
                    current += input[i];
                } else {
                    throw std::runtime_error(
                        "trailing escape character"
                    );
                }
            } else if (std::isspace(static_cast<unsigned char>(c))) {
                flushWord();
            } else if (c == '|') {
                flushWord();

                tokens.push_back({
                    TokenType::Pipe,
                    "|"
                });
            } else if (c == '<') {
                flushWord();

                tokens.push_back({
                    TokenType::RedirectIn,
                    "<"
                });
            } else if (c == '>') {
                flushWord();

                if (i + 1 < input.size() && input[i + 1] == '>') {
                    ++i;

                    tokens.push_back({
                        TokenType::RedirectAppend,
                        ">>"
                    });
                } else {
                    tokens.push_back({
                        TokenType::RedirectOut,
                        ">"
                    });
                }
            } else if (c == '2' &&
                       i + 1 < input.size() &&
                       input[i + 1] == '>') {
                flushWord();

                ++i;

                tokens.push_back({
                    TokenType::RedirectError,
                    "2>"
                });
            } else {
                current += c;
            }
        } else if (state == State::SingleQuote) {
            if (c == '\'') {
                state = State::Normal;
            } else {
                current += c;
            }
        } else if (state == State::DoubleQuote) {
            if (c == '"') {
                state = State::Normal;
            } else if (c == '\\') {
                if (i + 1 < input.size()) {
                    ++i;
                    current += input[i];
                } else {
                    throw std::runtime_error(
                        "trailing escape character"
                    );
                }
            } else {
                current += c;
            }
        }
    }

    if (state == State::SingleQuote ||
        state == State::DoubleQuote) {
        throw std::runtime_error("unterminated quote");
    }

    flushWord();

    return tokens;
}
