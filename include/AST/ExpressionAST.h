#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <string>

using namespace llvm;
class ExpressionAST {
    std::string value;

    public:
        virtual ~ExpressionAST() {}
        virtual Value *codegen() = 0;
};

#endif // __EXPR_AST_H__
