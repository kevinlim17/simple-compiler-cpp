#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "InstCount/InstCount.h"

PreservedAnalyses InstCount::run(const Function &F, 
  FunctionAnalysisManager &FAM) {
  dbgs() << "[InstCount] Pass Entry\n";
  return PreservedAnalyses::all();
}

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION,
    "InstCount",
    LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      dbgs() << "[Plugin] Registering InstCount Pass\n";
      PB.registerPipelineParsingCallback(
        [](const StringRef name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (name == "inst-count") {
            FPM.addPass(InstCount());
            return true; 
          } else {
            return false;
          }
        }
      );  
    }  
  };  
}
