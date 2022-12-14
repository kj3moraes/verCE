#include <utility>
#include "CodeGeneration/LLVMIRGenerator.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/// putchard - putchar that takes a double and returns 0.
extern "C" DLLEXPORT double putchard(double X) {
  fputc((char)X, stderr);
  return 0;
}

/// printd - printf that takes a double prints it as "%f\n", returning 0.
extern "C" DLLEXPORT double printd(double X) {
  fprintf(stderr, "%f\n", X);
  return 0;
}

static void *logIRGenerationError(std::string errorMsg) {
    std::cerr << "ERROR: (IR Generation) " << errorMsg << std::endl;
    return nullptr;
}

LLVMIRGenerator::LLVMIRGenerator() {

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // Open a new context and module.
    myJIT = std::make_unique<orc::KaleidoscopeJIT>();

    TheContext = std::make_unique<LLVMContext>();
    TheModule = std::make_unique<Module>("KEANE'S JIT.C", *TheContext);

    // Create a new builder for the module.
    Builder = std::make_unique<IRBuilder<>>(*TheContext);
    NamedValues = std::map<std::string, Value *>();

    // Create a new pass manager attached to it.
    TheFPM = std::make_unique<legacy::FunctionPassManager>(getModule());

    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();
}
    

LLVMIRGenerator::~LLVMIRGenerator() {}


Value *LLVMIRGenerator::visitVariable(const VariableExpressionAST *ast) const {
    // Look this variable up in the function.
    Value *V = NamedValues.at(ast->getName());
    if (!V)
        return (Value *)logIRGenerationError("Unknown variable name");
    return V;
}


Value *LLVMIRGenerator::visitBinaryOp(const BinaryExpressionAST *ast) const {
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
        case Kind::LT:
            lhs = Builder->CreateFCmpULT(lhs, rhs, "cmptmp");
            // Convert bool 0/1 to double 0.0 or 1.0
            return Builder->CreateUIToFP(lhs, Type::getDoubleTy(*TheContext), "booltmp");
        default:
            return nullptr;
    }
}


Value *LLVMIRGenerator::visitNumber(const NumberExpressionAST *ast) const {
    return ConstantFP::get(*TheContext, APFloat(ast->getValue()));
}


Value *LLVMIRGenerator::visitCallExpr(const CallExpressionAST *ast) const {
    // Look up the name in the global module table.
    Function *calleeF = TheModule->getFunction(ast->getCallee()); 

    if (!calleeF)
        return (Value *)logIRGenerationError("Unknown function referenced");

    if (calleeF->arg_size() != ast->getNumberOfArgs())
        return (Value *)logIRGenerationError("Incorrect # arguments passed");

    std::vector<Value *> argsV;
    for (unsigned long i = 0L, e = ast->getNumberOfArgs(); i != e; i++) {
        argsV.push_back(ast->getArgs()[i]->accept(this));
        if (!argsV.back())
            return nullptr;
    }

    return Builder->CreateCall(calleeF, argsV, "calltmp");
}


Function *LLVMIRGenerator::visitPrototype(const PrototypeAST *ast) const {

    // Make the function type:  double(double,double) etc.
    std::vector<Type *> Doubles(ast->getNumberOfArgs(), Type::getDoubleTy(*TheContext));
    
    FunctionType *functionTypes = FunctionType::get(Type::getDoubleTy(*TheContext), Doubles, false);
    Function *function = Function::Create(functionTypes, Function::ExternalLinkage, ast->getName(),
                                            TheModule.get());
    
    // Set names for all arguments.
    unsigned int i = 0;
    for (auto &arg : function->args())
        arg.setName(ast->getArgs()[i++]);

    return function;
}


Function *LLVMIRGenerator::visitFunctionDef(const FunctionAST *ast) {

    // 1. Check if the function is already defined via `extern`.
    Function *function = TheModule->getFunction(ast->getPrototype()->getName());

    if (!function)
        function = visitPrototype(ast->getPrototype());

    if (!function)
        return nullptr;

    if (!function->empty()) {
        return (Function *)logIRGenerationError("Function cannot be redefined.");
    }

    // Create a new basic block to start insertion into.
    BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", function);
    Builder->SetInsertPoint(BB);
    
    // Record the function arguments in the NamedValues map.
    NamedValues.clear();
    for (auto &arg : function->args())
        NamedValues[std::string(arg.getName())] = &arg;

    if (Value *returnValue = ast->getBody()->accept(this)) {
        // Finish off the function.
        Builder->CreateRet(returnValue);

        // Validate the generated code, checking for consistency.
        verifyFunction(*function);
        return function;
    } else {
        Builder->CreateRetVoid();
    }

    function->eraseFromParent();
    return nullptr;    
}


int LLVMIRGenerator::generateIR(const std::unique_ptr<NodeAST> &root) {
    
    if (FunctionAST *functionAST = dynamic_cast<FunctionAST *>(root.get())) {
        auto code = visitFunctionDef(functionAST);
        if (code == nullptr) {
            logIRGenerationError("Code Generation failed for prototype");
            return 1;
        }

        // if (functionAST->getPrototype()->getName().find("__anon_expr") != std::string::npos) {
        //     std::unique_ptr<Module> copied = CloneModule(*TheModule.get());
            
        //     auto H = myJIT->addModule(std::move(copied));

        //     // Search the JIT for the __anon_expr symbol.
        //     auto ExprSymbol = myJIT->findSymbol("__anon_expr");
        //     assert(ExprSymbol && "Function not found");

        //     // Get the symbol's address and cast it to the right type (takes no
        //     // arguments, returns a double) so we can call it as a native function.
        //     double (*FP)() = (double (*)())(intptr_t)cantFail(ExprSymbol.getAddress());
        //     fprintf(stderr, "Evaluated to %f\n", FP());

        //     // Delete the anonymous expression module from the JIT.
        //     myJIT->removeModule(H);
        // }
        
    } else if (PrototypeAST *prototypeAST = dynamic_cast<PrototypeAST *>(root.get())) {
        auto code = visitPrototype(prototypeAST);
        if (code == nullptr) {
            logIRGenerationError("Code Generation failed for prototype");
            return 1;
        }
    } else {
        logIRGenerationError("Unknown AST node type");
        return 1;
    }

    return 0;
}


void LLVMIRGenerator::printIR() const {
    TheModule->print(errs(), nullptr);
}

Module *LLVMIRGenerator::getModule() const {
    return TheModule.get();
}