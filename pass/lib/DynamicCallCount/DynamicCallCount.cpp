#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "DynamicCallCount/DynamicCallCount.h"

llvm::PreservedAnalyses DynamicCallCount::run(const llvm::Function &F, 
  llvm::FunctionAnalysisManager &FAM) {
  dbgs() << "[DynamicCallCount] Pass Entry\n";
  return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION, 
    "DynamicCallCount", 
    LLVM_VERSION_STRING, 
    [](llvm::PassBuilder &PB) {  
      dbgs() << "[Plugin] Registering DynamicCallCount Pass\n";
      PB.registerPipelineParsingCallback( 
        [](const llvm::StringRef name, llvm::FunctionPassManager &FPM, 
           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) { 
          if (name == "dynamic-call-count") {
            FPM.addPass(DynamicCallCount());
            return true;
          } else {
            return false;
          }
        }
      ); 
    }
  };  
}
