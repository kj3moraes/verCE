#include <string>
#include <utility>
#include "CodeGeneration/JITCompiler.h"

static unsigned long anon_expression_counter = 0;

JITCompiler::JITCompiler() {
    TheJIT = std::make_unique<orc::KaleidoscopeJIT>();
}

double JITCompiler::analyseTopLevelExpression(std::unique_ptr<llvm::Module> module) {
    
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // JIT the module containing the anonymous expression, keeping a handle so
    // we can free it later.
    auto H = TheJIT->addModule(std::move(module));

    // Search the JIT for the __anon_expr symbol.
    auto ExprSymbol = TheJIT->findSymbol("__anon_expr" + std::to_string(anon_expression_counter));
    assert(ExprSymbol && "Function not found");
    anon_expression_counter++;

    // Get the symbol's address and cast it to the right type (takes no
    // arguments, returns a double) so we can call it as a native function.
    double (*FP)() = (double (*)())(intptr_t)cantFail(ExprSymbol.getAddress());
    fprintf(stderr, "Evaluated to %f\n", FP());

    // Delete the anonymous expression module from the JIT.
    TheJIT->removeModule(H);

    return FP();
}