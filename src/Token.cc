#include "Token.h"

Kind Token::getKind() const {
    return kind;
}

const std::string Token::getLexeme() const {
    return lexeme;
}

std::ostream &operator<<(std::ostream &out, const Token &tok) {
    switch (tok.getKind()) {
        case ID:         out << "ID";         break;
        case NUM:        out << "NUM";        break;
        case BECOMES:    out << "BECOMES";    break;
        case EQ:         out << "EQ";         break;
        case LT:         out << "LT";         break;
        case PLUS:       out << "PLUS";       break;
        case MINUS:      out << "MINUS";      break; 
        case STAR:       out << "STAR";       break;
        case LPAREN:     out << "LPAREN";     break;
        case RPAREN:     out << "RPAREN";     break;
        case DEF:        out << "DEF";        break;
        case EXTERN:     out << "EXTERN";     break;
        case WHITESPACE: out << "WHITESPACE"; break;
    }
    out << ":" << tok.getLexeme() << " ";

    return out;
}

ScanningFailure::ScanningFailure(std::string message): message(std::move(message)) {}

const std::string ScanningFailure::what() const { return "ERROR: " + message; }