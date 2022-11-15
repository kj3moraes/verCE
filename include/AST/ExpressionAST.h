#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include <string>

#include "NodeAST.h"

class Visitor;
#include "../CodeGeneration.h"
using namespace llvm;

class ExpressionAST : public NodeAST {
    std::string value;

    public:
        virtual ~ExpressionAST() {}
        virtual Value *accept(Visitor *gen) = 0;
};

#endif // __EXPR_AST_H__
