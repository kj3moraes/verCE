#include "JITCompiler.h"

double JITCompiler::analyseTopLevelExpression(std::unique_ptr<llvm::Module> module) {
    
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    TheJIT = ExitOnErr(KaleidoscopeJIT::Create());

    // JIT the module containing the anonymous expression, keeping a handle so
    // we can free it later.
    auto H = TheJIT->addModule(std::move(module));
    InitializeModuleAndPassManager();

    // Search the JIT for the __anon_expr symbol.
    auto ExprSymbol = TheJIT->findSymbol("__anon_expr");
    assert(ExprSymbol && "Function not found");

    // Get the symbol's address and cast it to the right type (takes no
    // arguments, returns a double) so we can call it as a native function.
    double (*FP)() = (double (*)())(intptr_t)ExprSymbol.getAddress();
    fprintf(stderr, "Evaluated to %f\n", FP());

    // Delete the anonymous expression module from the JIT.
    TheJIT->removeModule(H);
}