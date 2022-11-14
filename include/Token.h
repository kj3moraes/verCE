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
    SLASH,
    MODULO,
    BECOMES,
    EQ,
    LT,
    LPAREN,
    RPAREN,
    COMMA,
    SEMI,
    DOT,
    DEF,
    EXTERN,
    IF,
    FOR,
    THEN,
    ELSE,
    WHITESPACE,
    END_OF_FILE,
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

bool operator==(const Token &lhs, const Token &rhs);

bool operator!=(const Token &lhs, const Token &rhs);

#endif // __TOKEN_H__
