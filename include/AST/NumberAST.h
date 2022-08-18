#ifndef __NUMBER_AST_H__
#define __NUMBER_AST_H__

#include <cmath>
#include "ExpressionAST.h"

class NumberExprAST : public ExpressionAST {
    double val;

    public:
        NumberExprAST(double value) : val(value) {}
};

#endif // __NUMBER_AST_H__