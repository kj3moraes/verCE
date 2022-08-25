#ifndef __VARIABLE_AST_H__
#define __VARIABLE_AST_H__

#include <cmath>
#include "ExpressionAST.h"

class VariableExpressionAST : public ExpressionAST {
    std::string Name;

    public:
        VariableExpressionAST(const std::string &Name) : Name(Name) {}
};

#endif // __NUMBER_AST_H__
