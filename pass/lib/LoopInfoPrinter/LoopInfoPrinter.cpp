#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "LoopInfoPrinter/LoopInfoPrinter.h"

llvm::PreservedAnalyses LoopInfoPrinter::run(const llvm::Function &F, 
  llvm::FunctionAnalysisManager &FAM) {
  dbgs() << "[LoopInfoPrinter] Pass Entry\n";
  return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {  
  return {  
    LLVM_PLUGIN_API_VERSION,  
    "LoopInfoPrinter",  
    LLVM_VERSION_STRING,  
    [](llvm::PassBuilder &PB) {  
      dbgs() << "[Plugin] Registering LoopInfoPrinter Pass\n";
      PB.registerPipelineParsingCallback(  
        [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,  
           llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {  
          if (name == "loop-info-printer") {  
            FPM.addPass(LoopInfoPrinter());  
            return true;  
          } else { 
            return false;  
          }
        }
      );  
    }  
  };  
}
