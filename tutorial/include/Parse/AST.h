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

class Expr {
public:
  virtual ~Expr() = default;
  virtual std::string toString(int depth = 0) = 0;
};

class NumExpr : public Expr {
  int Val;
public:
  NumExpr(int Val) : Val(Val) {}
  
  std::string toString(int depth = 0) {
    return std::string(depth * 2, ' ') 
         + "- NumExpr: " + std::to_string(Val);
  }
};

class Stmt {
public:
  virtual ~Stmt() = default;
  virtual std::string toString(int depth = 0) = 0;
};

class BinaryCalcStmt : public Stmt {
  op::OpCode Op;
  std::unique_ptr<Expr> LHS, RHS;

public:
  BinaryCalcStmt(op::OpCode Op, std::unique_ptr<Expr> LHS,
                 std::unique_ptr<Expr> RHS)
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
         + RHS->toString(depth + 1);
  }
};

#endif 
