#ifndef __FUNCTION_DEF_AST_H__
#define __FUNCTION_DEF_AST_H__

#include <memory>

#include "NodeAST.h"
#include "ExpressionAST.h"
#include "PrototypeAST.h"
#include "../CodeGeneration.h" 
class Visitor;

class FunctionAST : public NodeAST {
    std::unique_ptr<PrototypeAST> prototype;    
    std::unique_ptr<ExpressionAST> body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                    std::unique_ptr<ExpressionAST> Body)
            : prototype(std::move(Proto)), body(std::move(Body)) {}
        
        ~FunctionAST() { };

        PrototypeAST *getPrototype() const { return prototype.get(); }
        ExpressionAST *getBody() const { return body.get(); }

        Function *accept(Visitor *gen);
};

#endif // __FUNCTION_DEF_AST_H__
