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
  llvm::Value *EmitExpr(const Expr *E);
  llvm::Value *EmitNumExpr(const NumExpr *E);
  void EmitStmt(const Stmt *S);
  void EmitBinaryCalcStmt(const BinaryCalcStmt *S);
};

#endif 
