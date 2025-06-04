#ifndef __COMPILER_TUTORIAL_CODEGEN_CODEGENFUNCTION_H__
#define __COMPILER_TUTORIAL_CODEGEN_CODEGENFUNCTION_H__

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/NoFolder.h"
#include "CodeGen/CodeGenModule.h"

class CodeGenFunction {
  CodeGenModule &CGM;

  llvm::IRBuilder<llvm::NoFolder> Builder;
  llvm::Value *ACC;

public:
  CodeGenFunction(CodeGenModule &cgm);

  void GenerateCode(const Stmt *S, llvm::Function *F);

  /** Expressions */
  llvm::Value *EmitExpr(const Expr *E);
  llvm::Value *EmitNumExpr(const NumExpr *NE);

  /** Statements */
  void EmitStmt(const Stmt *S);
  void EmitCompoundStmt(const CompoundStmts *CS);
  void EmitCompoundUnaryStmts(const CompoundUnaryStmts *CUS);
  void EmitBinaryCalcStmt(const BinaryCalcStmt *BCS);
  void EmitUnaryCalcStmt(const UnaryCalcStmt *UCS);
  void EmitPrintStmt(const PrintStmt *PS);
};

#endif
