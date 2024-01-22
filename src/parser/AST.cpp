#include <vector>

#include <Symbol.hpp>
#include <Token.hpp>
#include <AST.hpp>

AST::ASTNode::ASTNode(AST::Type type) {
    // TODO
}

AST::AST() {
    ASTNode *node = new ASTNode(AST::Type::BlockDeclaration);
    this->nodes.push_back(*node);
};