#include <vector>

#include <Symbol.hpp>
#include <Token.hpp>
#include <AST.hpp>

AST::ASTNode::ASTNode(Token *token, AST::Type type) {
    this->token = token;
    this->type = type;
}

AST::AST() {
    this->head = new ASTNode(nullptr, AST::BlockDeclaration);
};

AST::ASTNode* AST::getHead() {
    return this->head;
}