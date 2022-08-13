#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierString; // Filled in if tok_identifier
static double NumberValue;             // Filled in if tok_number


/**
 * @brief Token reading function
 * 
 * @return int - Token or ASCII value
 */
static int gettok() {
    static int lastChar = ' ';

    // 1. Remove any leading whitespace.
    while (isspace(lastChar)) {
        lastChar = getchar();
    }

    // 2. Read an identifier (if it exists)
    if (isalpha(lastChar)) {
        IdentifierString = lastChar;
        while (isalnum(lastChar = getchar())) {
            IdentifierString += lastChar;
        }
        if (IdentifierString == "def") {
            return tok_def;
        }
        if (IdentifierString == "extern") {
            return tok_extern;
        }
        return tok_identifier;
    }

    // 3. Read a number (if it exists)
    if (isdigit(lastChar)) {
        std::string numStr;
        do {
            numStr += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar));
        
        NumberValue = strtod(numStr.c_str(), 0);
        return tok_number;
    }

    // 4. Read the comments
    if (lastChar == '#') {
        do {
            lastChar = getchar();
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
        
        if (lastChar != EOF) {
            return gettok();
        }
    }

    // 5. Read the EOF
    if (lastChar == EOF) {
        return tok_eof;
    }

    int thusFar = lastChar;
    lastChar = getchar();
    return thusFar;
}


static int CurTok;
static int getNextToken() {
    return CurTok = gettok();
}



/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "LogError: %s\n", Str);
  return nullptr;
}
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

