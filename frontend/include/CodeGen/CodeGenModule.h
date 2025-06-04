#ifndef __COMPILER_TUTORIAL_CODEGEN_CODEGENMODULE_H__  
#define __COMPILER_TUTORIAL_CODEGEN_CODEGENMODULE_H__

#include "llvm/IR/Module.h"
#include "Parse/AST.h"

class CodeGenModule {
  llvm::Module &TheModule;
  llvm::LLVMContext &VMContext;

public:
  explicit CodeGenModule(llvm::Module &M);

  llvm::LLVMContext &getLLVMContext() { return VMContext; }
  llvm::Module &getModule() const { return TheModule; }

  void EmitTopLevelStmt(const Stmt *S);

  void PrintModule();
};

#endif 


