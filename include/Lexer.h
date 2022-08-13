#ifndef __LEXER_H__
#define __LEXER_H__

#include <iostream>
#include <string>
#include "Token.h"

class Lexer {
    public:
        Lexer(const std::string &input);
        ~Lexer();

        Token getNextToken();
        std::string getIdentifierString();
        double getNumberValue();
};
#endif // __LEXER_H__