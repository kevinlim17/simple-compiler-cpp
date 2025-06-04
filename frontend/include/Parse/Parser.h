#ifndef __COMPILER_TUTORIAL_PARSE_PARSER_H__
#define __COMPILER_TUTORIAL_PARSE_PARSER_H__ 

#include <memory>

#include "Parse/AST.h"
#include "Lex/Lexer.h"

class Parser {
    // The lexer
    Lexer &L;

    // The current token
    Token Tok;

public:
    Parser(Lexer &Lexer): L(Lexer) {
        Tok.startToken();
        Tok.setKind(tok::eof);
    }

    std::unique_ptr<Stmt> ParseTopLevelStmt();

    std::unique_ptr<CompoundStmts> ParseCompoundStmts();

    std::unique_ptr<CompoundUnaryStmts> ParseCompoundUnaryStmts();

    static std::unique_ptr<PrintStmt> ParsePrintStmt();

    std::unique_ptr<UnaryCalcStmt> ParseUnaryCalcStmt();

    std::unique_ptr<BinaryCalcStmt> ParseBinaryCalcStmt();

    std::unique_ptr<Expr> ParseExpr();

    std::unique_ptr<NumExpr> ParseNumExpr();

    void ConsumeToken() {
        L.Lex(Tok);
    }

    bool TryConsumeToken(tok::TokenKind Expected) {
        if (Tok.isNot(Expected))
            return false;
        L.Lex(Tok);
        return true;
    }
};

#endif
