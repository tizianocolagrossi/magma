#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Type.h"
#include "pass/dbg_type_info.hpp"

#include "pass/origin.hpp"
#include "managershmem/manager.hpp"

#include <set>
#include <vector>
#include <algorithm>

using namespace llvm;

// cmp elements in struct to order by offset

class DumpInstrumenterBase{

public:
    unsigned long block_inserted = 0;

    Module * M = nullptr;
    FunctionAnalysisManager * FAM = nullptr;
    LLVMContext* C = nullptr;
    Type* VoidTy = Type::getVoidTy(*C);
    Type* Int8Ty = IntegerType::get(*C, 8);
    Type* Int16Ty = IntegerType::get(*C, 16);
    Type* Int32Ty = IntegerType::get(*C, 32);
    Type* Int64Ty = IntegerType::get(*C, 64);
    Type* Int8PTy  = PointerType::get(Int8Ty, 0);
    Type* Int32PTy = PointerType::get(Int8Ty, 0);

    Type* UInt64Ty   = Type::getIntNTy(*C, 64);

    Constant* null_i8  = Constant::getNullValue(Int8Ty );
    Constant* null_i16 = Constant::getNullValue(Int16Ty);
    Constant* null_i32 = Constant::getNullValue(Int32Ty);
    Constant* null_i64 = Constant::getNullValue(Int64Ty);

    FunctionCallee dump_enum_0 = M->getOrInsertFunction("__potato_dump_enum_i8" , VoidTy, Int8PTy, Int8PTy, Int8Ty );
    FunctionCallee dump_enum_1 = M->getOrInsertFunction("__potato_dump_enum_i16", VoidTy, Int8PTy, Int8PTy, Int16Ty);
    FunctionCallee dump_enum_2 = M->getOrInsertFunction("__potato_dump_enum_i32", VoidTy, Int8PTy, Int8PTy, Int32Ty);
    FunctionCallee dump_enum_3 = M->getOrInsertFunction("__potato_dump_enum_i64", VoidTy, Int8PTy, Int8PTy, Int64Ty);

    // FunctionCallee dump_enter = M->getOrInsertFunction("__potato_dump_enter_prologue", VoidTy, VoidTy);
    // FunctionCallee dump_exit  = M->getOrInsertFunction("__potato_dump_exit_prologue" , VoidTy, VoidTy);
    // FunctionCallee dump_place = M->getOrInsertFunction("__potato_dump_origin_place"  , VoidTy, Int8PTy, Int8PTy, UInt64Ty);
    
    // replaced with global volatile variables
    // FunctionCallee noop_function = M->getOrInsertFunction("__potato_noop", VoidTy, VoidTy);
    GlobalVariable* noop_volatile = new GlobalVariable(*M
                                                      , Int32Ty
                                                      , false /*isConstant=*/
                                                      , GlobalValue::CommonLinkage
                                                      , ConstantInt::get(Int32Ty, 0) /*Initializer=*/
                                                      , "noop_volatile");

    FunctionCallee dumpEnumDeclFn = M->getOrInsertFunction("__potato_declaration_enum", VoidTy, Int8PTy, Int8PTy);

    llvm::raw_ostream *out = &llvm::dbgs();

    

    DumpInstrumenterBase(Module* _M, FunctionAnalysisManager *_FAM)
        :M(_M),FAM(_FAM), C( &(_M->getContext()) ){};
    ~DumpInstrumenterBase(){};
    
    void injectRTDeclareEnum(Instruction* where, std::string type_name, std::string name);
    void injectRTDumpEnum(Instruction* where, std::string type_name, std::string name, Value* what, Value* what_ptr  = 0x0);
    void injectEnumBlocks(Instruction* where, Value* what, std::set<int> declaredValues);

    size_t TypeSizeToSizeIndex(uint32_t TypeSize){
        if(TypeSize == 1) TypeSize = 8;
        size_t ind = countTrailingZeros(TypeSize / 8);
        return ind;
    }

    std::set<Value*> getPointersAlias(Value* val);
    std::set<Value*> getPointersAliasOfGlobal(Value* val);

    void incrementVolatile(IRBuilderBase *IRB, GlobalValue* globalToIncrement, int incVal = -1);

    void setOut(raw_ostream *_out){out=_out;}
    virtual bool insertInstrumentation(){return false;};
};

class InstrumenterAA: public DumpInstrumenterBase{

public:
    InstrumenterAA(Module* _M, FunctionAnalysisManager *_FAM): DumpInstrumenterBase(_M, _FAM) {};
    ~InstrumenterAA(){};

    bool insertInstrumentation(std::set<Origin> origins);
    bool instrumentEnumOrigin(Origin O);
    // bool instrumentGlobalOrigin(Origin O);
    // bool instrumentGepOffOrigin(Origin O);
};

class CoverageDumperAA: public DumpInstrumenterBase{

    SharedStats*    shStatsPtr = nullptr;

    FunctionCallee cov_enum_0 = M->getOrInsertFunction("__potato_cov_enum_i8" , VoidTy, Int8PTy, /*UInt64Ty,*/ Int8Ty , Int32Ty, Int32Ty, Int32Ty);
    FunctionCallee cov_enum_1 = M->getOrInsertFunction("__potato_cov_enum_i16", VoidTy, Int8PTy, /*UInt64Ty,*/ Int16Ty, Int32Ty, Int32Ty, Int32Ty);
    FunctionCallee cov_enum_2 = M->getOrInsertFunction("__potato_cov_enum_i32", VoidTy, Int8PTy, /*UInt64Ty,*/ Int32Ty, Int32Ty, Int32Ty, Int32Ty);
    FunctionCallee cov_enum_3 = M->getOrInsertFunction("__potato_cov_enum_i64", VoidTy, Int8PTy, /*UInt64Ty,*/ Int64Ty, Int32Ty, Int32Ty, Int32Ty);

    void injectRTCovDumpEnum(Instruction* where, std::string type_name, Value* what, Value* what_ptr, unsigned oid);

public:
    CoverageDumperAA(Module* _M, FunctionAnalysisManager *_FAM, SharedStats* _shstat): DumpInstrumenterBase(_M, _FAM), shStatsPtr(_shstat) {};
    ~CoverageDumperAA(){};

    bool insertInstrumentation(std::set<Origin> origins);
    bool instrumentEnumOrigin(Origin O, unsigned oid);
    // bool instrumentGlobalOrigin(Origin O, unsigned oid);
    // bool instrumentGepOffOrigin(Origin O, unsigned oid);

};

