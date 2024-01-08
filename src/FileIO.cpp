#include <iostream>
#include <fstream>
#include <string>

#include <Token.hpp>
#include <Lexer.hpp>

void fileToLexer(Lexer &lxr, std::string file_name) {
    std::string temp;

    std::ifstream file;
    file.std::ifstream::open(file_name);

    if (file.is_open()) {
        while (std::getline(file, temp)) {
            lxr.stringToInput('\n' + temp);
        }
    }
    file.close();
}