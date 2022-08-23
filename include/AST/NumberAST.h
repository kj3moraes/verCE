#ifndef __NUMBER_AST_H__
#define __NUMBER_AST_H__

#include <cmath>
#include "ExpressionAST.h"

class NumberExpressionAST : public ExpressionAST {
    double val;

    public:
        NumberExpressionAST(double value) : val(value) {}
};

#endif // __NUMBER_AST_H__
