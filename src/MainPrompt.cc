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

    int lineNumber = 0;

    // Setup variables for code processing
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
        if (tokens.size() == 1 && tokens.at(1).getKind() == Kind::ID && tokens.at(1).getLexeme() == "ERROR") {
            cerr << "\nFailed to read at line : " << lineNumber << endl;
            cerr << "Refer to the DOCS for correct syntax" << endl;
            exit(1);
        }
        tokens.emplace_back(END_OF_FILE, "");

        Parser ps{tokens};
        
        auto ast = ps.parseInput();
        if (ast == nullptr) {
            cerr << "\nFailed to parse at line : " << lineNumber << endl;
            exit(2);
        }

        int irReturn = cg.generateIR(ast);
        if (irReturn != 0) {
            cerr << "\nFailed to generate code at line : " << lineNumber << endl;
            exit(3);
        }
        cg.printIR();
        lineNumber++;
    }

    cg.printIR();
}