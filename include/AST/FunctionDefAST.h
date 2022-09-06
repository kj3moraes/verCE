#ifndef __FUNCTION_DEF_AST_H__
#define __FUNCTION_DEF_AST_H__

#include <memory>

#include "ExpressionAST.h"
#include "PrototypeAST.h"
#include "../CodeGeneration.h" 
class Visitor;

class FunctionAST {
    std::unique_ptr<PrototypeAST> Proto;    
    std::unique_ptr<ExpressionAST> Body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                    std::unique_ptr<ExpressionAST> Body)
            : Proto(std::move(Proto)), Body(std::move(Body)) {}
        
        Value *accept(const Visitor *gen);
};

#endif // __FUNCTION_DEF_AST_H__
