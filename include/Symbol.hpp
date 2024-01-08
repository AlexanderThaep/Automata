#pragma once

#include <Token.hpp>

class Symbol : public Token {
    public:
        static std::unordered_map<std::string, Symbol> symbolTable;

        enum ValueType {
            Integer,
            Float,
            String,
            Character,
            Boolean,
            Pointer
        };

        ValueType vtype;
        int scopeID;
        bool isProcedure;
        bool isConstant;
        bool isDeclared;
        bool isInitialized;

        using Token::Token;
        Symbol(Token token);
};