#include "Lexer.h"
#include <algorithm>
#include <cctype>
#include <map>

const std::map<std::string, Kind> specialIDS = {
    {"def", DEF},
    {"extern", EXTERN},
};


Lexer::Lexer() {

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
                throw ScanningFailure("ERROR: Scanning failure on input: " + munchedInput);
            }
        }
    }
    return result;
}


std::vector<Token> Lexer::scan(std::string &input) {
    
}