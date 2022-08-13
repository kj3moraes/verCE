#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>

enum Token {
    TOKEN_EOF = -1,

    // Commands
    TOKEN_DEF = -2,
    TOKEN_EXTERN = -3,

    // Primary
    TOKEN_IDENTIFIER = -4,
    TOKEN_NUMBER = -5,
};

static std::string IdentifierString;
static double NumberValue; 

#endif // __TOKEN_H__