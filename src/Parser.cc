#include "Parser.h"

const std::map<char, int> Parser::binaryOperatorPrecedence = {
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40},
    {'/', 40},
};

Parser::~Parser() {}

void Parser::advance() {
    ++currentTokenIndex;
    currentToken = tokens[currentTokenIndex];
}

std::unique_ptr<ExpressionAST> Parser::parseExpression() {
    auto LHS = parsePrimary();
    if (!LHS)
        return nullptr;
    
    return parseBinaryOperatorRHS(0, std::move(LHS));
}


std::unique_ptr<ExpressionAST> Parser::parseParenthesisExpression() {
    advance();
    auto V = parseExpression();
    if (!V)
        return nullptr;
    
    if (currentToken.getKind() != RPAREN) {
        throw CompilationFailure("expected a ')'");
        return nullptr;
    }
    advance();
    return V;
}


std::unique_ptr<ExpressionAST> Parser::parseIdentifierExpression() {

}


std::unique_ptr<ExpressionAST> Parser::parsePrimary() {
    switch(currentToken.getKind()) {
        case Kind::NUM:
            return parseNumberExpression();
        case Kind::ID:
            return parseIdentifierExpression();
        case Kind::LPAREN:
            return parseParenthesisExpression();
        default:
            throw CompilationFailure("Unknown token when expecting an expression");
            return nullptr;
    }
}


std::unique_ptr<ExpressionAST> Parser::parseBinaryOperatorRHS(int precedence, std::unique_ptr<ExpressionAST> lhs) {
    
}


std::unique_ptr<NumberExpressionAST> Parser::parseNumberExpression() {
    auto result = std::make_unique<NumberExpressionAST>(currentToken);
    advance();
    return std::move(result);
}


std::unique_ptr<FunctionAST> Parser::parseDefintion() {
    advance();
    auto prototype = parsePrototypeExpression();
    if (!prototype)
        return nullptr;
    
    if (auto E = parseExpression()) {
        return std::make_unique<FunctionAST>(std::move(prototype), std::move(E));
    }
    return nullptr;
}


std::unique_ptr<FunctionAST> Parser::parseTopLevelExpression() {
    if (auto E = parseExpression()) {
        // Make an anonymous prototype.
        auto prototype = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(prototype), std::move(E));
    }
    return nullptr;
}


std::unique_ptr<PrototypeAST> Parser::parseExtern() {
    advance();
    return parsePrototypeExpression();
}

