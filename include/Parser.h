#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "AST.h"

class Parser {
    
    // Define the operator precedence for the binary operators.
    const static std::map<char, int> binaryOperatorPrecedence;

    std::unique_ptr<PrototypeAST> parseExtern();

    std::unique_ptr<ExpressionAST> parseExpression();

    std::unique_ptr<ExpressionAST> parseParenthesisExpression();

    std::unique_ptr<ExpressionAST> parseIdentifierExpression();

    std::unique_ptr<ExpressionAST> parsePrimary();

    std::unique_ptr<ExpressionAST> parseBinaryOperatorRHS(int precedence, std::unique_ptr<ExpressionAST> lhs);

    std::unique_ptr<NumberExprAST> parseNumberExpression();

    std::unique_ptr<FunctionAST> parseDefintion();
    
    std::unique_ptr<FunctionAST> parseTopLevelExpression();

    std::unique_ptr<PrototypeAST> parsePrototypeExpression();

    public:
        Parser();
        ~Parser();

        std::unique_ptr<ExpressionAST> parseInput(const std::vector<Token>& input);      
};

#endif // __PARSER_H__


#ifndef __COMPILATION_FAILURE_H__
#define __COMPILATION_FAILURE_H__

class CompilationFailure {
    std::string message;

    public:
        CompilationFailure(const std::string& message) : message(message) {}

        const std::string what() const { return message; }
};

#endif
