#pragma once

#include <string>
#include <vector>
#include "token.h"

enum class RedirectionType {
  Input,
  Output,
  Append,
  Error
};

struct Redirection {
  RedirectionType type;
  std::string target;
  
  Token targetToken;
};

struct Command {
  std::vector<std::string> arguments;
  std::vector<Redirection> redirections;
  
  std::vector<Token> argumentTokens;
};

struct Pipeline {
  std::vector<Command> commands;
};
