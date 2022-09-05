#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include <string>

#include "../CodeGeneration/Visitor.h"

using namespace llvm;
class ExpressionAST {
    std::string value;

    public:
        virtual ~ExpressionAST() {}
        virtual Value *accept(Visitor *gen) = 0;
};

#endif // __EXPR_AST_H__
