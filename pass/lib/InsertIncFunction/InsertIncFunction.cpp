#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "InsertIncFunction/InsertIncFunction.h"

llvm::PreservedAnalyses InsertIncFunction::run(const llvm::Module &M, 
  llvm::ModuleAnalysisManager &FAM) {
  dbgs() << "[InsertIncFunction] Pass Entry\n";
  return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION,  
    "InsertIncFunction",
    LLVM_VERSION_STRING, 
    [](llvm::PassBuilder &PB) {
      dbgs() << "[Plugin] Registering InsertIncFunction Pass\n";
      PB.registerPipelineParsingCallback(
        [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
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
