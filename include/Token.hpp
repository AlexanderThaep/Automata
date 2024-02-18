#pragma once

#include <string>
#include <unordered_map>

class Token {
    public:
        enum TokenType {
            // All token types
            // Arguably the most important
            Identifier,
            // Types
            Constant,
            Variable,
            Pointer,
            // Literal types
            LiteralStr,
            LiteralNum,
            LiteralBool,
            // Brackeys
            LeftBracket, RightBracket,
            LeftParen, RightParen,
            LeftBrace, RightBrace,
            // Operators
            BinaryOperator,
            UnaryOperator,
            AccessOperator,
            // Miscellaneous
            Comma,
            If, Else, Elif,
            For, While, Do,
            Procedure,
            Return,
            Unknown,
            Start,
            End
        };

        static Token retrieveTokenFromKeyword(std::string keyword);
        static std::string tokenTypeToString(Token::TokenType tokenType);

        TokenType type;
        std::string data;

        int StartLine;
        int StartCol;

        int EndLine;
        int EndCol;

        Token(TokenType type, std::string data);
};