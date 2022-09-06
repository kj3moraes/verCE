#ifndef __FUNCTION_CALL_AST_H__
#define __FUNCTION_CALL_AST_H__

#include <memory>
#include <string>
#include <vector>

#include "ExpressionAST.h"
#include "../CodeGeneration.h"

class CallExpressionAST : public ExpressionAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExpressionAST>> Args;

    public:
        CallExpressionAST(const std::string &Callee,
                    std::vector<std::unique_ptr<ExpressionAST>> Args)
            : Callee(Callee), Args(std::move(Args)) {}


        Value *accept(const Visitor *gen) override;
};

#endif // __FUNCTION_CALL_AST_H__
