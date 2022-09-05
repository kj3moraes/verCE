#ifndef __PROTOTYPE_AST_H__
#define __PROTOTYPE_AST_H__

#include <string>
#include <vector>

#include "ExpressionAST.h"
#include "../CodeGeneration/Visitor.h"

class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args)
            : Name(Name), Args(std::move(Args)) {}

        const std::string &getName() const { return Name; }

        Value *accept(Visitor *gen) { return gen->visitPrototype(this);}
};

#endif // __PROTOTYPE_AST_H__
