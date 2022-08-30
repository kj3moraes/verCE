#ifndef __IR_CODE_GENERATOR_H__
#define __IR_CODE_GENERATOR_H__

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

using namespace llvm;

class IRCodeGenerator : public Visitor {
    private:
        LLVMContext TheContext;
        IRBuilder<> Builder(LLVMContext TheContext);
        std::unique_ptr<Module> TheModule;
        std::map<std::string, Value *> NamedValues;


};

#endif