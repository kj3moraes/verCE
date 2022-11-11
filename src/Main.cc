#include "CodeGeneration/LLVMIRGenerator.h"
#include "Parser.h"
#include "Token.h"
#include "Lexer.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define BG_RED      "\033[1;41m"
#define FG_WHITE    "\033[1;37m"
#define RESET       "\033[0m"

int main(int argc, char **argv) {

    int lineNumber = 0;
    bool IS_FILE = false;
    ifstream file;
    if (argc == 2) {
        file.open(argv[1], ios::in);
        if (file.is_open()) {
            IS_FILE = true;
        } else {
            cout << BG_RED << "Could not open file " << argv[1] << RESET << endl;
            exit(-1);
        }
    }

    // Setup variables for code processing
    string line;
    istringstream ss; 
    Lexer ls;
    vector<Token> tokens;
    LLVMIRGenerator cg{};

    while (true) {

        if (!IS_FILE) {
            cout << ">> ";
            getline(cin, line);
            if (cin.eof()) {
                break;
            }
        } else {
            getline(file, line);
            if (file.eof()) {
                break;
            }
        }
        
        // LEXING STAGE
        tokens = ls.scan(line);
        if (tokens.size() == 1 && tokens.at(1).getKind() == Kind::ID && tokens.at(1).getLexeme() == "ERROR") {
            cerr << BG_RED << "\nFailed to read at line : " << lineNumber << endl;
            cerr << "Refer to the DOCS for correct syntax" << RESET << endl;
            exit(1);
        }
        tokens.emplace_back(END_OF_FILE, "");

        // PARSING STAGE
        Parser ps{tokens};
        auto ast = ps.parseInput();
        if (ast == nullptr) {
            cerr << BG_RED << "\nFailed to parse at line : " << lineNumber << endl;
            cerr << "Refer to the LANGUAGE_DOC.md file to correctly write statements" << RESET << endl;
            exit(2);
        }

        // IR GENERATION STAGE
        int irReturn = cg.generateIR(ast, false);
        if (irReturn != 0) {
            cerr << BG_RED "\nFailed to generate code at line : " << lineNumber << RESET << endl;
            exit(3);
        }
        cg.printIR();
        lineNumber++;
    }
    cg.printIR();
}