#ifndef __LLVM_IR_CODE_GENERATOR_H__
#define __LLVM_IR_CODE_GENERATOR_H__

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../AST.h"
#include "../CodeGeneration.h"
#include "Visitor.h"

using namespace llvm;

class LLVMIRGenerator : public Visitor {
    private:
        std::unique_ptr<LLVMContext> TheContext;
        std::unique_ptr<IRBuilder<>> Builder;
        std::unique_ptr<Module> TheModule;
        std::map<std::string, Value *> NamedValues;

        Value *visitBinaryOp(const BinaryExpressionAST *ast) const override;
        Value *visitNumber(const NumberExpressionAST *ast) const override;
        Value *visitVariable(const VariableExpressionAST *ast) const override;
        Value *visitCallExpr(const CallExpressionAST *ast) const override;
        Function *visitPrototype(const PrototypeAST *ast) const override;
        Function *visitFunctionDef(const FunctionAST *ast) override;
    
    public:
        LLVMIRGenerator();
        ~LLVMIRGenerator();

        void generateCode(const std::vector<std::unique_ptr<ExpressionAST>>& ast);
};

#endif
