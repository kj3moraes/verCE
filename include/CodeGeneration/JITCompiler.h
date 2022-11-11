#ifndef __JIT_COMPILER_H__
#define __JIT_COMPILER_H__

#include <algorithm>
#include <memory>

#include "../KaleidoscopeJIT.h"
#include "../CodeGeneration.h"

class JITCompiler {
    std::unique_ptr<llvm::orc::KaleidoscopeJIT> TheJIT;

    public:
        double analyseTopLevelExpression(std::unique_ptr<llvm::Module> module);
};
#endif