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
        case SLASH:      out << "SLASH";      break;
        case MODULO:     out << "MODULO";     break;
        case LPAREN:     out << "LPAREN";     break;
        case RPAREN:     out << "RPAREN";     break;
        case COMMA:      out << "COMMA";      break;
        case SEMI:       out << "SEMI";       break;
        case DOT:        out << "DOT";        break;
        case DEF:        out << "DEF";        break;
        case EXTERN:     out << "EXTERN";     break;
        case WHITESPACE: out << "WHITESPACE"; break;
        case IF:         out << "IF";         break;
        case FOR:        out << "FOR";        break;
        case THEN:       out << "THEN";       break;
        case ELSE:       out << "ELSE";       break;
        case END_OF_FILE:out << "//:eof://";  break;
    }
    out << ":" << tok.getLexeme() << " ";

    return out;
}

bool operator==(const Token &lhs, const Token &rhs) {
    return (lhs.getKind() == rhs.getKind()) && (lhs.getLexeme() == rhs.getLexeme());
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}
