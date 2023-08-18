#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexer.h"

using namespace std;

Tokenizer::Tokenizer(FileInput *s) : line_count(0), source(s){}

bool Tokenizer::parse_line() {
    if (!read_line()) return false;

    int i = 0;
    while (i < current_line.size()) {
        if (isalpha(current_line[i])) { // Check if character is alphabetical
            // Alphabet and most tokens
            const int start = i;
            do { i++; } while (i < current_line.size() && isalpha(current_line[i]) || current_line[i] == '_');
            string value = current_line.substr(start, i - start);

            if      (value == "int")    tokens.push_back(* new Token(Token::Token_Type::Token_INT));
            else if (value == "float")  tokens.push_back(* new Token(Token::Token_Type::Token_FLOAT));
            else if (value == "str")    tokens.push_back(* new Token(Token::Token_Type::Token_STR));
            else if (value == "bool")   tokens.push_back(* new Token(Token::Token_Type::Token_BOOL));
            else if (value == "char")   tokens.push_back(* new Token(Token::Token_Type::Token_CHAR));
            else if (value == "if")     tokens.push_back(* new Token(Token::Token_Type::Token_IF));
            else if (value == "elif")   tokens.push_back(* new Token(Token::Token_Type::Token_ELIF));
            else if (value == "else")   tokens.push_back(* new Token(Token::Token_Type::Token_ELSE));
            else if (value == "for")    tokens.push_back(* new Token(Token::Token_Type::Token_FOR));
            else if (value == "while")  tokens.push_back(* new Token(Token::Token_Type::Token_WHILE));
            else if (value == "return") tokens.push_back(* new Token(Token::Token_Type::Token_RETURN));
            else tokens.push_back(* new Token(Token::Token_Type::Token_VAR, value));

        } else if (valid_number(i)) {
            // Numbers and Integer Tokens
            const int start = i;
            do { i++; } while (i < current_line.size() && isdigit(current_line[i]));
            tokens.push_back(*new Token(Token::Token_Type::Token_NUM,
                                        stoi(current_line.substr(start, i - start))));
        } else if (current_line[i] == '"') {
            // For STRING tokens
            const int start = i;
            const char check = current_line[i];
            do { i++; } while (i < current_line.size() && current_line[i] != check);
            i++; // Iterate over the next "
            string value = current_line.substr(start, i - start);
            tokens.push_back(*new Token(Token::Token_Type::Token_STR, value));

        } else {
            // One character symbols
            switch (current_line[i]) {
                case '+':
                    tokens.push_back(*new Token(Token::Token_Type::Token_PLUS));
                    break;
                case '-':
                    tokens.push_back(*new Token(Token::Token_Type::Token_MINUS));
                    break;
                case '*':
                    tokens.push_back(*new Token(Token::Token_Type::Token_AST));
                    break;
                case '/':
                    tokens.push_back(*new Token(Token::Token_Type::Token_SLASH));
                    break;
                case '=':
                    tokens.push_back(*new Token(Token::Token_Type::Token_EQUALS));
                    break;
                case '(':
                    tokens.push_back(*new Token(Token::Token_Type::Token_LPAREN));
                    break;
                case ')':
                    tokens.push_back(*new Token(Token::Token_Type::Token_RPAREN));
                    break;
                case '[':
                    tokens.push_back(*new Token(Token::Token_Type::Token_LSQUARE));
                    break;
                case ']':
                    tokens.push_back(*new Token(Token::Token_Type::Token_RSQUARE));
                    break;
                case '{':
                    tokens.push_back(*new Token(Token::Token_Type::Token_LCURLY));
                    break;
                case '}':
                    tokens.push_back(*new Token(Token::Token_Type::Token_RCURLY));
                    break;
                case ';':
                    tokens.push_back(*new Token(Token::Token_Type::Token_SEMICOLON));
                    break;
                case ':':
                    tokens.push_back(*new Token(Token::Token_Type::Token_COLON));
                    break;
                case ',':
                    tokens.push_back(*new Token(Token::Token_Type::Token_COMMA));
                    break;
                case '.':
                    tokens.push_back(*new Token(Token::Token_Type::Token_PERIOD));
                default:
                    // Case if the character is a space ' '
                    i++;
                    continue;
            }
            i++;
        }
    }
    tokens.push_back(*new Token(Token::Token_Type::Token_EOL));
    return true;
}

bool Tokenizer::read_line() {
    // This is nice yeah?
    if (source->getLine(&current_line)){
        return true;
    }
    return false;
}

bool Tokenizer::valid_number(int index) {
    // Is a valid number if the character is a digit or if there is a '-' in front of a digit
    return isdigit(current_line[index]) || (current_line[index] == '-' && index + 1 < current_line.size()
    && isdigit(current_line[index + 1]));
}

bool Tokenizer::parse_file() {
    while (parse_line()){}
    for (auto i : tokens){
        cout << i.toString();
        if (i.type == Token::Token_Type::Token_EOL) cout << endl;
        else cout << " - ";
    }
    return true;
}
