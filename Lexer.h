#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string text;
    size_t pos;
    char currentChar;

    void advance();
    void skipWhitespace();
    std::string integer();
};

#endif
