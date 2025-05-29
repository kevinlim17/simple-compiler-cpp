#ifndef __PASS_FUNCTION_NAME_PRINTER_H__
#define __PASS_FUNCTION_NAME_PRINTER_H__

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

struct FunctionNamePrinter : public PassInfoMixin<FunctionNamePrinter> {
public:
  static PreservedAnalyses run(const Function &F, FunctionAnalysisManager &FAM);
};

#endif
