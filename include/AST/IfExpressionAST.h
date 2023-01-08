#ifndef __IF_EXPRESSION_AST_H__
#define __IF_EXPRESSION_AST_H__

#include <memory>

#include "NodeAST.h"
#include "ExpressionAST.h"
#include "../CodeGeneration.h" 
class Visitor;

class IfExpressionAST : public ExpressionAST {
    std::unique_ptr<ExpressionAST> Cond, Then, Else;

    public:
        IfExpressionAST(std::unique_ptr<ExpressionAST> Cond,
                        std::unique_ptr<ExpressionAST> Then,
                        std::unique_ptr<ExpressionAST> Else)
                        : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}
        
        ~IfExpressionAST() {}

        const std::unique_ptr<ExpressionAST> &getCondition() const { return Cond; }
        const std::unique_ptr<ExpressionAST> &getThen() const { return Then; }
        const std::unique_ptr<ExpressionAST> &getElse() const { return Else; }

        Value *accept(Visitor *gen) override;
};

#endif