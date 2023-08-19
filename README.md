# Lexer
Tokenizer/Lexer Learning Project in C++. Fun, challenging project that I would love to continue further (maybe).

### Overview
The goal of this project was to learn the basics of lexing and parsing

### Example usage diagram
![Logo](https://tomassetti.me/wp-content/uploads/2017/02/lexer-parser-center-1030x187.png)



### Expected output:
Input.txt
```
int a = 365;
for (int i = 0; i < 50; i++){
    print i;
}
```
Output
```
token_int - token_var : a - token_equals - token_num : 365 - token_semicolon - token_eol
token_for - token_lparen - token_int - token_var : i - token_equals - token_num : 0 - token_semicolon - token_var : i -
token_num : 50 - token_semicolon - token_var : i - token_plus - token_plus - token_rparen - token_lcurly - token_eol
token_var : print - token_var : i - token_semicolon - token_eol
token_rcurly - token_eol
```

### What to do next?
The next step in my project would be to implement a parser to create a parse tree / abstract syntax tree (AST), as shown in the diagram
