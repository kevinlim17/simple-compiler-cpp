#include "Parse/Parser.h"

std::unique_ptr<StmtAST> ParseTopLevelStmt() {
  return ParseCalcStmt();
}

std::unique_ptr<ExprAST> ParseExpr() { 
}

std::unique_ptr<CalcStmtAST> ParseCalcStmt() {
  switch (CurTok) {
  case :
  };
}

std::unique_ptr<StmtAST> ParseNumExpr() {
}




