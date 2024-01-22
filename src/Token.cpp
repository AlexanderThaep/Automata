#include <string>
#include <unordered_map>

#include <Token.hpp>

static std::unordered_map<std::string, Token> Keywords = {
    {"var", Token(Token::Variable, "var")},
    {"const", Token(Token::Constant, "const")},
    {"ptr", Token(Token::Pointer, "ptr")},
    {"ret", Token(Token::Return, "ret")},
    {"proc", Token(Token::Procedure, "proc")},
    {"true", Token(Token::LiteralBool, "true")},
    {"false", Token(Token::LiteralBool, "false")},
    {"for", Token(Token::For, "for")},
    {"while", Token(Token::While, "while")},
    {"do", Token(Token::Do, "do")},
    {"if", Token(Token::If, "if")},
    {"else", Token(Token::Else, "else")},
    {"elif", Token(Token::Elif, "elif")},
    //More keywords here
    {"{", Token(Token::LeftBrace, "{")},
    {"}", Token(Token::RightBrace, "}")},
    {"(", Token(Token::LeftParen, "(")},
    {")", Token(Token::RightParen, ")")},
    {"[", Token(Token::LeftBracket, "[")},
    {"]", Token(Token::RightBracket, "]")},
    {",", Token(Token::Separator, ",")},
};

std::string Token::tokenTypeToString(Token::TokenType tokenType) {
    switch (tokenType) {
        case Token::Identifier: return "Identifier";
        case Token::Constant: return "Constant";
        case Token::Variable: return "Variable";
        case Token::Pointer: return "Pointer";
        case Token::LiteralStr: return "LiteralStr";
        case Token::LiteralNum: return "LiteralNum";
        case Token::LiteralBool: return "LiteralBool";
        case Token::LeftBracket: return "LeftBracket";
        case Token::RightBracket: return "RightBracket";
        case Token::LeftParen: return "LeftParen";
        case Token::RightParen: return "RightParen";
        case Token::LeftBrace: return "LeftBrace";
        case Token::RightBrace: return "RightBrace";
        case Token::BinaryOperator: return "BinaryOperator";
        case Token::UnaryOperator: return "UnaryOperator";
        case Token::AccessOperator: return "AccessOperator";
        case Token::Separator: return "Separator";
        case Token::If: return "If";
        case Token::Else: return "Else";
        case Token::Elif: return "Elif";
        case Token::For: return "For";
        case Token::While: return "While";
        case Token::Do: return "Do";
        case Token::Procedure: return "Procedure";
        case Token::Return: return "Return";
        case Token::Unknown: return "Unknown";
        case Token::Start: return "Start";
        case Token::End: return "End";
    }
}

Token Token::retrieveTokenFromKeyword(std::string kw) {
    auto value = Keywords.find(kw);
    if (value != Keywords.end()) {
        return value->second;
    }
    return Token(Token::Unknown, "");
}

Token::Token(TokenType type, std::string data) {
    this->type = type;
    this->data = data;

    this->StartCol = 0;
    this->EndCol = 0;
    this->StartLine = 0;
    this->EndLine = 0;
}