#include "Lexer.h"
#include <algorithm>
#include <cctype>
#include <map>

const std::map<std::string, Kind> specialIDS = {
    {"def", DEF},
    {"extern", EXTERN},
};

Lexer::Lexer() {

    // 1. DEFINE ALL THE ACCEPTING STATES
    acceptingStates = {
        ST_ID,
        ST_NUM,
        ST_NUM_AFTER_DECIMAL,
        ST_LPAREN,
        ST_RPAREN,
        ST_BECOMES,
        ST_EQ,
        ST_COMMA,
        ST_WHITESPACE,
        ST_PLUS,
        ST_MINUS,
        ST_STAR,
        ST_SLASH,
        ST_ZEROERR
    };

    // 2. SET ALL THE DEFAULT TRANSITIONS TO THE ERROR STATE
    for (size_t i = 0; i < transitionFunction.size(); i++) {
        for (size_t j = 0; j < transitionFunction[i].size(); j++) {
            transitionFunction[i][j] = ST_ERR;
        }
    }

    // 3. REGISTER ALL THE TRANSITIONS
    registerTransition(ST_START, isalpha, ST_ID);
    registerTransition(ST_START, "0", ST_ZEROERR);
    registerTransition(ST_START, isdigit, ST_NUM);
    registerTransition(ST_START, ")", ST_RPAREN);
    registerTransition(ST_START, "(", ST_LPAREN);
    registerTransition(ST_START, "=", ST_BECOMES);
    registerTransition(ST_START, "+", ST_PLUS);
    registerTransition(ST_START, "-", ST_MINUS);
    registerTransition(ST_START, "*", ST_STAR);
    registerTransition(ST_START, "/", ST_SLASH);
    registerTransition(ST_START, ",", ST_COMMA);
    registerTransition(ST_START, "#", ST_WHITESPACE);
    registerTransition(ST_START, isspace, ST_WHITESPACE);

    registerTransition(ST_NUM, isdigit, ST_NUM);
    registerTransition(ST_ID, isalnum, ST_ID);
    registerTransition(ST_NUM, ".", ST_DECIMAL);
    registerTransition(ST_DECIMAL, isdigit, ST_NUM_AFTER_DECIMAL);
    registerTransition(ST_NUM_AFTER_DECIMAL, isdigit, ST_NUM_AFTER_DECIMAL);
    registerTransition(ST_ZEROERR, ".", ST_DECIMAL);
    registerTransition(ST_WHITESPACE, isspace, ST_WHITESPACE);
    registerTransition(ST_BECOMES, "=", ST_EQ);
    
}

Lexer::~Lexer() {}

Kind Lexer::stateToKind(State s) const {
    switch (s) {
        case ST_ID:                 return ID;
        case ST_NUM:                return NUM;
        case ST_NUM_AFTER_DECIMAL:  return NUM;
        case ST_LPAREN:             return LPAREN;
        case ST_RPAREN:             return RPAREN;
        case ST_BECOMES:            return BECOMES;
        case ST_EQ:                 return EQ;
        case ST_PLUS:               return PLUS;
        case ST_MINUS:              return MINUS;
        case ST_STAR:               return STAR;
        case ST_SLASH:              return SLASH;
        default:                    return WHITESPACE;
    }
}

void Lexer::registerTransition(State oldState, const std::string &chars, State newState) {
    for (char c : chars) {
        transitionFunction[oldState][c] = newState;
    }
}

void Lexer::registerTransition(State oldState, int (*test)(int), State newState) {
    for (int c = 0; c < 128; ++c) {
        if (test(c)) {
            transitionFunction[oldState][c] = newState;
        }
    }
}

Lexer::State Lexer::transition(State state, char nextChar) const {
      return transitionFunction[state][nextChar];
}


bool Lexer::isFailed(State state) const {
    return state == ST_ERR;
}


bool Lexer::isAccepted(State state) const {
    return acceptingStates.count(state) > 0;
}


Lexer::State Lexer::start() const {
    return ST_START;
}


std::vector<Token> Lexer::simplifiedMaximalMunch(const std::string &input) const {
    std::vector<Token> result;

    State state = start();
    std::string munchedInput;

    for (std::string::const_iterator inputPosn = input.begin(); inputPosn != input.end();) {

        State oldState = state;
        state = transition(state, *inputPosn);

        if (!isFailed(state)) {
            munchedInput += *inputPosn;
            oldState = state;
            ++inputPosn;
        }

        if (inputPosn == input.end() || isFailed(state)) {
            if (isAccepted(oldState)) {
                result.emplace_back(stateToKind(oldState), munchedInput);
                munchedInput = "";
                state = start();
            } else {
                if (isFailed(state)) {
                    munchedInput += *inputPosn;
                }
                throw ScanningFailure("Failure on input>" + munchedInput);
            }
        }
    }
    return result;
}


std::vector<Token> Lexer::scan(std::string &input, const long lineNumber) {
    
    std::vector<Token> tokens;
    try {
       tokens  = simplifiedMaximalMunch(input);
    } catch (ScanningFailure &err) {
        std::cerr << "Scanning Failure at line " << lineNumber << ": " << std::endl;
        std::cerr << err.what() << "\n" << std::endl;
        throw ScanningFailure(err.what());
    }
    std::vector<Token> finaltokens;

    for (auto &t : tokens) {
        if (t.getKind() == ID) {
            auto it = specialIDS.find(t.getLexeme());

            if (it == specialIDS.end()) {
                finaltokens.push_back(t);
                continue;
            }
            finaltokens.emplace_back(it->second, it->first);
            continue;
        } else if (t.getKind() == WHITESPACE) {
            if ( t.getLexeme()[0] == COMMENT_INIT) break;
            else continue;
        } 
        finaltokens.push_back(t);
    }
    return finaltokens;
}
