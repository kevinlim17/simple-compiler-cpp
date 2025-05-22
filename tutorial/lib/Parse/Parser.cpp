#include "Parse/Parser.h"

#include <string>
#include <iostream>

std::unique_ptr<StmtAST> Parser::ParseTopLevelStmt() {
  return std::move(ParseBinaryCalcStmt());
}

std::unique_ptr<BinaryCalcStmtAST> Parser::ParseBinaryCalcStmt() {
  ConsumeToken();

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
    Code = op::sub;
    break;
  default:
    return nullptr;
  };

  auto L = ParseExpr();
  if (!L) {
    return nullptr;
  }

  ConsumeToken();
  if (Tok.isNot(tok::comma)) {
    return nullptr;
  }  

  auto R = ParseExpr();
  if (!R) {
    return nullptr;
  }
  
  return std::make_unique<BinaryCalcStmtAST>(Code, std::move(L), std::move(R));
}

std::unique_ptr<ExprAST> Parser::ParseExpr() { 
  return std::move(ParseNumExpr());
}

std::unique_ptr<NumExprAST> Parser::ParseNumExpr() {
  ConsumeToken();
 
  if (Tok.isNot(tok::num)) {
    return nullptr; 
  }

  auto Ptr = Tok.getLiteralData();
  auto Len = Tok.getLength();
  std::string literal(Ptr, Len);

  return std::make_unique<NumExprAST>(std::stoi(literal));
}

