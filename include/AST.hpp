#pragma once

#include <vector>

#include <Symbol.hpp>
#include <Token.hpp>

class AST {
public:
    enum Type {
        BlockDeclaration,
        VariableDeclaration,
        VariableAddress,
        Plus,
        Minus,
        Assign,
        Value
    };

    enum Precedence {
        Equal,
        MinPlus,
        MultDiv,
        Binary,
        Unary,
        Function
    };

    struct ASTNode {
        AST::Type type;
        Token *token;
        std::vector<ASTNode*> children;

        ASTNode(Token *token, AST::Type type);
    };
    
    AST();
    ASTNode* getHead();
    
private:
    ASTNode *head;
};