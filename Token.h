#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    INTEGER,
    IDENTIFIER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    SEMICOLON,
    LPAREN,
    RPAREN,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

#endif
