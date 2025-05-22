#ifndef __COMPILER_TUTORIAL_PARSE_AST_H__  
#define __COMPILER_TUTORIAL_PARSE_AST_H__ 

namespace op {
enum OpCode {
  add;
  sub;
  div;
  mul; 
};
}

class ExprAST {
public:
  virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
  int Val;
public:
  NumberExprAST(int Val) : Val(Val) {}
};

class StmtAST {
public:
  virtual ~StmtAST() = default;
};

class CalcStmtAST : public StmtAST {
  op::OpCode Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  CalcStmtAST(op::OpCode Op, std::unique_ptr<ExprAST> LHS,
              std::unique_ptr<ExprAST> RHS)
  : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

#endif 
