//
// Created by SamTebbet on 17/08/2023.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <vector>
#include <string>
#include <fstream>
#include <set>


struct Token {
    enum class Token_Type {

        Token_EOL,
        Token_EOF,
        Token_VAR,

        // Variables
        Token_INT,
        Token_FLOAT,
        Token_STRING,
        Token_BOOL,
        Token_CHAR,

        // Operators
        Token_PLUS,
        Token_MINUS,
        Token_AST,
        Token_SLASH,
        Token_EQUALS,

        // Separators
        Token_LPAREN,
        Token_RPAREN,
        Token_LCURLY,
        Token_RCURLY,
        Token_LSQUARE,
        Token_RSQUARE,
        Token_SEMICOLON,
        Token_COLON,
        Token_COMMA,
        Token_PERIOD,

        // Values
        Token_NUM,
        Token_STR,

        // Keywords
        Token_IF,
        Token_ELIF,
        Token_ELSE,
        Token_FOR,
        Token_WHILE,
        Token_RETURN
    };

    // Constructors
    explicit Token(Token_Type T) : type(T), integer(0){}

    explicit Token(Token_Type T, std::string &s) : type(T), str(s), integer(0){}

    explicit Token(Token_Type T, int i) : type(T), integer(i){}


    [[nodiscard]] std::string type_to_string() const {
        switch (type){
            case Token_Type::Token_EOL:
                return "token_eol";
            case Token_Type::Token_EOF:
                return "token_eof";
            case Token_Type::Token_VAR:
                return "token_var";
            case Token_Type::Token_INT:
                return "token_int";
            case Token_Type::Token_FLOAT:
                return "token_float";
            case Token_Type::Token_STRING:
                return "token_string";
            case Token_Type::Token_BOOL:
                return "token_bool";
            case Token_Type::Token_CHAR:
                return "token_char";
            case Token_Type::Token_PLUS:
                return "token_plus";
            case Token_Type::Token_MINUS:
                return "token_minus";
            case Token_Type::Token_AST:
                return "token_ast";
            case Token_Type::Token_SLASH:
                return "token_slash";
            case Token_Type::Token_EQUALS:
                return "token_equals";
            case Token_Type::Token_LPAREN:
                return "token_lparen";
            case Token_Type::Token_RPAREN:
                return "token_rparen";
            case Token_Type::Token_LCURLY:
                return "token_lcurly";
            case Token_Type::Token_RCURLY:
                return "token_rcurly";
            case Token_Type::Token_LSQUARE:
                return "token_lsquare";
            case Token_Type::Token_RSQUARE:
                return "token_rsquare";
            case Token_Type::Token_SEMICOLON:
                return "token_semicolon";
            case Token_Type::Token_COLON:
                return "token_colon";
            case Token_Type::Token_COMMA:
                return "token_comma";
            case Token_Type::Token_PERIOD:
                return "token_period";
            case Token_Type::Token_NUM:
                return "token_num";
            case Token_Type::Token_STR:
                return "token_str";
            case Token_Type::Token_IF:
                return "token_if";
            case Token_Type::Token_ELIF:
                return "token_elif";
            case Token_Type::Token_ELSE:
                return "token_else";
            case Token_Type::Token_FOR:
                return "token_for";
            case Token_Type::Token_WHILE:
                return "token_while";
            case Token_Type::Token_RETURN:
                return "token_return";
            default:
                return "";
        }
    }

    [[nodiscard]] std::string toString() const{
        return type_to_string() + (str.empty() ? "" : " : " + str) +
                (type == Token_Type::Token_NUM ? " : " + std::to_string(integer) : "");
    }

    const Token_Type type;
    const std::string str;
    const int integer;
};


class FileInput {
    // Need this class because otherwise we would have to reopen the file at each function
public:
    FileInput(std::string &filename) {
        input_stream.open(filename);
    }
    ~FileInput(){
        if (input_stream.is_open()) input_stream.close();
    }

    bool getLine(std::string * line){
        // Gets the line in the file
        if (!input_stream) return false;

        if ((bool) std::getline(input_stream, *line)){
            lineNumber++;
            return true;
        }
        return false;
    }

    int getLineNum(){
        return lineNumber;
    }

private:
    std::ifstream input_stream;
    int lineNumber;

};

class Tokenizer {
public:
    std::vector<Token> tokens;

    explicit Tokenizer(FileInput* s);

    bool parse_file();

private:

    std::string current_line;
    FileInput* source;

    bool read_line();

    bool parse_line();

    bool valid_number(int index);
};

#endif //LEXER_LEXER_H