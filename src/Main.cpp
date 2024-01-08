#include <iostream>

#include <Token.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>

int main(void) {

    Lexer lxr;

    lxr.tokenize("Example.dog");

    for (auto token : lxr.tokens) {
        std::cout 
        << Token::tokenTypeToString(token.type)
        << "\t\t" 
        << token.data 
        << "\t"
        << token.line 
        << " "
        << token.col 
        << std::endl;
    }

    std::cout << std::endl;

    return 0;
}