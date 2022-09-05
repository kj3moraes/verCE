#include "CodeGeneration.h"

LLVMIRCodeGenerator::LLVMIRCodeGenerator() {
// Open a new context and module.
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);

  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}
    


Value *LLVMIRCodeGenerator::visitBinaryOp(const BinaryExpressionAST *ast) const {
    Value *lhs = ast->getLHS()->accept(this);
    Value *rhs = ast->getRHS()->accept(this);
    switch (ast->getOperator().getKind()) {
        case Kind::PLUS:
            return Builder->CreateAdd(lhs, rhs, "addtmp");
        case Kind::MINUS:
            return Builder->CreateSub(lhs, rhs, "subtmp");
        case Kind::STAR:
            return Builder->CreateMul(lhs, rhs, "multmp");
        case Kind::SLASH:
            return Builder->CreateSDiv(lhs, rhs, "divtmp");
        default:
            return nullptr;
    }
}

Value *LLVMIRCodeGenerator::visitNumber(const NumberExpressionAST *ast) const {
    return ConstantFP::get(*TheContext, APFloat(ast->getValue()));
}

