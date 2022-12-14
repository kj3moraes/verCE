#ifndef __BINARY_OP_AST_H__
#define __BINARY_OP_AST_H__

#include <cmath>
#include <memory>

#include "../Token.h"
#include "ExpressionAST.h"
#include "../CodeGeneration.h"
using namespace llvm;

class BinaryExpressionAST : public ExpressionAST {
    Token op;
    std::unique_ptr<ExpressionAST> LHS, RHS;

    public:
        BinaryExpressionAST(Token Op, 
                      std::unique_ptr<ExpressionAST> LHS,
                      std::unique_ptr<ExpressionAST> RHS) : op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

        const Token getOperator() const { return op; }

        ExpressionAST *getLHS() const { return LHS.get(); }
        ExpressionAST *getRHS() const { return RHS.get(); }

        Value *accept(const Visitor *gen) override;
};

#endif
