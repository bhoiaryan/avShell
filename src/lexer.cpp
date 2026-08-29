#include "lexer.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;

    std::string current;
    std::vector<WordPart> currentParts;

    enum class State {
        Normal,
        SingleQuote,
        DoubleQuote
    };

    State state = State::Normal;

    // Add a character to the current word.
    // Consecutive characters with the same quote type
    // are stored in the same WordPart.
    auto addPart = [&](char c, QuoteType quote) {
        current += c;

        if (!currentParts.empty() &&
            currentParts.back().quote == quote) {

            currentParts.back().value += c;
        }
        else {
            currentParts.push_back({
                std::string(1, c),
                quote
            });
        }
    };

    // Convert the current word into a Token.
    auto flushWord = [&]() {
        if (!current.empty() || !currentParts.empty()) {

            tokens.push_back({
                TokenType::Word,
                current,
                currentParts
            });

            current.clear();
            currentParts.clear();
        }
    };

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        // =====================================================
        // NORMAL STATE
        // =====================================================
        if (state == State::Normal) {

            // Whitespace ends the current word.
            if (std::isspace(
                    static_cast<unsigned char>(c))) {

                flushWord();
            }

            // Start single-quoted section.
            else if (c == '\'') {
                state = State::SingleQuote;
            }

            // Start double-quoted section.
            else if (c == '"') {
                state = State::DoubleQuote;
            }

            // Escape character.
            else if (c == '\\') {

                if (i + 1 >= input.size()) {
                    throw std::runtime_error(
                        "trailing escape character"
                    );
                }

                ++i;

                // Escaped character is treated as
                // unquoted text.
                addPart(
                    input[i],
                    QuoteType::None
                );
            }

            // Pipe.
            else if (c == '|') {

                flushWord();

                tokens.push_back({
                    TokenType::Pipe,
                    "|",
                    {}
                });
            }

            // Input redirection.
            else if (c == '<') {

                flushWord();

                tokens.push_back({
                    TokenType::RedirectIn,
                    "<",
                    {}
                });
            }

            // Output redirection.
            else if (c == '>') {

                flushWord();

                // >>
                if (i + 1 < input.size() &&
                    input[i + 1] == '>') {

                    ++i;

                    tokens.push_back({
                        TokenType::RedirectAppend,
                        ">>",
                        {}
                    });
                }

                // >
                else {
                    tokens.push_back({
                        TokenType::RedirectOut,
                        ">",
                        {}
                    });
                }
            }

            // Error redirection: 2>
            else if (c == '2' &&
                     i + 1 < input.size() &&
                     input[i + 1] == '>') {

                flushWord();

                ++i;

                tokens.push_back({
                    TokenType::RedirectError,
                    "2>",
                    {}
                });
            }

            // Normal character.
            else {
                addPart(c, QuoteType::None);
            }
        }

        // =====================================================
        // SINGLE QUOTE STATE
        // =====================================================
        else if (state == State::SingleQuote) {

            // Closing single quote.
            if (c == '\'') {
                state = State::Normal;
            }

            else {
                addPart(c, QuoteType::Single);
            }
        }

        // =====================================================
        // DOUBLE QUOTE STATE
        // =====================================================
        else if (state == State::DoubleQuote) {

            // Closing double quote.
            if (c == '"') {
                state = State::Normal;
            }

            // Escape inside double quotes.
            else if (c == '\\') {

                if (i + 1 >= input.size()) {
                    throw std::runtime_error(
                        "trailing escape character"
                    );
                }

                ++i;

                addPart(
                    input[i],
                    QuoteType::Double
                );
            }

            else {
                addPart(c, QuoteType::Double);
            }
        }
    }

    // We reached the end while still inside quotes.
    if (state == State::SingleQuote ||
        state == State::DoubleQuote) {

        throw std::runtime_error(
            "unterminated quote"
        );
    }

    // Add the final word.
    flushWord();

    return tokens;
}
