#ifndef __FUNCTION_DEF_AST_H__
#define __FUNCTION_DEF_AST_H__

#include <memory>

#include "ExpressionAST.h"
#include "PrototypeAST.h"
#include "../CodeGeneration/Visitor.h"

class FunctionAST {
    std::unique_ptr<PrototypeAST> Proto;    
    std::unique_ptr<ExpressionAST> Body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                    std::unique_ptr<ExpressionAST> Body)
            : Proto(std::move(Proto)), Body(std::move(Body)) {}
        
        Value *accept(Visitor *gen) { return gen->visitFunctionDef(this);}
};

#endif // __FUNCTION_DEF_AST_H__
