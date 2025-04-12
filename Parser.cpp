#include "Parser.h"
#include <optional>
#include <unordered_map>

static std::vector<Token> tokens;
static size_t current;
static std::unordered_map<std::string, std::optional<int>> symbolTable;
static std::string error;

Token peek() {
    if (current >= tokens.size()) return Token(TokenType::END_OF_FILE, "");
    return tokens[current];
}

Token advance() {
    return tokens[current++];
}

bool match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

void setError(const std::string& msg) {
    if (error.empty()) error = msg;
}

std::optional<int> parseExp();
std::optional<int> parseTerm();
std::optional<int> parseFact();
bool parseAssignment();

std::optional<int> parseFact() {
    Token tok = peek();

    if (tok.type == TokenType::MINUS || tok.type == TokenType::PLUS) {
        Token unary = advance();
        auto value = parseFact();  // allow recursion
        if (!value) return std::nullopt;
        return (unary.type == TokenType::MINUS) ? -(*value) : *value;
    }    

    if (match(TokenType::LPAREN)) {
        auto val = parseExp();
        if (!match(TokenType::RPAREN)) {
            setError("missing ')'");
            return std::nullopt;
        }
        return val;
    }

    if (match(TokenType::INTEGER)) {
        return std::stoi(tok.value);
    }

    if (match(TokenType::IDENTIFIER)) {
        std::string name = tok.value;
        if (!symbolTable.count(name) || !symbolTable[name].has_value()) {
            setError("undefined variable: " + name);
            return std::nullopt;
        }
        return symbolTable[name].value();
    }

    setError("unexpected token: " + tok.value);
    return std::nullopt;
}

std::optional<int> parseTerm() {
    auto left = parseFact();
    if (!left) return std::nullopt;

    while (peek().type == TokenType::MULTIPLY || peek().type == TokenType::DIVIDE) {
        Token op = advance();
        auto right = parseFact();
        if (!right) return std::nullopt;

        if (op.type == TokenType::MULTIPLY) *left *= *right;
        else if (*right != 0) *left /= *right;
        else {
            setError("division by zero");
            return std::nullopt;
        }
    }

    return left;
}

std::optional<int> parseExp() {
    auto left = parseTerm();
    if (!left) return std::nullopt;

    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        Token op = advance();
        auto right = parseTerm();
        if (!right) return std::nullopt;

        if (op.type == TokenType::PLUS) *left += *right;
        else *left -= *right;
    }

    return left;
}

bool parseAssignment() {
    if (peek().type != TokenType::IDENTIFIER) {
        setError("expected variable name");
        return false;
    }

    std::string name = advance().value;

    if (!match(TokenType::ASSIGN)) {
        setError("expected '='");
        return false;
    }

    auto value = parseExp();
    if (!value) return false;

    if (!match(TokenType::SEMICOLON)) {
        setError("expected semicolon");
        return false;
    }

    symbolTable[name] = value;
    return true;
}

bool parseProgram(const std::vector<Token>& tokenStream, std::unordered_map<std::string, int>& variables, std::string& errorMessage) {
    tokens = tokenStream;
    current = 0;
    symbolTable.clear();
    error.clear();

    while (peek().type != TokenType::END_OF_FILE) {
        if (!parseAssignment()) {
            errorMessage = error;
            return false;
        }
    }

    for (const auto& [key, val] : symbolTable) {
        if (val.has_value()) {
            variables[key] = val.value();
        }
    }

    return true;
}
