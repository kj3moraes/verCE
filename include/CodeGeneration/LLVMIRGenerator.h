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

        void *logIRGenerationError(std::string errorMsg) const;

        /**
         * @brief Generates the IR for a binary operation passed in via the AST
         * and stores it in the Module.
         * 
         * @param[in] ast The root of the Binary Operation AST.
         * @return Value* - 
         */
        Value *visitBinaryOp(const BinaryExpressionAST *ast) const override;
        
        /**
         * @brief Generates the IR for a number passed in via the AST and stores
         * it in the Module.
         * 
         * @param[in] ast 
         * @return Value* - 
         */
        Value *visitNumber(const NumberExpressionAST *ast) const override;
        Value *visitVariable(const VariableExpressionAST *ast) const override;
        Value *visitCallExpr(const CallExpressionAST *ast) const override;
        Function *visitPrototype(const PrototypeAST *ast) const override;
        Function *visitFunctionDef(const FunctionAST *ast) override;
    
    public:
        LLVMIRGenerator();
        ~LLVMIRGenerator();

        void generateIR(const std::unique_ptr<NodeAST> &root);
        
        void printIR() const;
};

#endif
