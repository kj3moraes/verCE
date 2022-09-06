#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include <string>

class Visitor;
#include "../CodeGeneration.h"
using namespace llvm;

class ExpressionAST {
    std::string value;

    public:
        virtual ~ExpressionAST() {}
        virtual Value *accept(const Visitor *gen) = 0;
};

#endif // __EXPR_AST_H__
