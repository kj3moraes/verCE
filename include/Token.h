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
    WHITESPACE,
};

class Token {

    private:
        Kind kind;
        std::string value;
    
    public:
        Token(Kind kind, std::string value) : kind(kind), value(value) {}

        Kind getKind() const; 
        const std::string getValue() const; 
};

std::ostream &operator<<(std::ostream &out, const Token &token);

#endif // __TOKEN_H__


#ifndef __SCAN_FAIL_H__
#define __SCAN_FAIL_H__
class ScanningFailure {

    std::string message;

    public:
        ScanningFailure(std::string message) : message(message) {}
        const std::string waht() const;
};
#endif // __SCAN_FAIL_H__