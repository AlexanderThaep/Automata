#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include <Token.hpp>

class Lexer {
    public:
        std::unordered_map<std::string, Token> symbolTable;

        std::vector<Token> tokens;
        std::string currentString;
        std::string input;

        int lineNumber;
        int colNumber;
        int offset;

        Lexer();
        Token getNextToken();
        void tokenize(std::string file_name);

    private:
        Token matchKeyword();
        char at(int index);
        void handlePunctuator(int &index);
        void handleString(int &index);
        void handleWord(int &index);
        void handleDigits(int &index);
        void pushToken(Token token);
        void pushToken();
};