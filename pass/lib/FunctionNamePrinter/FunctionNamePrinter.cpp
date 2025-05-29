#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "FunctionNamePrinter/FunctionNamePrinter.h"

llvm::PreservedAnalyses FunctionNamePrinter::run(const llvm::Function &F, 
  llvm::FunctionAnalysisManager &FAM) {
  dbgs() << "[FunctionNamePrinter] Pass Entry\n";
  return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION,  
    "FnctionNamePrinter",  
    LLVM_VERSION_STRING,  
    [](llvm::PassBuilder &PB) {  
      dbgs() << "[Plugin] Registering FunctionNamePrinter Pass\n";
      PB.registerPipelineParsingCallback(  
        [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,  
           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {  
          if (name == "function-name-printer") { 
            FPM.addPass(FunctionNamePrinter());  
            return true;  
          } else {  
            return false;  
          }
        }
      );  
    }  
  };  
}
