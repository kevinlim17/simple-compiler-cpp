#include "Parse/Parser.h"

#include <string>
#include <iostream>

std::unique_ptr<Stmt> Parser::ParseTopLevelStmt() {
  ConsumeToken();
  return std::move(ParseBinaryCalcStmt());
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

