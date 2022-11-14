#ifndef __JIT_COMPILER_H__
#define __JIT_COMPILER_H__

#include <memory>

#include "../KaleidoscopeJIT.h"
#include "../CodeGeneration.h"

using namespace llvm;

class JITCompiler {
    std::unique_ptr<orc::KaleidoscopeJIT> TheJIT;

    public:
        JITCompiler();

        TargetMachine &getTargetMachine() const;
        double analyseTopLevelExpression(std::unique_ptr<Module> module);
};
#endif