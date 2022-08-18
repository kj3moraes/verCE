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

#ifndef __SCAN_FAILURE_H__
#define __SCAN_FAILURE_H__
class ScanningFailure {

    std::string message;

    public:
        ScanningFailure(std::string message);

        const std::string what() const;
};

#endif // __SCAN_FAILURE_H__