#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }

    string input((istreambuf_iterator<char>(infile)),
                 istreambuf_iterator<char>());

    infile.close();

    try {
        Lexer lexer(input);
        vector<Token> tokens = lexer.tokenize();

        unordered_map<string, int> variables;
        string errorMessage;

        bool success = parseProgram(tokens, variables, errorMessage);

        if (!success) {
            cout << "error" << endl;
        } else {
            for (const auto& [key, value] : variables) {
                cout << key << " = " << value << endl;
            }
        }

    } catch (const exception& ex) {
        cout << "error" << endl;
    }

    return 0;
}

