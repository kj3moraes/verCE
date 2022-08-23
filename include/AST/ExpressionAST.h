#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include <string>

class ExpressionAST {
    std::string value;

    public:
        virtual ~ExpressionAST() {}
        virtual std::string toString() const = 0;
};

#endif // __EXPR_AST_H__
