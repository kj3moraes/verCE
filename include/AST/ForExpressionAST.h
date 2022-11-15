#ifndef __FOR_EXPRESSION_AST_H__
#define __FOR_EXPRESSION_AST_H__

#include <memory>

#include "NodeAST.h"
#include "ExpressionAST.h"
#include "../CodeGeneration.h" 
class Visitor;

class ForExpressionAST : public ExpressionAST {
    std::string VarName;
    std::unique_ptr<ExpressionAST> Start, End, Step, Body;

    public:
        ForExpressionAST(const std::string &VarName, 
                        std::unique_ptr<ExpressionAST> Start,
                        std::unique_ptr<ExpressionAST> End, 
                        std::unique_ptr<ExpressionAST> Step,
                        std::unique_ptr<ExpressionAST> Body)
                : VarName(VarName), Start(std::move(Start)), End(std::move(End)),
                Step(std::move(Step)), Body(std::move(Body)) {}
        ~ForExpressionAST() { }

         Value *accept(Visitor *gen) override;
};

#endif
