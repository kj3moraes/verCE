#ifndef __LEXER_H__
#define __LEXER_H__

#include <array>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>

#include "Token.h"


class Lexer {

    enum State {

        // Literals and numbers
        ST_ID = 0,
        ST_NUM,

        // Parenthesis, Braces and Brackets
        ST_LPAREN,
        ST_RPAREN,
        ST_LBRACE,
        ST_RBRACE,
        ST_LBRACK,
        ST_RBRACK,

        // Relational Operators
        ST_BECOMES,
        ST_EQ,
        ST_NE,
        ST_LT,
        ST_GT,
        ST_LE,
        ST_GE,

        // Arithmetic Operators
        ST_PLUS,
        ST_MINUS,
        ST_STAR,
        ST_SLASH,
        ST_MODULO,

        // Punctuality
        ST_COMMA,
        ST_SEMI,
        ST_WHITESPACE,

        // Memory Management
        ST_NEW,
        ST_DELETE,
        ST_AMP,

        // States that are not Kinds
        ST_START,
        ST_ZEROERR,
        ST_ERR,
        ST_EXC,
        ST_DOLLARS,

        ST_LARGEST_STATE = ST_DOLLARS
    };

        
    std::set<State> acceptingStates;

    std::array<std::array<State, 256>, ST_LARGEST_STATE + 1> transitionFunction;

    Kind stateToKind(State s) const;

    std::vector<Token> simplifiedMaximalMunch(const std::string &input) const;

    void registerTransition(State oldState, const std::string &chars, State newState);

    void registerTransition(State oldState, int (*test)(int), State newState);

    State transition(State oldState, char nextChar) const;

    bool isFailed(State state) const;

    bool isAccepted(State state) const;

    State start() const;

    public:
        Lexer();
        ~Lexer();

        /**
         * @brief 
         * 
         * @param input 
         * @return std::vector<Token> 
         */
        std::vector<Token> scan(std::string &input);
};
#endif // __LEXER_H__