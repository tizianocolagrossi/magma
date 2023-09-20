/**
 * @brief Pass that will set name to the instuctions that does't have a name.
 * For the requirements of the fuzzy pass, in order to get some dumps 
 * readable this pass will set a name to the LoadInst and StoreInst with
 * an iincrementing counter for the StoreInst and the LoadInst.
 */
#include "pass/instnamer_module.hpp"

using namespace llvm;

PreservedAnalyses InstnamerModule::run(Module &M, ModuleAnalysisManager &AM  ){
    bool Changed = false;

    for(auto &F:M)
        Changed |= nameInstructions(F);
    
    return (Changed ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}


bool InstnamerModule::nameInstructions(Function &F) {

    bool Changed = false;

    unsigned long argcounter = 0;
    for (auto &Arg : F.args()) {
        if (!Arg.hasName()){
            Changed |= true;
            Twine suffix = "i";
            Twine name = suffix.concat(Twine(argcounter++));
            Arg.setName(name);
        }
            
    }
    unsigned long bbcounter = 0;
    for (BasicBlock &BB : F) {
        if (!BB.hasName()){
            Changed |= true;
            Twine suffix = "bb";
            Twine name = suffix.concat(Twine(bbcounter++));
            BB.setName(name);
        }

        unsigned long load_counter = 0;
        unsigned long store_counter = 0;
        for (Instruction &I : BB) {
            if (!I.hasName()){
                if(I.getType()->isVoidTy()){
                    if(!isa<StoreInst>(I))continue;
                    Changed |= true;
                    Twine suffix = "store";
                    Twine name = suffix.concat(Twine(store_counter++));
                    I.setName(name);
                }else{
                    if(!isa<LoadInst>(I))continue;
                    Changed |= true;
                    Twine suffix = "load";
                    Twine name = suffix.concat(Twine(load_counter++));
                    I.setName(name);
                }
            }
        }
    }
    return Changed;
}

