#include "llvm/IR/Constants.h"
#include "CodeGen/CodeGenFunction.h"

CodeGenFunction::CodeGenFunction(CodeGenModule &cgm)
  : CGM(cgm), ACC(nullptr), Builder(cgm.getLLVMContext()){ }

void CodeGenFunction::GenerateCode(const Stmt *S, llvm::Function *F) {
  llvm::LLVMContext &Context = F->getContext();
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(F->getContext(), "entry", F);
  Builder.SetInsertPoint(BB);
 
  // Emit statements based on the AST
  EmitStmt(S);
  
  // Create the return instruction
  Builder.CreateRet(ACC);
}

llvm::Value *CodeGenFunction::EmitExpr(const Expr *E) { 
  if (auto NE = dynamic_cast<const NumExpr*>(E)) {
    return EmitNumExpr(NE);
  }
  return nullptr;
}

llvm::Value *CodeGenFunction::EmitNumExpr(const NumExpr *NE) {
  return llvm::ConstantInt::get(CGM.getLLVMContext(), llvm::APInt(32, NE->getVal()));;
}

void CodeGenFunction::EmitStmt(const Stmt *S) {
  if (auto *BCS = dynamic_cast<const BinaryCalcStmt*>(S)) {
    EmitBinaryCalcStmt(BCS);
  }
}

void CodeGenFunction::EmitBinaryCalcStmt(const BinaryCalcStmt *BCS) {
  llvm::Value *LV = EmitExpr(BCS->getLHS());
  llvm::Value *RV = EmitExpr(BCS->getRHS());

  llvm::Value *V = nullptr;
  switch (BCS->getOpCode()) {
  case op::add:
    V = Builder.CreateAdd(LV, RV, "add");
    break;
  case op::sub:
    V = Builder.CreateSub(LV, RV, "sub");
    break;
  case op::mul:
    V = Builder.CreateMul(LV, RV, "mul");
    break;
  case op::div: 
    V = Builder.CreateSDiv(LV, RV, "div");
    break;
  }
  
  ACC = V;
  return;
}
