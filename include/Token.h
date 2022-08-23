#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <iostream>
#include <string>
#include <vector>

/* The character that indicates that a comment follows */
#define COMMENT_INIT '#'

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
    COMMA,
    DOT,
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
