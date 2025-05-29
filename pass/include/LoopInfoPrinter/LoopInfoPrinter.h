#ifndef __PASS_LOOP_INFO_PRINTER_H__
#define __PASS_LOOP_INFO_PRINTER_H__

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

struct LoopInfoPrinter : public PassInfoMixin<LoopInfoPrinter> {
public:
  PreservedAnalyses run(const Function &F, FunctionAnalysisManager &FAM);
};

#endif
