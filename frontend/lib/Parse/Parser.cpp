#include "Parse/Parser.h"

#include <string>
#include <iostream>

std::unique_ptr<Stmt> Parser::ParseTopLevelStmt() {
    ConsumeToken();
    return std::move(ParseCompoundStmts());
}

std::unique_ptr<CompoundStmts> Parser::ParseCompoundStmts() {
    auto BINARY_CALC = ParseBinaryCalcStmt();
    ConsumeToken();
    /** BINARY CALC -> PRINT */
    if (Tok.is(tok::print)) {
        return std::make_unique<CompoundStmts>(std::move(BINARY_CALC), std::move(ParsePrintStmt()));
    }
    /** BINARY CALC -> UNARY CALCS -> PRINT */
    return std::make_unique<CompoundStmts>(std::move(BINARY_CALC), std::move(ParseCompoundUnaryStmts()),
                                           std::move(ParsePrintStmt()));
}

std::unique_ptr<CompoundUnaryStmts> Parser::ParseCompoundUnaryStmts() {
    auto UNARY_CALC = ParseUnaryCalcStmt();
    if (!UNARY_CALC) {
        return nullptr;
    }
    switch (Tok.getKind()) {
        case tok::add:
        case tok::sub:
        case tok::mul:
        case tok::div:
            return std::make_unique<CompoundUnaryStmts>(std::move(UNARY_CALC), std::move(ParseCompoundUnaryStmts()));
        case tok::print:
            return std::make_unique<CompoundUnaryStmts>(std::move(UNARY_CALC));
        default:
            return nullptr;
    }
}

std::unique_ptr<PrintStmt> Parser::ParsePrintStmt() {
    return std::make_unique<PrintStmt>(op::print);
}

std::unique_ptr<UnaryCalcStmt> Parser::ParseUnaryCalcStmt() {
    op::OpCode Code;
    switch (Tok.getKind()) {
        case tok::add:
            Code = op::add;
            break;
        case tok::sub:
            Code = op::sub;
            break;
        case tok::mul:
            Code = op::mul;
            break;
        case tok::div:
            Code = op::div;
            break;
        default:
            return nullptr;
    }

    ConsumeToken();
    auto OPERAND = ParseExpr();
    if (!OPERAND) {
        return nullptr;
    }

    ConsumeToken();
    return std::make_unique<UnaryCalcStmt>(Code, std::move(OPERAND));
}

std::unique_ptr<BinaryCalcStmt> Parser::ParseBinaryCalcStmt() {
    op::OpCode Code;
    switch (Tok.getKind()) {
        case tok::add:
            Code = op::add;
            break;
        case tok::sub:
            Code = op::sub;
            break;
        case tok::mul:
            Code = op::mul;
            break;
        case tok::div:
            Code = op::div;
            break;
        default:
            return nullptr;
    };

    ConsumeToken();
    auto L = ParseExpr();
    if (!L) {
        return nullptr;
    }

    ConsumeToken();
    if (Tok.isNot(tok::comma)) {
        return nullptr;
    }

    ConsumeToken();
    auto R = ParseExpr();
    if (!R) {
        return nullptr;
    }

    return std::make_unique<BinaryCalcStmt>(Code, std::move(L), std::move(R));
}

std::unique_ptr<Expr> Parser::ParseExpr() {
    return std::move(ParseNumExpr());
}

std::unique_ptr<NumExpr> Parser::ParseNumExpr() {
    if (Tok.isNot(tok::num)) {
        return nullptr;
    }

    auto Ptr = Tok.getLiteralData();
    auto Len = Tok.getLength();
    std::string literal(Ptr, Len);

    return std::make_unique<NumExpr>(std::stoi(literal));
}
