#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "DynamicCallCount/DynamicCallCount.h"

PreservedAnalyses DynamicCallCount::run(const Function &F, 
  FunctionAnalysisManager &FAM) {
  dbgs() << "[DynamicCallCount] Pass Entry\n";
  return PreservedAnalyses::all();
}

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION, 
    "DynamicCallCount", 
    LLVM_VERSION_STRING, 
    [](PassBuilder &PB) {  
      dbgs() << "[Plugin] Registering DynamicCallCount Pass\n";
      PB.registerPipelineParsingCallback( 
        [](const StringRef name, FunctionPassManager &FPM, 
           ArrayRef<PassBuilder::PipelineElement>) { 
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
