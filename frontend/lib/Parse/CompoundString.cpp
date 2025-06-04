#include "Parse/AST.h"

std::string CompoundStmts::toString(int depth) {
    std::string result = std::string(depth * 2, ' ') + "- Compound Statements:\n";
    result += FirstStm->toString(depth + 1) + "\n";
    if (UnaryStms) {
        result += UnaryStms->toString(depth + 1);
    }
    result += LastStm->toString(depth + 1);
    return result;
}

std::string CompoundUnaryStmts::toString(int depth) {
    std::string result = FirstUnaryStm->toString(depth) + "\n";
    if (LastUnaryStmts) {
        result += LastUnaryStmts->toString(depth);
    }
    return result;
}


