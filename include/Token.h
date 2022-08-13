#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <iostream>
#include <string>
#include <vector>

enum Kind {
    ID = 0,
    NUM,
    PLUS,
    MINUS,
    STAR,
    BECOMES,
    EQ,
    LT,
    LPAREN,
    RPAREN,
    DEF,
    EXTERN,
    WHITESPACE,
};

class Token {

    private:
        Kind kind;
        std::string lexeme;
    
    public:
        Token(Kind kind, std::string value) : kind(kind), lexeme(value) {}

        Kind getKind() const; 
        const std::string getLexeme() const; 
};

std::ostream &operator<<(std::ostream &out, const Token &token);

#endif // __TOKEN_H__


class ScanningFailure {

    std::string message;

    public:
        ScanningFailure(std::string message) : message(message) {}

        const std::string what() const;
};
