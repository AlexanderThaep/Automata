#pragma once

#include <vector>

#include <Symbol.hpp>
#include <Token.hpp>

class AST {
private:
    enum Type {
        BlockDeclaration,
        VariableDeclaration,

    };

    struct ASTNode {
        AST::Type type;
        Token *token;
        std::vector<ASTNode> children;

        ASTNode(AST::Type type);
    };

    std::vector<ASTNode> nodes;

public:
    AST();
};