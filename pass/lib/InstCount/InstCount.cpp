#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "InstCount/InstCount.h"

llvm::PreservedAnalyses InstCount::run(const llvm::Function &F, 
  llvm::FunctionAnalysisManager &FAM) {
  dbgs() << "[InstCount] Pass Entry\n";
  return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION,
    "InstCount",
    LLVM_VERSION_STRING,
    [](llvm::PassBuilder &PB) {
      dbgs() << "[Plugin] Registering InstCount Pass\n";
      PB.registerPipelineParsingCallback(
        [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
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
