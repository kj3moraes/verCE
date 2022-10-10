#include "CodeGeneration/LLVMIRGenerator.h"
#include "Parser.h"
#include "Token.h"
#include "Lexer.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define RED_BG "\033[1;41m"
#define WHITE_FG "\033[1;37m"
#define RESET "\033[0m"

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
        
        lineToks = ls.scan(line);
        if (lineToks.size() == 0) {
            cerr << RED_BG << WHITE_FG << "Error on line " << lineNumber << RESET << endl;
            continue;
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

    LLVMIRGenerator cg{};
}