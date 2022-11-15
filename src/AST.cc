#include "AST.h"
#include "CodeGeneration.h"
#include "CodeGeneration/Visitor.h"

using namespace llvm;

Value *BinaryExpressionAST::accept(Visitor *gen) { return gen->visitBinaryOp(this); }

Value *NumberExpressionAST::accept(Visitor *gen) { return gen->visitNumber(this); }

Value *VariableExpressionAST::accept(Visitor *gen) { return gen->visitVariable(this); }

Value *CallExpressionAST::accept(Visitor *gen) { return gen->visitCallExpr(this); }

Value *IfExpressionAST::accept(Visitor *gen) { return gen->visitIfExpr(this); }

Value *ForExpressionAST::accept(Visitor *gen) { return gen->visitForExpr(this); }

Function *FunctionAST::accept(Visitor *gen) { return gen->visitFunctionDef(this); }

Function *PrototypeAST::accept(Visitor *gen) { return gen->visitPrototype(this); }
