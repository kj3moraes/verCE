#ifndef __PROTOTYPE_AST_H__
#define __PROTOTYPE_AST_H__

#include <string>
#include <vector>

#include "NodeAST.h"
#include "../CodeGeneration.h"
using namespace llvm;

class PrototypeAST : public NodeAST{
    std::string Name;
    std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args)
            : Name(Name), Args(std::move(Args)) {}
        ~PrototypeAST() {}
        
        inline std::string getName() const { return Name; }
        inline const std::vector<std::string> &getArgs() const { return Args; }
        inline unsigned long getNumberOfArgs() const { return Args.size(); }
        
        Function *accept(Visitor *gen);
};

#endif // __PROTOTYPE_AST_H__
