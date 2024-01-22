#include <iostream>

#include <Lexer.hpp>
#include <Parser.hpp>

int main(void) {

    Lexer lxr;
    Parser psr;

    lxr.tokenize("Example.dog");
    lxr.printTokens();

    // psr.parse(&lxr);

    return 0;
}