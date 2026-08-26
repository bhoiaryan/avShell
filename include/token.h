#pragma once

#include <string>

enum class TokenType {
  Word,
  Pipe,
  RedirectIn,
  RedirectOut,
  RedirectAppend,
  RedirectError
};

struct Token {
  TokenType type;
  std::string value;
};
