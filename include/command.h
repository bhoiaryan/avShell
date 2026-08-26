#pragma once

#include <string>

#include <vector>

enum class RedirectionType {
  Input,
  Output,
  Append,
  Error
};

struct Redirection {
  RedirectionType type;
  std::string target;
};

struct Command {
  std::vector<std::string> arguments;
  std::vector<Redirection> redirections;
};

struct Pipeline {
  std::vector<Command> commands;
};
