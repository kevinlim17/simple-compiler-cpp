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

  std::unique_ptr<StmtAST> ParseTopLevelStmt();
  std::unique_ptr<BinaryCalcStmtAST> ParseBinaryCalcStmt();
  
  std::unique_ptr<ExprAST> ParseExpr();
  std::unique_ptr<NumExprAST> ParseNumExpr();

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
