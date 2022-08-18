#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <memory>

#include "AST.h"

class Parser {
    public :
        Parser(const std::string& input);
        ~Parser();

        ExpressionAST* parse();
}

#endif // __PARSER_H__