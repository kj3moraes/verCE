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
    Lexer ls; 
    unsigned long lineNumber = 1;

    vector<Token> tokens, lineToks;
    vector<std::string> linesOfCode;

    // Collect code line by line and tokenize each line.
    while (true) {
        getline(cin, line);
        if (cin.eof()) {
            break;
        }
        try {
            lineToks = ls.scan(line, lineNumber++);
        } catch(ScanningFailure &s) {
            cerr << "Scanning Failed!" << endl;
            cerr << s.what() << endl;
            break;
        }
        tokens.insert(tokens.end(), lineToks.begin(), lineToks.end());
    }
    tokens.emplace_back(END_OF_FILE, "eof");

    // Print out all the tokens
    for (auto &v : tokens) {
        cout << v << endl;
    }
    
    // Construct a parser object for the tokenlist of the whole program.
    Parser ps{tokens};
    try {
        auto ast = ps.parseInput();
        cout << "Parsed successfully!" << endl;
    } catch(CodeGenerationFailure &c) {
        cerr << "\nCompilation failed!" << endl;
        cerr << c.what() << endl;
    }

    LLVMIRCodeGenerator cg{};
}