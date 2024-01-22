#pragma once

#include <string>
#include <vector>

#include <Token.hpp>
#include <Lexer.hpp>
#include <AST.hpp>

class Parser {
    private:
        AST *ast;
    public:
        Parser();

        void parse(Lexer *lxr);
};