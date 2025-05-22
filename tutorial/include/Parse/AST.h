#ifndef __COMPILER_TUTORIAL_PARSE_AST_H__  
#define __COMPILER_TUTORIAL_PARSE_AST_H__ 

#include <memory>

namespace op {
enum OpCode {
  add,
  sub,
  div,
  mul, 
};
}

class ExprAST {
public:
  virtual ~ExprAST() = default;
};

class NumExprAST : public ExprAST {
  int Val;
public:
  NumExprAST(int Val) : Val(Val) {}
};

class StmtAST {
public:
  virtual ~StmtAST() = default;
};

class BinaryCalcStmtAST : public StmtAST {
  op::OpCode Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryCalcStmtAST(op::OpCode Op, std::unique_ptr<ExprAST> LHS,
                    std::unique_ptr<ExprAST> RHS)
  : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

#endif 
