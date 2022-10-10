#include "AST.h"
#include "CodeGeneration.h"
#include "CodeGeneration/Visitor.h"

using namespace llvm;

Value *BinaryExpressionAST::accept(const Visitor *gen) { return gen->visitBinaryOp(this); }

Value *NumberExpressionAST::accept(const Visitor *gen) { return gen->visitNumber(this); }

Value *VariableExpressionAST::accept(const Visitor *gen) { return gen->visitVariable(this); }

Value *CallExpressionAST::accept(const Visitor *gen) { return gen->visitCallExpr(this); }

Function *FunctionAST::accept(Visitor *gen) { return gen->visitFunctionDef(this); }

Function *PrototypeAST::accept(const Visitor *gen) { return gen->visitPrototype(this); }
