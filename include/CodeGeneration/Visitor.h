#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "../AST.h"
#include "../CodeGeneration.h"

using namespace llvm;

class ExpressionAST;
class BinaryExpressionAST;
class NumberExpressionAST;
class VariableExpressionAST;
class CallExpressionAST;
class FunctionAST;
class PrototypeAST;

class Visitor {
    public:
        virtual ~Visitor() {}

        virtual Value *visitBinaryOp(const BinaryExpressionAST *ast) = 0;
        virtual Value *visitNumber(const NumberExpressionAST *ast) = 0;
        virtual Value *visitVariable(const VariableExpressionAST *ast) = 0;
        virtual Value *visitCallExpr(const CallExpressionAST *ast) = 0;
        virtual Value *visitIfExpr(const IfExpressionAST *ast) = 0;
        virtual Value *visitForExpr(const ForExpressionAST *ast) = 0;
        virtual Function *visitPrototype(const PrototypeAST *ast) = 0;
        virtual Function *visitFunctionDef(const FunctionAST *ast) = 0;
};

#endif // __VISITOR_H__

