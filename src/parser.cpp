#include "parser.h"

#include <iostream>
#include <stdexcept>
#include <utility>

Pipeline parse(const std::vector<Token>& tokens) {
    Pipeline pipeline;
    Command currentCommand;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];

        if (token.type == TokenType::Word) {
              currentCommand.arguments.push_back(token.value);
              currentCommand.argumentTokens.push_back(token);
          }

        else if (token.type == TokenType::Pipe) {
            if (currentCommand.arguments.empty()) {
                throw std::runtime_error("invalid pipe placement");
            }

            pipeline.commands.push_back(std::move(currentCommand));
            currentCommand = Command{};
        }

        else if (token.type == TokenType::RedirectIn ||
                 token.type == TokenType::RedirectOut ||
                 token.type == TokenType::RedirectAppend ||
                 token.type == TokenType::RedirectError) {
            
            if (i + 1 >= tokens.size() ||
                tokens[i + 1].type != TokenType::Word) {
                throw std::runtime_error(
                    "redirection requires a target"
                );
            }

            Redirection redirection;

            switch (token.type) {
                case TokenType::RedirectIn:
                    redirection.type = RedirectionType::Input;
                    break;

                case TokenType::RedirectOut:
                    redirection.type = RedirectionType::Output;
                    break;

                case TokenType::RedirectAppend:
                    redirection.type = RedirectionType::Append;
                    break;

                case TokenType::RedirectError:
                    redirection.type = RedirectionType::Error;
                    break;

                default:
                    throw std::runtime_error("invalid redirection");
            }

            redirection.target = tokens[i + 1].value;

            currentCommand.redirections.push_back(
                std::move(redirection)
            );

            ++i;
        }
    }

    // Add the final command.
    if (!currentCommand.arguments.empty() ||
        !currentCommand.redirections.empty()) {
        pipeline.commands.push_back(std::move(currentCommand));
    }

    return pipeline;
}
