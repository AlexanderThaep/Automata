#include <iostream>

#include <Token.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>

int main(void) {

    Lexer lxr;

    lxr.tokenize("Example.dog");
    lxr.printTokens();

    return 0;
}