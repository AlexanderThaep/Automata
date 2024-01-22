#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <Lexer.hpp>
#include <Token.hpp>
#include <Symbol.hpp>
#include <FileIO.hpp>

static const char COMMENT_DELIMITER = '#';

Lexer::Lexer() {
    this->lineNumber = 0;
    this->lineOffset = 0;
    this->colNumber = 0;
    this->offset = 0;
    //Nothing
    //LL(1) lexer, I spent way too much time on this, making it elegant
    //With token streaming
}

std::vector<Token> Lexer::getTokens() {
    return this->tokens;
}

Token Lexer::getNextToken() {

    if (this->tokens.empty()) {
        Token token = Token(Token::Start, "Start");
        tokens.push_back(token);
        return token;
    }

    if (!this->input.empty()) {

        int &i = this->offset;

        while (i < this->input.size()) {

            char curChar = this->input[i];
            char nextChar = at(i + 1);

            this->colNumber = i - this->lineOffset;
            
            switch (curChar) {
                //Skip comments
                case '#':
                    do {
                        i++;
                    }
                    while (i < this->input.size() && this->input[i] != COMMENT_DELIMITER);
                    break;
                //Whitespace is dealt with by skipping
                case '\n':
                    this->lineNumber++;
                    this->lineOffset = i;
                case ' ':
                case '\t':
                case '\f':
                case '\v':
                case '\r':
                    i++;
                    continue;
                //Strings with interchangeable options for enclosing quotes
                case '\'':
                case '\"':
                    handleString(i);
                    break;
                //Words starting with A-Z, a-z, or _
                case 'A' ... 'Z':
                case 'a' ... 'z':
                case '_':
                    handleWord(i);
                    break;
                //Numbers starting with digits
                case '0' ... '9':
                    handleDigits(i);
                    break;
                //Dot operator or numbers starting with .
                case '.':
                    switch (nextChar) {
                        case '0' ... '9':
                            this->currentString.push_back('0');
                            handleDigits(i);
                            break;
                        default:
                            pushToken(Token(Token::AccessOperator, "."));
                            break;
                    }
                    break;
                //All of these share [x=] where x is the character
                case '=':
                case '+':
                case '-':
                case '/':
                case '*':
                case '&':
                case '>':
                case '<':
                case '!':
                case '|':
                    handleOperators(i);
                    break;
                case '{':
                case '}':
                case '(':
                case ')':
                case '[':
                case ']':
                case ',':
                    this->currentString.push_back(curChar);
                    pushToken();
                    break;
                case '\0':
                    break;
                default:
                    pushToken(Token(Token::Unknown, std::string(1, curChar)));
                    break;
            }

            i++;
            Token &token = this->tokens.back();
            token.EndCol = i - this->lineOffset;
            token.EndLine = this->lineNumber;
            return token;
        }
    }

    Token token = Token(Token::End, "End");
    this->tokens.push_back(token);

    return token;
}

void Lexer::tokenize(std::string file_name="") {
    
    // tokenize(), tokenize("xyz.dog")
    this->reset();
    if (!file_name.empty()) fileToLexer(*this, file_name);
    if (this->input.empty()) return;

    Token token = Token(Token::Start, "Start");

    while (token.type != Token::End) {
        token = this->getNextToken();
    };

    this->tokens.push_back(token);
} 

void Lexer::reset() {
    this->input.clear();
    this->tokens.clear();
    this->lineNumber = 0;
    this->lineOffset = 0;
    this->colNumber = 0;
    this->offset = 0;
}

void Lexer::printTokens() {
    for (auto token : this->tokens) {
        std::cout 
        << Token::tokenTypeToString(token.type)
        << "\t\t" 
        << token.data 
        << "\t"
        << token.StartLine << "/" << token.StartCol 
        << " "
        << token.EndLine << "/" << token.EndCol
        << 
        std::endl;
    }
    for (auto symbol : Symbol::symbolTable) {
        std::cout 
        << symbol.second.data
        <<
        std::endl;
    }
}

void Lexer::stringToInput(std::string str) {
    this->input.append(str);
}

Token Lexer::matchKeyword() {
    Token token = Token::retrieveTokenFromKeyword(this->currentString);
    if (token.type == Token::Unknown) {
        token.type = Token::Identifier;
        token.data = this->currentString;

        Symbol::symbolTable.insert({this->currentString, Symbol(token)});
    }
    return token;
}

char Lexer::at(int index) {
    if (index < this->input.size()) {
        return this->input[index];
    }
    return '\0';
}

// I don't very much like the overloading
void Lexer::pushToken(Token token) {
    //Already got a token?
    token.StartLine = this->lineNumber;
    token.StartCol = this->colNumber;

    this->tokens.push_back(token);
    this->currentString.clear();        
}
void Lexer::pushToken() {
    //Do not try to match empty against the hash table
    if (!this->currentString.empty()) {
        Token token = matchKeyword();
        token.StartLine = this->lineNumber;
        token.StartCol = this->colNumber;

        this->tokens.push_back(token);
        this->currentString.clear();        
    }
}

void Lexer::handleOperators(int &index) {

    char curChar = this->input[index];
    char nextChar = at(index + 1);

    switch (curChar) {
        case '=':
            this->currentString.push_back('=');
            break;
        case '+':
            switch (nextChar) {
                case '+':
                    pushToken(Token(Token::UnaryOperator, "++"));
                    index++;
                    return;
            }
            this->currentString.push_back('+');
            break;
        case '-':
            switch (nextChar) {
                case '-':
                    pushToken(Token(Token::UnaryOperator, "--"));
                    index++;
                    return;
                case '>':
                    pushToken(Token(Token::AccessOperator, "->"));
                    index++;
                    return; 
            }
            this->currentString.push_back('-');
            break;
        case '/':
            this->currentString.push_back('/');
            break;
        case '*':
            switch (nextChar) {
                case 'A' ... 'Z':
                case 'a' ... 'z':
                case '_':
                    pushToken(Token(Token::UnaryOperator, "*"));
                    return;
            }
            this->currentString.push_back('*');
            break;
        case '&':
            switch (nextChar) {
                case 'A' ... 'Z':
                case 'a' ... 'z':
                case '_':
                    pushToken(Token(Token::UnaryOperator, "&"));
                    return;
                case '&':
                    pushToken(Token(Token::BinaryOperator, "&&"));
                    index++;
                    return;  
            }
            this->currentString.push_back('&');
            return;
        case '>':
            switch (nextChar) {
                case '>':
                    pushToken(Token(Token::BinaryOperator, ">>"));
                    index++;
                    return;
            }
            this->currentString.push_back('>');
            break;
        case '<':
            switch (nextChar) {
                case '<':
                    pushToken(Token(Token::BinaryOperator, "<<"));
                    index++;
                    return;
            }     
            this->currentString.push_back('<');       
            break;
        case '!':
            if (nextChar != '=') {
                pushToken(Token(Token::UnaryOperator, "!"));
                index++;
                return;
            }
            this->currentString.push_back('!');       
            break;
        case '|':
            switch (nextChar) {
                case '|':
                    pushToken(Token(Token::BinaryOperator, "||"));
                    index++;
                    return;
            }   
            this->currentString.push_back('|');         
            break;
    }

    if (nextChar == '=') {
        this->currentString.push_back('=');
        pushToken(Token(Token::BinaryOperator, this->currentString));
        index++;
        return;
    }

    pushToken(Token(Token::BinaryOperator, this->currentString));
}

void Lexer::handleString(int &index) {
    //Advance past the ' or "
    index++;
    while (index < this->input.size()) {
        char c = this->input[index];
        switch (c) {
            // I choose to ignore octals
            case '\'':
            case '\"':
                //Interchangeable
                pushToken(Token(Token::LiteralStr, this->currentString));
                return;
            case '\\':
                switch (at(index + 1)) {
                    case 'b':
                        this->currentString.push_back('\b');
                        break;
                    case 't':
                        this->currentString.push_back('\t');
                        break;
                    case 'n':
                        this->currentString.push_back('\n');
                        break;
                    case 'f':
                        this->currentString.push_back('\f');
                        break;
                    case 'r':
                        this->currentString.push_back('\r');
                        break;
                    case 'a':
                        this->currentString.push_back('\a');
                        break;
                    case 'e':
                        this->currentString.push_back('\e');
                        break;
                    case '\"':
                        this->currentString.push_back('\"');
                        break;
                    case '\'':
                        this->currentString.push_back('\'');
                        break;
                    case '\\':
                        this->currentString.push_back('\\');
                        break;
                    case '0':
                        this->currentString.push_back('\0');
                        break;
                }
                //Move past the escape character \ //
                index++;
                break;
            default:
                this->currentString.push_back(c);
                break;
        }
        index++;
    }
}

void Lexer::handleWord(int &index) {
    while (index < this->input.size()) {
        char c = this->input[index];
        switch (c) {
            //Words can start with A-Z, a-z, or _ and then contain digits
            case 'A' ... 'Z':
            case 'a' ... 'z':
            case '0' ... '9':
            case '_':
                this->currentString.push_back(c);
                break;
            default:
                pushToken();
                //Quirk, we have to move back to the last valid letter
                index--;
                return;
        }
        index++;
    }
}

void Lexer::handleDigits(int &index) {

    //Numbers assumed integer until ., x, b
    bool alreadyDecimal = false;
    bool hexadecimal = false;
    bool binary = false;

    while (index < this->input.size()) {
        char c = this->input[index];
        switch (c) {
            //I choose to ignore octals
            case '0':
                if (index == 0 && (binary|hexadecimal) == false) {
                    switch (at(index + 1)) {
                        case 'b':
                            binary = true;
                            index += 2;
                            continue;
                        case 'x':
                            hexadecimal = true;
                            index += 2;
                            continue;
                    }
                }
                this->currentString.push_back(c);
                break;
            case '1' ... '9':
                //In binary sequence, numbers > 1 are treated as 1
                if (binary) {
                    c = '1';
                }
                this->currentString.push_back(c);
                break;
            case 'a' ... 'f':
            case 'A' ... 'F':
                if (hexadecimal) {
                    this->currentString.push_back(c);
                    break;
                }
                //Outside of a hexadecimal sequence, return
                pushToken(Token(Token::LiteralNum, this->currentString));
                index--;
                return;
            case '.':
                if (!alreadyDecimal && !(hexadecimal|binary)) {
                    alreadyDecimal = true;
                    this->currentString.push_back(c);
                }
                //First decimal point is included, rest are ignored
                break;
            case '_':
                //Skip over
                break;
            default:
                pushToken(Token(Token::LiteralNum, this->currentString));
                //Quirk, we have to move back to the last valid character
                index--;
                return;
        }
        index++;
    }
}