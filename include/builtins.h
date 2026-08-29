#pragma once

#include <string>
#include <vector>

bool isBuiltin(const std::string& command);

struct BuiltinResult {
  bool shouldExit;
  int  exitStatus;
 };

BuiltinResult executeBuiltin(const std::vector<std::string>& args);


