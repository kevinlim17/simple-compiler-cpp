#include "CodeGen/CodeGenModule.h"
#include "CodeGen/CodeGenFunction.h"

CodeGenModule::CodeGenModule(llvm::Module &M) 
  : VMContext(M.getContext()), TheModule(M) { }

void CodeGenModule::EmitTopLevelStmt(const Stmt *S) {
  auto *Ty = llvm::FunctionType::get(
    llvm::Type::getInt32Ty(VMContext), false);
  auto *Fn = llvm::Function::Create(
    Ty, llvm::Function::ExternalLinkage, "main", TheModule);

  CodeGenFunction(*this).GenerateCode(S, Fn);
  return;
}

void CodeGenModule::PrintModule() {
  TheModule.print(llvm::outs(), nullptr);
}

