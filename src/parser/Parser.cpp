#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <Lexer.hpp>
#include <Token.hpp>
#include <Symbol.hpp>
#include <Parser.hpp>
#include <FileIO.hpp>
#include <AST.hpp>

Parser::Parser() {
    this->ast = new AST();
}

void parseTerm(std::vector<Token>::iterator &tokenIter) {
    Token current = *tokenIter;
    Token lookahead = *(tokenIter + 1);

    switch (current.type) {
        case Token::UnaryOperator:
            if (lookahead.type == Token::Identifier) {
                // operate
                return;
            }
            if (lookahead.type == Token::LeftParen) {
                parseExpression(tokenIter += 1);
                return;
            }
        case Token::LiteralBool:
        case Token::LiteralNum:
        case Token::LiteralStr:
        case Token::Identifier:
            // term
            return;
        case Token::LeftParen:
            parseExpression(tokenIter += 1);
            return;
    }
}

void parseExpression(std::vector<Token>::iterator &tokenIter) {
    Token current = *tokenIter;
    Token lookahead = *(tokenIter + 1);

    while (current.type != Token::RightParen) {

        current = *tokenIter;
        lookahead = *(tokenIter + 1);

        parseTerm(tokenIter);
        if (lookahead.type == Token::BinaryOperator) {
            // operate
            tokenIter++;
            continue;
        }
        break;
    }

    tokenIter++;
}

void parseDeclaration(std::vector<Token>::iterator &tokenIter) {
    Token current = *tokenIter;
    Token lookahead = *(tokenIter + 1);

    switch (current.type) {
        case Token::BinaryOperator:
            if (current.data == "=") {
                parseExpression(tokenIter += 1);
            }
            return;
        default:
            return;
    }
}

void parseBlock(std::vector<Token>::iterator &tokenIter) {

    Token current = *tokenIter;
    Token lookahead = *(tokenIter + 1);

    while (current.type != Token::RightBrace || current.type != Token::End) {

        current = *tokenIter;
        lookahead = *(tokenIter + 1);

        switch (current.type) {
            case Token::Constant:
            case Token::Variable:
            case Token::Procedure:
                if (lookahead.type == Token::Identifier) {
                    parseDeclaration(tokenIter += 2);
                }
                return;
            case Token::Identifier:
                if (lookahead.type == Token::LeftParen) {
                    tokenIter += 2;
                    // parse function args
                }
                parseDeclaration(tokenIter += 1);
                return;
            default:
                return;
        }
    }
}

void Parser::parse(Lexer *lxr) {
    std::vector<Token> tokens = lxr->getTokens();
    auto tokenIter = tokens.begin();

    if ((*tokenIter).type == Token::Start) tokenIter++;

    parseBlock(tokenIter);
}