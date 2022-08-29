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
            break;
        }

        Parser ps{tokens};
        try {
            auto ast = ps.parseInput();
            cout << "Parsed successfully!" << endl;
            cout << "AST: " << endl;
        } catch(CompilationFailure &c) {
            cout << "\nCompilation failed!" << endl;
            cout << "ERROR: " <<  c.what() << endl;
        }
    }
}