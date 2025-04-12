# LexParseEval

A simple expression interpreter in C++ that supports:

- Integer arithmetic: `+`, `-`, `*`, `/`
- Variable assignments: `x = 3 + 2;`
- Nested expressions with parentheses
- Multiple unary operators like `---(x + 1)`
- Clean error handling

---


```bash
g++ -std=c++17 main.cpp Lexer.cpp Parser.cpp -o LexParseEval
