#ifndef __COMPILER_TUTORIAL_PARSE_AST_H__  
#define __COMPILER_TUTORIAL_PARSE_AST_H__ 

#include <memory>
#include <string>

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
  virtual std::string toString(int depth = 0) = 0;
};

class NumExprAST : public ExprAST {
  int Val;
public:
  NumExprAST(int Val) : Val(Val) {}
  
  std::string toString(int depth = 0) {
    return std::string(depth * 2, ' ') 
         + "- NumExpr: " + std::to_string(Val);
  }
};

class StmtAST {
public:
  virtual ~StmtAST() = default;
  virtual std::string toString(int depth = 0) = 0;
};

class BinaryCalcStmtAST : public StmtAST {
  op::OpCode Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryCalcStmtAST(op::OpCode Op, std::unique_ptr<ExprAST> LHS,
                    std::unique_ptr<ExprAST> RHS)
  : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  
  std::string toString(int depth = 0) {
    std::string opStr;
    switch(Op) {
    case op::add: opStr = "Add"; break;
    case op::sub: opStr = "Sub"; break;
    case op::mul: opStr = "Mul"; break;
    case op::div: opStr = "Div"; break;
    }
    return std::string(depth * 2, ' ') 
         + "- BinaryCalcExpr: " + opStr + "\n"
         + LHS->toString(depth + 1) + "\n"
         + RHS->toString(depth + 1) + "\n";
  }
};

#endif 
