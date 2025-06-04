#ifndef __COMPILER_TUTORIAL_PARSE_AST_H__
#define __COMPILER_TUTORIAL_PARSE_AST_H__

#include <memory>
#include <string>

class CompoundUnaryStmts;
class PrintStmt;
class PrintLastStmts;
class UnaryCalcStmt;
class BinaryCalcStmt;

namespace op {
    enum OpCode {
        add,
        sub,
        div,
        mul,
        print,
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
    NumExpr(int Val) : Val(Val) {
    }

    const int getVal() const { return Val; }

    std::string toString(const int depth) override {
        return std::string(depth * 2, ' ')
               + "- NumExpr: " + std::to_string(Val);
    }
};

class Stmt {
public:
    virtual ~Stmt() = default;

    virtual std::string toString(int dept = 0) = 0;
};

/** FOR MULTIPLE STATEMENTS */
class CompoundStmts : public Stmt {
    std::unique_ptr<BinaryCalcStmt> FirstStm;
    std::unique_ptr<CompoundUnaryStmts> UnaryStms = nullptr;
    std::unique_ptr<PrintStmt> LastStm;

public:
    ~CompoundStmts() override = default;

    std::string toString(int depth = 0) override;

    CompoundStmts(std::unique_ptr<BinaryCalcStmt> stm1, std::unique_ptr<CompoundUnaryStmts> stm2,
                  std::unique_ptr<PrintStmt> stm3) : FirstStm(std::move(stm1)),
                                                     UnaryStms(std::move(stm2)), LastStm(std::move(stm3)) {
    }

    CompoundStmts(std::unique_ptr<BinaryCalcStmt> stm1, std::unique_ptr<PrintStmt> stm2) : FirstStm(std::move(stm1)),
        LastStm(std::move(stm2)) {
    }
};

class CompoundUnaryStmts : public Stmt {
    std::unique_ptr<UnaryCalcStmt> FirstUnaryStm;
    std::unique_ptr<CompoundUnaryStmts> LastUnaryStmts = nullptr;

public:
    CompoundUnaryStmts(std::unique_ptr<UnaryCalcStmt> UnaryStmt,
                       std::unique_ptr<CompoundUnaryStmts> LastUnaryStms)
        : FirstUnaryStm(std::move(UnaryStmt)), LastUnaryStmts(std::move(LastUnaryStms)) {
    }

    explicit CompoundUnaryStmts(std::unique_ptr<UnaryCalcStmt> UnaryStmt) : FirstUnaryStm(std::move(UnaryStmt)) {
    }

    std::string toString(int depth = 0) override;
};

/** PRINT */
class PrintStmt : public Stmt {
    op::OpCode Op;

public:
    explicit PrintStmt(op::OpCode Op) : Op(Op) {
    }

    op::OpCode getOpCode() const { return Op; }

    std::string toString(int depth = 0) override {
        return std::string(depth * 2, ' ') + "- PrintStmt";
    }
};


/** STATEMENT FOR SINGLE OPERAND */
class UnaryCalcStmt : public Stmt {
    op::OpCode Op;
    std::unique_ptr<Expr> OPERAND;

public:
    ~UnaryCalcStmt() override = default;

    explicit UnaryCalcStmt(op::OpCode Op, std::unique_ptr<Expr> OPERAND)
        : Op(Op), OPERAND(std::move(OPERAND)) {
    }

    op::OpCode getOpCode() const { return Op; }
    const Expr *getOperand() const { return OPERAND.get(); }

    std::string toString(int depth = 0) override {
        std::string opStr;
        switch (Op) {
            case op::add: opStr = "Add";
                break;
            case op::sub: opStr = "Sub";
                break;
            case op::mul: opStr = "Mul";
                break;
            case op::div: opStr = "Div";
                break;
            default:
                break;
        }
        return std::string(depth * 2, ' ')
               + "- UnaryCalcStmt: " + opStr + "\n"
               + OPERAND->toString(depth + 1);
    }
};


class BinaryCalcStmt : public Stmt {
    op::OpCode Op;
    std::unique_ptr<Expr> LHS, RHS;

public:
    explicit BinaryCalcStmt(op::OpCode Op, std::unique_ptr<Expr> LHS,
                            std::unique_ptr<Expr> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {
    }

    op::OpCode getOpCode() const { return Op; }
    const Expr *getLHS() const { return LHS.get(); }
    const Expr *getRHS() const { return RHS.get(); }

    std::string toString(int depth = 0) override {
        std::string opStr;
        switch (Op) {
            case op::add: opStr = "Add";
                break;
            case op::sub: opStr = "Sub";
                break;
            case op::mul: opStr = "Mul";
                break;
            case op::div: opStr = "Div";
                break;
        }
        return std::string(depth * 2, ' ')
               + "- BinaryCalcStmt: " + opStr + "\n"
               + LHS->toString(depth + 1) + "\n"
               + RHS->toString(depth + 1);
    }
};

#endif
