#pragma once

#include <string>
#include <unordered_map>

class Token {
    public:
            enum TokenType {
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
            If, Else, Elif,
            For, While, Do,
            Procedure,
            Return,
            Unknown,
            End
        };

        static Token retrieveTokenFromKeyword(std::string keyword);
        static std::string tokenTypeToString(Token::TokenType tokenType);

        TokenType type;
        std::string data;

        int line;
        int col;

        Token(TokenType type, std::string data);
};