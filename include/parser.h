#pragma once

#include "token.h"
#include "command.h"

#include <vector>

Pipeline parse(const std::vector<Token>& tokens);
