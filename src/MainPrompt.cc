#include "CodeGeneration/LLVMIRCodeGenerator.h"
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
        try {
            tokens = ls.scan(line, 0);
            for (auto &v : tokens) {
                cout << v << endl;
            }
        } catch(ScanningFailure &s) {
            cout << s.what() << endl;
            break;
        }
        tokens.emplace_back(END_OF_FILE, "eof");

        Parser ps{tokens};
        try {
            auto ast = ps.parseInput();
            cout << "Parsed successfully!" << endl;
        } catch(CompilationFailure &c) {
            cout << "\nCompilation failed!" << endl;
            cout << c.what() << endl;
        }

        LLVMIRCodeGenerator cg{};
    }
}