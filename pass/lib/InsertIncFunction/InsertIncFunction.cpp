#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "InsertIncFunction/InsertIncFunction.h"

PreservedAnalyses InsertIncFunction::run(const Module &M, 
  ModuleAnalysisManager &MAM) {
  dbgs() << "[InsertIncFunction] Pass Entry\n";
  return PreservedAnalyses::all();
}

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION,  
    "InsertIncFunction",
    LLVM_VERSION_STRING, 
    [](PassBuilder &PB) {
      dbgs() << "[Plugin] Registering InsertIncFunction Pass\n";
      PB.registerPipelineParsingCallback(
        [](const StringRef name, ModulePassManager &MPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (name == "insert-inc-function") {
            MPM.addPass(InsertIncFunction()); 
            return true; 
          } else {  
            return false; 
          }
        }
      ); 
    }  
  };  
}
