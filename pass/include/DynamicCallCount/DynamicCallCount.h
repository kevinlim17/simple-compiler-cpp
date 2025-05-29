#ifndef __PASS_DYNAMIC_CALL_COUNT_H__
#define __PASS_DYNAMIC_CALL_COUNT_H__

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

struct DynamicCallCount : public PassInfoMixin<DynamicCallCount> {
public:
  PreservedAnalyses run(const Function &F, FunctionAnalysisManager &FAM);
};

#endif
