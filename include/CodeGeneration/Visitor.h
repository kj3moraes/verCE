#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "../AST.h"
#include "LLVMIncludes.h"

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

        virtual Value *visitBinaryOp(const BinaryExpressionAST *ast) const = 0;
        virtual Value *visitNumber(const NumberExpressionAST *ast) const = 0;
        virtual Value *visitVariable(const VariableExpressionAST *ast) const = 0;
        virtual Value *visitPrototype(const PrototypeAST *ast) const = 0;
        virtual Value *visitCallExpr(const CallExpressionAST *ast) const = 0;
        virtual Value *visitFunctionDef(const FunctionAST *ast) const = 0;
};

#endif // __VISITOR_H__

#ifndef __CODE_GENERATION_FAILURE_H__
#define __CODE_GENERATION_FAILURE_H__

class CodeGenerationFailure {
    std::string message;

    public:
        CodeGenerationFailure(const std::string& message) : message("ERROR (codegen): " + message) {}

        std::string what() const { return message; }
};

#endif