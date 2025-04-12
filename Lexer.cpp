#include "Lexer.h"
#include "Token.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& input) : text(input), pos(0) {
    currentChar = text.empty() ? '\0' : text[0];
}

void Lexer::advance() {
    pos++;
    currentChar = (pos < text.length()) ? text[pos] : '\0';
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && std::isspace(currentChar)) {
        advance();
    }
}

std::string Lexer::integer() {
    std::string result;
    while (currentChar != '\0' && std::isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return result;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (currentChar != '\0') {
        if (std::isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (std::isdigit(currentChar)) {
            std::string num = integer();
            if (num.length() > 1 && num[0] == '0') {
                throw std::runtime_error("error");
            }
            tokens.emplace_back(TokenType::INTEGER, num);
            continue;
        }

        if (std::isalpha(currentChar) || currentChar == '_') {
            std::string id;
            while (std::isalnum(currentChar) || currentChar == '_') {
                id += currentChar;
                advance();
            }
            tokens.emplace_back(TokenType::IDENTIFIER, id);
            continue;
        }

        switch (currentChar) {
            case '+': tokens.emplace_back(TokenType::PLUS, "+"); break;
            case '-': tokens.emplace_back(TokenType::MINUS, "-"); break;
            case '*': tokens.emplace_back(TokenType::MULTIPLY, "*"); break;
            case '/': tokens.emplace_back(TokenType::DIVIDE, "/"); break;
            case '=': tokens.emplace_back(TokenType::ASSIGN, "="); break;
            case ';': tokens.emplace_back(TokenType::SEMICOLON, ";"); break;
            case '(': tokens.emplace_back(TokenType::LPAREN, "("); break;
            case ')': tokens.emplace_back(TokenType::RPAREN, ")"); break;
            default:
                throw std::runtime_error("error");
        }

        advance();
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "");
    return tokens;
}
