#ifndef __PASS_INSERT_INC_FUNCTION_H__
#define __PASS_INSERT_INC_FUNCTION_H__

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

struct InsertIncFunction : PassInfoMixin<InsertIncFunction> {
  static PreservedAnalyses run(const Module &M, ModuleAnalysisManager &MAM);
};

#endif
