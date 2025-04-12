#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main() {
    while (true) {
        std::string input, line;
        std::cout << "\nEnter expression (empty line to run and type \"exit\" to exit):\n";

        while (true) {
            std::getline(std::cin, line);
            if (line == "exit") return 0;
            if (line.empty()) break;
            input += line + " ";
        }

        try {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();

            std::unordered_map<std::string, int> variables;  
            std::string errorMessage;

            bool success = parseProgram(tokens, variables, errorMessage);

            if (!success) {
                std::cout << "error" << std::endl;
            } else {
                for (const auto& [key, value] : variables) {
                    std::cout << key << " = " << value << std::endl;
                }
            }

        } catch (const std::exception& ex) {
            std::cout << "error" << std::endl;
        }
    }

    return 0;
}
