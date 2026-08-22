#pragma once

#include <string>
#include <vector>

bool isBuiltin(const std::string& command);

int executeBuiltin(const std::vector<string>& args);


