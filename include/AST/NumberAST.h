#ifndef __NUMBER_AST_H__
#define __NUMBER_AST_H__

#include <cmath>

#include "ExpressionAST.h"
#include "../CodeGeneration.h"

class NumberExpressionAST : public ExpressionAST {
    double val;

    public:
        NumberExpressionAST(double value) : val(value) {}
        ~NumberExpressionAST() {}
        
        double getValue() const { return val; }

        Value *accept(Visitor *gen) override;
};

#endif // __NUMBER_AST_H__
