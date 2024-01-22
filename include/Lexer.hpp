#pragma once

#include <string>
#include <vector>

#include <Token.hpp>
#include <Symbol.hpp>

class Lexer {
    public:
        Lexer();
        std::vector<Token> getTokens();
        Token getNextToken();
        void tokenize(std::string file_name);
        void reset();
        void printTokens();
        void stringToInput(std::string str);

    private:
        std::vector<Token> tokens;
        std::string currentString;
        std::string input;

        int lineNumber;
        int lineOffset;
        int colNumber;

        int offset;

        Token matchKeyword();
        char at(int index);
        void handleOperators(int &index);
        void handleString(int &index);
        void handleWord(int &index);
        void handleDigits(int &index);
        void pushToken(Token token);
        void pushToken();
};