#ifndef __BINARY_OP_AST_H__
#define __BINARY_OP_AST_H__

#include <cmath>
#include <memory>

#include "ExpressionAST.h"

class BinaryExprAST : public ExpressionAST {
    char op;
    std::unique_ptr<ExpressionAST> LHS, RHS;

    public:
        BinaryExprAST(char Op, 
                      std::unique_ptr<ExpressionAST> LHS,
                      std::unique_ptr<ExpressionAST> RHS) : op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

#endif