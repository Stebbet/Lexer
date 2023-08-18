#include <fstream>
#include <iostream>
#include <string>
#include "lexer.h"

using namespace std;

int main() {

    // "Code" file
    string filename = "input.txt";
    FileInput file(filename);
    Tokenizer myLexer(&file);
    myLexer.parse_file();

    return 0;
}



