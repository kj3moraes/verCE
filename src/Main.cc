#include "Token.h"
#include "Lexer.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
    string line;
    istringstream ss; 
    Lexer ls;
    int lineNumber = 1;

    while (getline(cin, line)) {
        istringstream is{line};
        string pluck;
        
        try {
            vector<Token> tokens = ls.scan(line, lineNumber++);
            for (auto &v : tokens) {
                cout << v << endl;
            }
        } catch(ScanningFailure &s) {
            cerr << s.what() << endl;
        }

    }

}