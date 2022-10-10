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
    while (true) {
        cout << ">> ";
        getline(cin, line);
        if (cin.eof()) {
            break;
        }
        
        tokens = ls.scan(line);

        tokens.emplace_back(END_OF_FILE, "eof");

        Parser ps{tokens};
        
        auto ast = ps.parseInput();
        
        LLVMIRGenerator cg{};
    }
}