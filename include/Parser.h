#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "Lexer.h"
#include "AST.h"

class Parser {
    
    std::unique_ptr<PrototypeAST> parseExtern();

    std::unique_ptr<ExpressionAST> parseExpression();

    std::unique_ptr<FunctionAST> parseDefintion();
    
    std::unique_ptr<FunctionAST> parseTopLevelExpression();

    std::unique_ptr<PrototypeAST> parsePrototypeExpression();

    public:
        Parser();
        ~Parser();

        std::unique_ptr<ExpressionAST> parseInput(const std::vector<Token>& input);      
};

#endif // __PARSER_H__