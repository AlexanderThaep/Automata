#include <Token.hpp>
#include <Symbol.hpp>

std::unordered_map<std::string, Symbol> Symbol::symbolTable;

Symbol::Symbol(Token token) : Token(token) {
    
};