#ifndef __PROTOTYPE_AST_H__
#define __PROTOTYPE_AST_H__

#include <string>
#include <vector>

#include "../CodeGeneration.h"
using namespace llvm;

class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args)
            : Name(Name), Args(std::move(Args)) {}

        const std::string &getName() const { return Name; }
        const std::vector<std::string> &getArgs() const { return Args; }
        const unsigned long getNumberOfArgs() const { return Args.size(); }
        
        Function *accept(const Visitor *gen);
};

#endif // __PROTOTYPE_AST_H__
