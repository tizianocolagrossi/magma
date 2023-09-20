#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "pass/instnamer_module.hpp"
#include "pass/fuzzy_pass.hpp"


using namespace llvm;
//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------

PassPluginLibraryInfo getPocPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "potato-dump", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            using OptimizationLevel = typename PassBuilder::OptimizationLevel;
             PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel OL) {
                    MPM.addPass(InstnamerModule());
                    MPM.addPass(FuzzyPass());
                    return true;
                });  
          }};
}


extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getPocPassPluginInfo();
}