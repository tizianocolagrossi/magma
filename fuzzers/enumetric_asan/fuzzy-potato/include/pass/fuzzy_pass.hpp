#pragma once

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/DebugInfo.h"

#include "pass/dbg_type_info.hpp"
#include "pass/dbg_value_info.hpp"
#include "pass/origin.hpp"

#include "managershmem/manager.hpp"

#include <new>  // for placement new
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include <memory>

// cmp elements in struct to order by offset
struct cmp_type_str {
    bool operator() (const DbgTypeInfo a,const DbgTypeInfo b)const {
      return a.getOffset()<b.getOffset(); };
};

class FuzzyPass : public llvm::PassInfoMixin<FuzzyPass> {
  
  /**
   * [TODO] this can (and shuld) be remobed from here
   */
  std::set<DbgTypeInfo> typeinfo_set  = {};

  /**
   * Map that mantain the link between an DbgTypeInfo and its inner elements
   */
  std::map<DbgTypeInfo, std::set<DbgTypeInfo, cmp_type_str>> typeinfo_map  = {};

  /**
   * Map that mantain the link between an llvm::Value* to its DbgValueInfo
   * so using this we can get the DIType of a value and other infos
   * saved inside the DbgValueInfo object.
   */
  std::map<Value*, std::shared_ptr<DbgValueInfo>>   valueinfo_map = {};

  // [TODO] those can be removed from here and should be passed as params
  // to the function that use this.
  std::set<GlobalVariable*>       globals_declare      = {};
  std::set<DbgVariableIntrinsic*> dbg_info_instrinsic  = {};
  std::set<GetElementPtrInst*>    gep_constant         = {};
  // [TODO] This can be removed since wa part of the idea of instrument 
  // also the index of the geps
  // std::set<GetElementPtrInst*>    gep_non_constant     = {};

  std::set<Origin>                origins              = {};

  const int SHM_SIZE = sizeof(SharedStats);
  SharedStats* shStatsPtr = nullptr;

public:
  FuzzyPass() {}
  ~FuzzyPass(){}

  static bool isBlacklisted(const Function *F);

  llvm::raw_ostream *out = &llvm::dbgs();

  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &AM);

private:

 /**
  * Function used to find all Type defined inside the source code 
  * @param finder Pointer to instance of llvm::DebugInfoFinder 
  * This function will iterate over the type found by the @finder and will 
  * create an DbgTypeInfo instance that will contain the name of the type 
  * found, the subtypes of that type, the size and the offset if is inside 
  * a struct. And will popolate the typeinfo_set and the typeinfo_map.
  */
  void populateTypeMap(llvm::DebugInfoFinder *finder);
 

 /**
  * Fill the valueinfo_map with the info collected before.
  * Using the globals_declare, dbg_info_instrinsic and gep_constant list/map
  * will fill the valueinfo_map that will link a llvm::Value* to a DbgValueInfo
  * instance. The DbgValueInfo class will mantain the reference to the 
  * DbgTypeInfo of the value used as key of the valueinfo_map and also the
  * line where is used, the reference of the llvm::Value, the name of the 
  * llvm::Value and the directory and the file where the Value is present.
  */
  void analyzeCollectedListAndBuildValueMap();
 
 /**
  * Search inside the valueinfo_map the llvm::Value that are enums
  * This function will scan the valueinfo_map in search of values that
  * are Enums and will create an Origin object for each values of type 
  * Enum that will be used to instrument the module. 
  * The Origin calss indicate an origin of instrumentation and the class 
  * contain the origin type (since this pass was thinked in order to have
  * different origins like enum, global, gep_index etc), the llvm::Value* 
  * of the origin, the possible values that the origin can assume (if is an
  * Enum) the operandIndex (if is an origin of type gep_index) and will mantain
  * also an object of type DbgTypeInfo. 
  */
  void searchEnumOrigins();

 /**
  * Analyse the function passed iterating over the instructions   
  * @param F Pointer to llvm::Function that will be analyzed
  * Will iterate over the instruction of the function F and will call 
  * the functions collectCallBases and collectGEPs that will analyze as
  * the name suggest the CallBase and the GEP instructions.
  */
  void analyzeFunctionAndFillLists(Function* F);

 /**
  * If the CB is a DbgVariableIntrinsic will be saved into dbg_info_instrinsic
  * @param CB pointer to CallBase instances under analysis
  */
  void collectCallBases(CallBase* CB);

 /**
  * If the GEP has all constant indices will be saved into gep_constant
  * @èaram GEP pointer to GetElementPtrInst instances under analysis
  */
  void collectGEPs(GetElementPtrInst* GEP);

  void dumpAllTypeMap(raw_ostream &OS);
  void dumpEnumInTypeMap(raw_ostream &OS);

};
