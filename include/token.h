#pragma once

#include <string>
#include <vector>

enum class TokenType {
  Word,
  Pipe,
  RedirectIn,
  RedirectOut,
  RedirectAppend,
  RedirectError
};
enum class QuoteType {
  None,
  Single,
  Double
};
struct WordPart{
  std::string value;
  QuoteType quote;
};

struct Token {
  TokenType type;
  std::string value;
  std::vector<WordPart> parts;
};
