#include "Token.h"
#include "Parser.h"

std::map<Kind, int> Parser::binaryOperatorPrecedence = {
    {LT, 10},
    {PLUS, 20},
    {MINUS, 20},
    {STAR, 40},
    {SLASH, 40},
};

Parser::~Parser() {}

void Parser::advance() {
    ++currentTokenIndex;
    currentToken = tokens[currentTokenIndex];
}

int Parser::getTokenPrecedence() {
    if (binaryOperatorPrecedence.find(currentToken.getKind()) != binaryOperatorPrecedence.end()) {
        return binaryOperatorPrecedence[currentToken.getKind()];
    }
    return -1;
}

void Parser::logParsingError(const std::string errorMsg) const {
    std::cerr << "ERROR (Parsing): " << errorMsg << std::endl;
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
        logParsingError("Expected ')'");
        return nullptr;
    }
    advance();
    return V;
}


std::unique_ptr<ExpressionAST> Parser::parseIdentifierExpression() {
    std::string idName = currentToken.getLexeme();

    advance();

    // CASE 1: Simple variable reference.
    if (currentToken.getKind() != LPAREN)
        return std::make_unique<VariableExpressionAST>(idName);
    

    // CASE 2: Function call.
    advance(); // consume the '('
    std::vector<std::unique_ptr<ExpressionAST>> args;
    if (currentToken.getKind() != RPAREN) {
        while (currentToken.getKind() != RPAREN) {
            auto arg = parseExpression();
            if (!arg) {
                logParsingError("expected an expression");
                return nullptr;
            }

            args.push_back(std::move(arg));
            
            if (currentToken.getKind() != COMMA) {
                logParsingError("expected ',' or ')' after argument");
                return nullptr;
            }
            advance();
        }
    }
    advance(); // Consume the ')'

    return std::make_unique<CallExpressionAST>(idName, std::move(args));
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
            logParsingError("Unknown token when expecting an expression");
            return nullptr;
    }
}


std::unique_ptr<ExpressionAST> Parser::parseBinaryOperatorRHS(int precedence, std::unique_ptr<ExpressionAST> lhs) {

    while (true) {
        int tokenPrecedence = getTokenPrecedence();
        
        // CASE 1:
        if (tokenPrecedence < precedence) {
            break;
        }

        // CASE 2: IS A Binary operator.
        //      a) Pra
        Token binaryOp = currentToken;
        advance();

        auto RHS = parsePrimary();
        if (!RHS) 
            return nullptr;

        int nextPrecedence = getTokenPrecedence();
        if (tokenPrecedence < nextPrecedence) {
            RHS = parseBinaryOperatorRHS(tokenPrecedence + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        lhs = std::make_unique<BinaryExpressionAST>(binaryOp, std::move(lhs), std::move(RHS));
    }
    return lhs;
}


std::unique_ptr<NumberExpressionAST> Parser::parseNumberExpression() {
    double number = std::stod(currentToken.getLexeme());
    auto result = std::make_unique<NumberExpressionAST>(number);
    advance();
    return result;
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


std::unique_ptr<PrototypeAST> Parser::parsePrototypeExpression() {
    if (currentToken.getKind() != Kind::ID) {
        logParsingError("Expected function name in prototype");
        return nullptr;
    }

    std::string functionName = currentToken.getLexeme();
    advance();

    if (currentToken.getKind() != Kind::LPAREN) {
        logParsingError("Expected a '(' in the prototype");
        return nullptr;
    }

    std::vector<std::string> argumentNames;
    advance();
    while (currentToken.getKind() == Kind::ID) {
        argumentNames.push_back(currentToken.getLexeme());
        advance();
    }

    if (currentToken.getKind() != Kind::RPAREN) {
        logParsingError("Expected a ')' in the prototype");
        return nullptr;
    }

    advance();
    
    return std::make_unique<PrototypeAST>(functionName, std::move(argumentNames));
}

std::unique_ptr<NodeAST> Parser::parseInput() {

    while (currentToken.getKind() != Kind::END_OF_FILE) {
        switch (currentToken.getKind()) {
            case Kind::DEF:
            {
                std::cout << "Handling definition" << std::endl;
                const auto a = parseDefintion();
                std::cout << currentToken << std::endl;
                break;
            }
                
            case Kind::EXTERN:
            {
                std::cout << "Handling extern" << std::endl;
                const auto a = parseExtern();
                break;
            }

            default:
                std::cout << "Handling top level expression" << std::endl;
                const auto a = parseTopLevelExpression();
                break;
        }
    }
    return nullptr;
}
