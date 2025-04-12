#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Token.h"

bool parseProgram(
    const std::vector<Token>& tokens,
    std::unordered_map<std::string, int>& variables,
    std::string& errorMessage
);

#endif
