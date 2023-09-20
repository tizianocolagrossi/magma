#pragma once

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"


class InstnamerModule : public llvm::PassInfoMixin<InstnamerModule> {
  
public:
  InstnamerModule() {}
  ~InstnamerModule(){}
  
  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &AM);

private:
  bool nameInstructions(llvm::Function &F);
};