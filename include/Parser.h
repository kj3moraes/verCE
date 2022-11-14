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
    
    // The token list for the entire program as a reference
    const std::vector<Token> &tokens;
    
    // Tracking for the current token. 
    Token currentToken;
    unsigned long currentTokenIndex;

    // Define the operator precedence for the binary operators.
    static std::map<Kind, int> binaryOperatorPrecedence;

    /**
     * @brief Increments the tracking information to point to
     * the next token in the token vector.
     */
    void advance();
    
    /**
     * @brief Get the Token of the current token. The respective
     * values are defined in the binaryOperatorPrecedence map.
     * @return int - the token precedence
     */
    int getTokenPrecedence();

    std::unique_ptr<ExpressionAST> parseExpression();

    std::unique_ptr<ExpressionAST> parseParenthesisExpression();

    std::unique_ptr<ExpressionAST> parseIdentifierExpression();

    std::unique_ptr<ExpressionAST> parsePrimary();

    std::unique_ptr<ExpressionAST> parseIfExpression();

    std::unique_ptr<ExpressionAST> parseForExpression();

    std::unique_ptr<ExpressionAST> parseBinaryOperatorRHS(int precedence, std::unique_ptr<ExpressionAST> lhs);

    std::unique_ptr<NumberExpressionAST> parseNumberExpression();

    std::unique_ptr<FunctionAST> parseDefintion();
    
    std::unique_ptr<FunctionAST> parseTopLevelExpression();

    std::unique_ptr<PrototypeAST> parseExtern();

    std::unique_ptr<PrototypeAST> parsePrototypeExpression();

    public:

        /**
         * @brief Construct a new Parser object with the reference
         * to the token list for the entire program.
         * @param[in] tokens is the token list for the entire program.
         */
        Parser(const std::vector<Token> &tokens) : tokens(tokens), currentToken(tokens[0]), currentTokenIndex(0) {}
        Parser(const std::vector<Token> &&) = delete; // prevents rvalue binding

        ~Parser();

        /**
         * @brief Builds the AST for the entire program specified by the
         * Token vector list and returns the root of the tree.
         * @return std::unique_ptr<ExpressionAST> is the root of the AST built from the token list.
         */
        std::unique_ptr<NodeAST> parseInput();      
};

#endif // __PARSER_H__
