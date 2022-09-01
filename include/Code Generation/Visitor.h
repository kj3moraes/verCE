#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "../AST.h"
#include "LLVMIncludes.h"

class Visitor {
    public:
        virtual ~Visitor() {}

        virtual Value *visit(BinaryExpressionAST *ast) = 0;
        virtual Value *visit(NumberExpressionAST *ast) = 0;
        virtual Value *visit(VariableExpressionAST *ast) = 0;
        virtual Value *visit(PrototypeAST *ast) = 0;
        virtual Value *visit(CallExpressionAST *ast) = 0;
        virtual Value *visit(FunctionAST *ast) = 0;
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