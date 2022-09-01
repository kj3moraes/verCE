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

        Value *visit(BinaryExpressionAST *ast) override;
        Value *visit(NumberExpressionAST *ast) override;
        Value *visit(VariableExpressionAST *ast) override;
        Value *visit(PrototypeAST *ast) override;
        Value *visit(CallExpressionAST *ast) override;
        Value *visit(FunctionAST *ast) override;


};

#endif