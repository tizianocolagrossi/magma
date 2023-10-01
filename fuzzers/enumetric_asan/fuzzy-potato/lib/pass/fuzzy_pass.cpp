#include "pass/fuzzy_pass.hpp"


#include "llvm/Support/FileSystem.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Support/ErrorHandling.h"

#include "pass/dump_instrumenter.hpp"

#include "common.hpp"
#include <sys/stat.h>
#include <cerrno>
#include <set>

using namespace llvm;

bool FuzzyPass::isBlacklisted(const Function *F){
    static const char *Blacklist[] = {
        "asan.", "llvm.", "sancov.", "__ubsan_handle_", "ign.", "__afl_",
        "_fini", "__libc_csu", "__asan",  "__msan", "msan.",
    };
    for (auto const &BlacklistFunc : Blacklist) {
        if (F->getName().startswith(BlacklistFunc)) { return true; }
    }

    // if (F->getName() == "main") return true;
    if (F->getName() == "LLVMFuzzerTestOneInput") return true;
    if (F->getName() == "_start") return true;

    return false;
}

PreservedAnalyses FuzzyPass::run(Module &M, ModuleAnalysisManager &AM  ){
    bool Changed = false;
    
    dbgs()<<ANS_CY<<"FuzzyPass::run"<<ANS_RST<<"\n";
    // Map a shared memory to of SharedStats struct created by the 
    // manager.cpp that allocare the Struct in order to achive some 
    // cross modules counters. (used only in build ECOV)
    if (getenv("ECOV")){
        int fd = shm_open("/fuzzy_shstats", O_RDWR, 0666);
        ftruncate(fd, SHM_SIZE);
        void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);
        shStatsPtr = (SharedStats*) ptr;
        shStatsPtr->addModule();
    }

    // flags defined inside the common.hpp file. Control the file where some
    // dumps will be written. Can be one single output file, a single file 
    // for each module or no output file. 
#if defined(OUT_ON_FILE) || defined(OUT_MULTIPLE_FILES)
    std::string path_dir_out = "./dumps/";
    if (getenv("HOME")){
        std::string homepath = std::string(getenv("HOME"));
        path_dir_out = homepath+"/build_dumps/"; 
    }
    int ret = mkdir((const char*) path_dir_out.c_str(),0777);
    if (ret!=0 && errno!=EEXIST) {
        errs()<<"could not create directory\n";
        return llvm::PreservedAnalyses::all();
    }
    std::error_code EC;

#ifdef OUT_MULTIPLE_FILES   
    auto module_name = M.getName().str();
    std::string base_filename = module_name.substr(module_name.find_last_of("/") + 1);
    llvm::raw_fd_ostream tmp_ostream(path_dir_out+base_filename +".dump", EC);
#endif
#ifdef OUT_ON_FILE   
    std::string base_filename = "out";
    llvm::raw_fd_ostream tmp_ostream(path_dir_out+base_filename +".dump", EC,
                                     sys::fs::CreationDisposition::CD_OpenAlways,
                                     sys::fs::FileAccess::FA_Write,
                                     sys::fs::OpenFlags::OF_Append
                                    );
#endif

    if (EC){
        errs()<<"could not crate file dump fallback to errs() or dbgs()";
    }else{
        out = &tmp_ostream;
    }
#endif
    
    D(DUMP_MODULE_NAME, *out<<"[fuzzy_potato] module "<<M.getName()<<"\n");
    //dbgs()<<"IN MODULE "<<M.getName()<<"\n";

    if (getenv("VERBOSE")){
        dbgs()<<ANS_CM<<"[+] IN MODULE: "<<M.getName()<<ANS_RST<<"\n";
    }

    DebugInfoFinder Finder;
    Finder.processModule(M);

    populateTypeMap(&Finder);
    D(DUMP_ALLTYPE_MAP       , dumpAllTypeMap(*out)   );    
    D(DUMP_ENUMS_IN_TYPE_MAP , dumpEnumInTypeMap(*out));  

    for(GlobalVariable &GV : M.getGlobalList()){
        globals_declare.insert(&GV);
    }

    for(auto &F:M){
        if(F.isDeclaration())continue;
        if (isBlacklisted(&F)) continue;
        
        analyzeFunctionAndFillLists(&F);
    }

    analyzeCollectedListAndBuildValueMap();
    
    // get all enums declared in the code
    // insert in origins (enum_origins)
    searchEnumOrigins();

    auto &FAM = AM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();

    
    //[TODO] write better here
    if(origins.size() > 0){
        dbgs()<<ANS_CY<<"FuzzyPass"<<ANS_RST<<" ["<<ANS_CG<<"!"<<ANS_RST<<"] Origins found\n";

        if (getenv("ECOV")){
            if (shStatsPtr == 0){
                report_fatal_error("ERROR: shStatsPtr during ECOV build is null. there is the need to run the program manager_sh_stats placed inside build/lib/managershmem!");
            }
            CoverageDumperAA instrumenter = CoverageDumperAA(&M, &FAM, shStatsPtr);
            instrumenter.setOut(out);

            Changed |= instrumenter.insertInstrumentation(origins);

        }else{
            InstrumenterAA instrumenter = InstrumenterAA(&M, &FAM);
            instrumenter.setOut(out);

            Changed |= instrumenter.insertInstrumentation(origins);
        }
    }

    // Unmap the dhared mamory of the SharedStats structs
    if (getenv("ECOV")){
        munmap(shStatsPtr, SHM_SIZE);
    }

    return (Changed ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}

void FuzzyPass::populateTypeMap(DebugInfoFinder* finder){
    
    // iterate over the type found by the DebugInfoFinder and for each 
    // DIType* will create an DbgTypeInfo instance and will insert that 
    // into the typeinfo_set in order to get a set with all the types 
    // present inside the module currently under analysis.
    for(auto type_found:finder->types()){
        if(!type_found)continue;
        DbgTypeInfo tinfo = DbgTypeInfo(type_found);
        typeinfo_set.insert(tinfo);
    }

    // Here we iterate over the set of the types present in the module under
    // analysis and we create map with key the DbgTypeInfo instance present
    // inside the typeinfo_set created above. 
    // [TODO] maybe we can avod to create before the set and check if a key
    // is alredy present into the map. (Yup)
    for(auto ti : typeinfo_set){
        typeinfo_map[ti] = {};
    }

    // Iterating over the typeinfo_map we insert into the set linked to 
    // the type as key, its inner element. So inside typeinfo_map[StructTy] 
    // we have the set of DbgTypeInfo of the element of the struct.
    // With this we can found also the enum that are inside a struct.
    for(auto [type, set_elem]:typeinfo_map){
        if(type.getActualTTag() != dwarf::DW_TAG_structure_type) continue;

        DIType* actual = type.getActualType();
        DICompositeType * CT = dyn_cast<DICompositeType>(actual);
        if(!CT)continue;

        for(auto elem:CT->getElements()){
             DIDerivedType* DID = dyn_cast<DIDerivedType>(elem);
             if(!DID)continue;
             typeinfo_map[type].insert(DbgTypeInfo(DID));
        }
    }
}

void FuzzyPass::analyzeFunctionAndFillLists(Function* F){
    for(auto &I:instructions(F)){
        if(auto call = dyn_cast<CallBase>(&I)){
            collectCallBases(call);
            continue;
        }
        if(auto gep = dyn_cast<GetElementPtrInst>(&I)){
            collectGEPs(gep);
            continue;
        }
    }
}

void inline FuzzyPass::collectCallBases(CallBase* CB){
    if(!CB->getCalledFunction())return;
    StringRef name = CB->getCalledFunction()->getName();
    if(auto callDbgIntrinsic = dyn_cast<DbgVariableIntrinsic>(CB)){
        dbg_info_instrinsic.insert(callDbgIntrinsic);
        return;
    }
    return;
 }

void inline FuzzyPass::collectGEPs(GetElementPtrInst* GEP){
    if(GEP->hasAllConstantIndices()){
        gep_constant.insert(GEP);
        return;
    }
    // [TODO] this may be removed since was an idea to achive coverage over
    // the indices of a GEP instruction, so array, struct etc.
#ifdef INSTR_GEP_OFF
    // gep_non_constant.insert(GEP);
    for (unsigned i=1; i<GEP->getNumOperands(); i++){
        Value* ind = GEP->getOperand(i);
        if(isa<Constant>(ind))continue;
        Origin new_origin = Origin(ind, OriginType::ORIG_GEP_OFF, i);
        origins.insert(new_origin);
    }
#endif
    return;
}

void FuzzyPass::analyzeCollectedListAndBuildValueMap(){

    // Create entry into the valueinfo_map for GlobalVariables 
    // resent in the mofule.
    for(GlobalVariable *GV : globals_declare){
        if(!GV){continue;}
        SmallVector<DIGlobalVariableExpression *, 1> GVEs;
        GV->getDebugInfo(GVEs);
        
        if(GVEs.size()==0) continue;
        for (DIGlobalVariableExpression *GVE : GVEs){
            if(!GVE)continue;

            DIGlobalVariable* di_variable_declared = GVE->getVariable();

            valueinfo_map[GV] = std::shared_ptr<DbgValueInfo>(new DbgValueInfo(GV, di_variable_declared));
            break;
        } 

        D(DUMP_COST_VALUE_MAP,dbgs()<<ANS_BGB<<"find global"<<*GV<<ANS_RST<<"\n");

    }
    
    // Create entry into the valueinfo_map for local variables into the module 
    // the DbgDeclareInst is an intrinsic that will indicate a new declared
    // variables.
    for(DbgVariableIntrinsic* dbg_call: dbg_info_instrinsic){
        if(!dbg_call) continue;
        if(!isa<DbgDeclareInst>(dbg_call))continue;
        if(!dbg_call->getCalledFunction()) continue; // callbase not has a function

        DbgVariableIntrinsic* call = dyn_cast<DbgVariableIntrinsic>(dbg_call);
        if(!call){continue;}

        StringRef name = call->getCalledFunction()->getName();
        if(!name.endswith("declare")){continue;}

        DIVariable* di_variable_declared = call->getVariable();
        if(!di_variable_declared){continue;}

        Value * value_declared = call->getVariableLocationOp(0);
        if(!value_declared){continue;}

        //cheks

        valueinfo_map[value_declared] = std::shared_ptr<DbgValueInfo>(new DbgValueInfo(value_declared, di_variable_declared));
        D(DUMP_COST_VALUE_MAP,dbgs()<<ANS_BGR<<"find local"<<*value_declared<<ANS_RST<<"\n");

    }

    // Create entry into the valueinfo_map for GEP references into the module 
    for(GetElementPtrInst* GEP: gep_constant){
        if(!GEP)continue;

        Value* pointerOp = GEP->getPointerOperand();
        auto ite = valueinfo_map.find(pointerOp);
        if(ite == valueinfo_map.end())continue;
        std::shared_ptr<DbgValueInfo> dbgVI = valueinfo_map[pointerOp];
        if(!dbgVI){continue;}
    
        if(!(GEP->getNumIndices()==2
                &&GEP->getPointerOperandIndex()==0
                &&dbgVI->getActualTTag()==dwarf::DW_TAG_structure_type)){
            // dbgs()<<"GEP->getNumIndices()==2)&&GEP->getPointerOperandIndex()==0 FAIL\n";
            continue;
        }
        // get the index to retrive the right element in the struct
        auto ind=GEP->idx_begin();
        ind++;
        ConstantInt* CI = dyn_cast<ConstantInt>(*ind);
        if(CI==nullptr)continue;
        if(CI->getBitWidth() > 32) continue;
        int index = CI->getSExtValue();

        DbgTypeInfo* tyinfo = dbgVI->getTypeInfo();
        if(!tyinfo)continue;
        auto pointer_set = typeinfo_map[*tyinfo];
        if(pointer_set.size() <= index){
            errs()<<"Ponter to an element at offset bigger respect the size of the struct ";
            errs()<<"index "<<index<<" struct size "<<pointer_set.size()<<"\n";
            continue;
        }
        auto it = pointer_set.begin();
        std::advance(it, index);
        const DbgTypeInfo* x = &*it;
        
        valueinfo_map[GEP] = std::shared_ptr<DbgValueInfo>(new DbgValueInfo(GEP, *x));
        D(DUMP_COST_VALUE_MAP,dbgs()<<ANS_BGY<<"find GEP"<<*GEP<<ANS_RST<<"\n");

    }
}

void FuzzyPass::searchEnumOrigins(){
#ifdef INSTR_ENUMS
    //collect all the enums
    for(auto [val, dbgVinfo]:valueinfo_map){

        std::set<const Value*> place_enums_used = {};
        if(!val || !dbgVinfo.get())continue;
        DbgTypeInfo* typeInfo = dbgVinfo->getTypeInfo();

        if(typeInfo->getActualTTag()!=dwarf::DW_TAG_enumeration_type) continue;

        DIType* llvmDbgTypeInfo = typeInfo->getActualType();
        DICompositeType * CT = dyn_cast<DICompositeType>(llvmDbgTypeInfo);

        // [TODO] Here the defined values set can be removed from the 
        // Origin object and can be calculated inside the InstrumenterAA
        // since the data is saved inside the DbgTypeInfo inside the Origin
        std::set<int> DefinedValues = {};
        for(auto x:CT->getElements()){
            DIEnumerator* DIE = dyn_cast<DIEnumerator>(x);
            if(!DIE)continue;
            DefinedValues.insert(DIE->getValue().getSExtValue());
        }

        Origin new_origin = Origin(val, OriginType::ORIG_ENUM, *typeInfo, DefinedValues);
        origins.insert(new_origin);
    }
#endif
}

//    ___                    
//   / _ \__ ____ _  ___  ___
//  / // / // /  ' \/ _ \(_-<
// /____/\_,_/_/_/_/ .__/___/
//                /_/       

void FuzzyPass::dumpAllTypeMap(raw_ostream &OS){
    OS<<SEPARATOR;
    OS<<ANS_BGM<<ANS_CY<<" Dump TypeInfoMap "<<ANS_RST<<"\n";
    for(auto [type, set]:typeinfo_map){    
        OS<<SEPARATOR;
        type.dump(OS);
        if(set.size()==0)continue;
        OS<<ANS_BGB<<ANS_CW<<"elem:   --------------------------------------------------------------------"<<ANS_RST<<"\n";
        for(auto el: set){
            OS<<"\tTypeName: "<<ANS_CG<<el.getName()<<ANS_RST<<" "
                  <<"facial: "<<TagString(el.getFaceTTag())
                  <<"\n\tactual: "<<ANS_CG<<TagString(el.getActualTTag())<<ANS_RST<<" "
                  <<"size: "<<el.getSize()<<"bit offset@"<<el.getOffset()<<"\n"
                  <<"\t--------------------------------------------------------------------\n";
        }
    }
    OS<<SEPARATOR;
}

void FuzzyPass::dumpEnumInTypeMap(raw_ostream &OS){
    for(auto [type, set]:typeinfo_map){
        if(type.getActualTTag() == dwarf::Tag::DW_TAG_enumeration_type){
            type.dump(OS);
            DICompositeType* CTenum = dyn_cast<DICompositeType>(type.getActualType());
            if(!CTenum)continue;
            for(auto x:CTenum->getElements()){
                DIEnumerator* DIE = dyn_cast<DIEnumerator>(x);
                if(!DIE)continue;
                OS<<"\t<"<<DIE->getName()<<">:"<<DIE->getValue()<<"\n";
            } 
        }
            
    }
}
