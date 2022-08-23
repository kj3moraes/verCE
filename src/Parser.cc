#include "Parser.h"

const std::map<char, int> Parser::binaryOperatorPrecedence = {
    {'+', 20},
    {'-', 20},
    {'*', 40},
    {'/', 40},
};


Parser::Parser() {
}

Parser::~Parser() {
}

