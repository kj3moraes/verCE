#ifndef __LLVM_IR_CODE_GENERATOR_H__
#define __LLVM_IR_CODE_GENERATOR_H__

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../AST.h"
#include "Visitor.h"
#include "LLVMIncludes.h"

using namespace llvm;

class LLVMIRCodeGenerator : public Visitor {
    private:
        std::unique_ptr<LLVMContext> TheContext;
        std::unique_ptr<IRBuilder<>> Builder;
        std::unique_ptr<Module> TheModule;
        std::map<std::string, Value *> NamedValues;

    public:
        LLVMIRCodeGenerator();
        ~LLVMIRCodeGenerator();

        Value *visitBinaryOp(const BinaryExpressionAST *ast) const override;
        Value *visitNumber(const NumberExpressionAST *ast) const override;
        Value *visitVariable(const VariableExpressionAST *ast) const override;
        Value *visitPrototype(const PrototypeAST *ast) const override;
        Value *visitCallExpr(const CallExpressionAST *ast) const override;
        Value *visitFunctionDef(const FunctionAST *ast) const override;


};

#endif