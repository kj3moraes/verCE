#include "CodeGeneration/LLVMIRGenerator.h"
#include "Parser.h"
#include "Token.h"
#include "Lexer.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string line;
    istringstream ss; 
    Lexer ls;

    vector<Token> tokens;
    LLVMIRGenerator cg{};
    while (true) {
        cout << ">> ";
        getline(cin, line);
        if (cin.eof()) {
            break;
        }
        
        tokens = ls.scan(line);
        tokens.emplace_back(END_OF_FILE, "");

        Parser ps{tokens};
        
        auto ast = ps.parseInput();
        
        cg.generateIR(ast);

        cg.printIR();
    }

    cg.printIR();
}