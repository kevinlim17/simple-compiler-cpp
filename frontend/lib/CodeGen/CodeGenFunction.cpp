#include "llvm/IR/Constants.h"
#include "CodeGen/CodeGenFunction.h"

#include "Parse/AST.h"

CodeGenFunction::CodeGenFunction(CodeGenModule &cgm)
    : CGM(cgm), Builder(cgm.getLLVMContext()), ACC(nullptr) {
}

void CodeGenFunction::GenerateCode(const Stmt *S, llvm::Function *F) {
    llvm::LLVMContext &Context = F->getContext();
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(Context, "entry", F);
    Builder.SetInsertPoint(BB);

    // Emit statements based on the AST
    EmitStmt(S);

    // Create the return instruction
    Builder.CreateRet(ACC);
}

llvm::Value *CodeGenFunction::EmitExpr(const Expr *E) {
    if (auto NE = dynamic_cast<const NumExpr *>(E)) {
        return EmitNumExpr(NE);
    }
    return nullptr;
}

llvm::Value *CodeGenFunction::EmitNumExpr(const NumExpr *NE) {
    return llvm::ConstantInt::get(CGM.getLLVMContext(), llvm::APInt(32, NE->getVal()));;
}

void CodeGenFunction::EmitStmt(const Stmt *S) {
    if (auto *CSS = dynamic_cast<const CompoundStmts *>(S)) {
        EmitCompoundStmt(CSS);
    }
}

void CodeGenFunction::EmitCompoundStmt(const CompoundStmts *CS) {
    if (auto *FIRST_STM = dynamic_cast<const BinaryCalcStmt *>(CS->getFirstStm().get())) {
        EmitBinaryCalcStmt(FIRST_STM);
    }
    if (auto *MIDDLE_STM = dynamic_cast<const CompoundUnaryStmts *>(CS->getUnaryStms().get())) {
        EmitCompoundUnaryStmts(MIDDLE_STM);
    }
    if (auto *LAST_STM = dynamic_cast<const PrintStmt *>(CS->getLastStm().get())) {
        EmitPrintStmt(LAST_STM);
    }
}

void CodeGenFunction::EmitCompoundUnaryStmts(const CompoundUnaryStmts *CUS) {
    if (auto *FIRST_UNARY_STM = dynamic_cast<const UnaryCalcStmt *>(CUS->getFirstUnaryStm().get())) {
        EmitUnaryCalcStmt(FIRST_UNARY_STM);
    }
    if (auto *LAST_UNARY_STMS = dynamic_cast<const CompoundUnaryStmts *>(CUS->getLastUnaryStm().get())) {
        EmitCompoundUnaryStmts(LAST_UNARY_STMS);
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
        default:
            break;
    }

    ACC = V;
    return;
}

void CodeGenFunction::EmitUnaryCalcStmt(const UnaryCalcStmt *UCS) {
    llvm::Value *OPERAND = EmitExpr(UCS->getOperand());

    llvm::Value *STMT_VALUE = nullptr;
    switch (UCS->getOpCode()) {
        case op::add:
            STMT_VALUE = Builder.CreateAdd(ACC, OPERAND, "add");
            break;
        case op::sub:
            STMT_VALUE = Builder.CreateSub(ACC, OPERAND, "sub");
            break;
        case op::mul:
            STMT_VALUE = Builder.CreateMul(ACC, OPERAND, "mul");
            break;
        case op::div:
            STMT_VALUE = Builder.CreateSDiv(ACC, OPERAND, "div");
            break;
        default:
            break;
    }

    ACC = STMT_VALUE;
    return;
}

void CodeGenFunction::EmitPrintStmt(const PrintStmt *PS) {
    llvm::FunctionType *printfType = llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(CGM.getLLVMContext()),
        llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(CGM.getLLVMContext())),
        true
    );
    const llvm::FunctionCallee printfFunc = CGM.getModule().getOrInsertFunction("printf", printfType);

    /** Global Variable for Formatting */
    llvm::Value *formatStr = Builder.CreateGlobalString("Result: %d\n");

    /** Call printf */
    Builder.CreateCall(printfFunc, {formatStr, ACC});
}
