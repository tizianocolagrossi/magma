#include "pass/dump_instrumenter.hpp"

// #include "llvm/ADT/TinyPtrVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/ConstantRange.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
// #include "llvm/IR/DebugInfo.h"
#include "common.hpp"
#include "pass/origin.hpp"

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LazyValueInfo.h"
#include "llvm/IR/CFG.h"



using namespace llvm;

//   ___         _                          _            _   _ _               
//  |_ _|_ _  __| |_ _ _ _  _ _ __  ___ _ _| |_ ___ _ _ /_\ | (_)__ _ ___ __ _ 
//   | || ' \(_-<  _| '_| || | '  \/ -_) ' \  _/ -_) '_/ _ \| | / _` (_-</ _` |
//  |___|_||_/__/\__|_|  \_,_|_|_|_\___|_||_\__\___|_|/_/ \_\_|_\__,_/__/\__,_|

bool InstrumenterAA::insertInstrumentation(std::set<Origin> origins){
    bool Changed = false;
    D( DUMP_ORIGINS_INSTRU ,
    *out<<"origins "<<origins.size()<<"\n"
    );

    unsigned cori = 0;
    unsigned orilen = origins.size();
    for(auto O:origins){

        cori++;
        if (getenv("VERBOSE")){
            dbgs()<<"\n[+] origin value: "<<*O.get()<<"\n";
            DbgTypeInfo* DT = O.getDbgTypeInfo();
            if(DT)
                dbgs()<<"[i] TypeName: "<<DT->getName()<<"\n";
            dbgs()<<"[+] \tinj:"<<orilen<<" : "<<cori<<"\n";
        }
        if(!O.get())continue;
        
        D( DUMP_ORIGINS_INSTRU ,
        *out<<"value: "<<*O.get()<<"\n";
        *out<<"\tenum: "<<O.get()->getName()<<" type:"<< O.getDbgTypeInfo()->getName()<<"\n";
        DICompositeType* CTenum = dyn_cast<DICompositeType>(O.getDbgTypeInfo()->getActualType());
        if(!CTenum)continue;
        for(auto x:CTenum->getElements()){
            DIEnumerator* DIE = dyn_cast<DIEnumerator>(x);
            if(!DIE)continue;
            *out<<"\t\t<"<<DIE->getName()<<">:"<<DIE->getValue()<<"\n";
        });

        switch(O.getType()){
            case OriginType::ORIG_ENUM:
                Changed |= instrumentEnumOrigin(O);
                break;
            // Idea to expand this concept
            // case OriginType::ORIG_GLOBAL:
            //     Changed |= instrumentGlobalOrigin(O, oid);
            //     break;
            // case OriginType::ORIG_GEP_OFF:
            //     Changed |= instrumentGepOffOrigin(O, oid);
            //     break;
            default:
                break;
        }


    }
    dbgs()<<ANS_CY<<"FuzzyPass"<<ANS_RST<<" ["<<ANS_CG<<"!"<<ANS_RST<<"] "<<origins.size()<<" origins instrumented"<<ANS_RST<<"\n";
    dbgs()<<ANS_CY<<"FuzzyPass"<<ANS_RST<<" ["<<ANS_CG<<"!"<<ANS_RST<<"] "<<block_inserted<<" block inserted"<<"\n";
    
    return Changed;
}

bool InstrumenterAA::instrumentEnumOrigin(Origin O){
    bool Changed = false;
    if(!O.get())return Changed;
    
    std::set<Value*> alias = isa<GlobalVariable>(O.get()) 
        ? getPointersAliasOfGlobal(O.get()) 
        : getPointersAlias(O.get());
    
    for(auto ins:alias){
        for(auto user:ins->users()){
            // errs()<<*user<<"\n";
            if(!isa<LoadInst>(user)&&!isa<StoreInst>(user))continue;
            D( DUMP_ORIGINS_INSTRU ,
            *out<<"\t\tused: "<<*user<<"\n"
            );
            // dbgs()<<"value: "<<*O.get()<<" >> "<<*use<<"\n";
            Instruction* I= dyn_cast<Instruction>(user);
            if(!I)continue;

            Value* what = isa<LoadInst>(user) ? user : I->getOperand(0);

#ifdef DUMP_VALUES
            std::string name = user->getName().str();
            std::string type_name = O.getDbgTypeInfo()->getName().str();

    #ifdef ORIGIN_MEMORY_PLACE
            // dbgs()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
            Value* ptr = isa<LoadInst>(user)  ? I->getOperand(0) :  I->getOperand(1);
            injectRTDumpEnum(I, type_name, name, what, ptr);
    #endif
    #ifndef ORIGIN_MEMORY_PLACE
            injectRTDumpEnum(I, type_name, name, what);
    #endif
#endif

#ifdef INJECT_INSTRUMENTATION
            injectEnumBlocks(I, what, O.getPossibleValues());
#endif
            Changed |= true;
        } 
    }
    return Changed;
}


//    ___                               ___                            _        
//   / __|_____ _____ _ _ __ _ __ _ ___|   \ _  _ _ __  _ __  ___ _ _ /_\  __ _ 
//  | (__/ _ \ V / -_) '_/ _` / _` / -_) |) | || | '  \| '_ \/ -_) '_/ _ \/ _` |
//   \___\___/\_/\___|_| \__,_\__, \___|___/ \_,_|_|_|_| .__/\___|_|/_/ \_\__,_|
//                            |___/                    |_|                      

bool CoverageDumperAA::insertInstrumentation(std::set<Origin> origins){
    bool Changed = false;
    D( DUMP_ORIGINS_INSTRU ,
    *out<<"origins "<<origins.size()<<"\n"
    );

    unsigned cori = 0;
    unsigned orilen = origins.size();
    for(auto O:origins){
        if(!O.get())continue;
        unsigned oid = shStatsPtr->getNewOrigID();
        switch(O.getType()){
            case OriginType::ORIG_ENUM:
                Changed |= instrumentEnumOrigin(O, oid);
                break;
            // Idea to expand this concept
            // case OriginType::ORIG_GLOBAL:
            //     Changed |= instrumentGlobalOrigin(O, oid);
            //     break;
            // case OriginType::ORIG_GEP_OFF:
            //     Changed |= instrumentGepOffOrigin(O, oid);
            //     break;
            default:
                break;
        }
    }
    dbgs()<<ANS_CY<<"FuzzyPass"<<ANS_RST<<" ["<<ANS_CG<<"!"<<ANS_RST<<"] "<<origins.size()<<" origins instrumented for coverage"<<ANS_RST<<"\n";    
    return Changed;
}

bool CoverageDumperAA::instrumentEnumOrigin(Origin O, unsigned oid){
    bool Changed = false;
    if(!O.get())return Changed;
    
    if(isa<GlobalVariable>(O.get())){
        shStatsPtr->addGlobalO();
    }else{
        shStatsPtr->addLocalO();
    }

    std::set<Value*> alias = isa<GlobalVariable>(O.get()) 
        ? getPointersAliasOfGlobal(O.get()) 
        : getPointersAlias(O.get());
    
    for(auto ins:alias){
        for(auto user:ins->users()){
            // errs()<<*user<<"\n";
            if(!isa<LoadInst>(user)&&!isa<StoreInst>(user))continue;
 
            Instruction* I= dyn_cast<Instruction>(user);
            if(!I)continue;
            Value* what = isa<LoadInst>(user) ? user : I->getOperand(0);

            std::string name = user->getName().str();            
            std::string type_name = O.getDbgTypeInfo()->getName().str();
            Value* ptr = isa<LoadInst>(user)  ? I->getOperand(0) :  I->getOperand(1);
            //injectRTDumpEnum(I, type_name, name, what);
            injectRTCovDumpEnum(I, type_name, what, ptr, oid);
            Changed |= true;
        } 
    }
    return Changed;
}


void CoverageDumperAA::injectRTCovDumpEnum(Instruction* where, std::string type_name, Value* what, Value* what_ptr, unsigned oid){
    if(!where || !what ) return;
    BasicBlock* bb = where->getParent();
    if(!bb)return;
    Instruction* instr = dyn_cast<Instruction>(where);
    llvm::IRBuilder<> IRB(bb);
    IRB.SetInsertPoint(instr->getNextNode());
    
    Value* ptr_dump = what_ptr;

    Type *T = what->getType();
    
    if(T->getTypeID()!=Type::PointerTyID && T->getTypeID()!=Type::IntegerTyID){
        errs()<<"Type ID not handled: "<<T->getTypeID()<<"\n";
        return;
    }

    // INFO! We dont need to dereference a pointer to an enum value
    // this because the compiler will do this automagically if the 
    // value stored by the pointers is used, so we need to track it
    // but we don't need to dereference it.
    if(T->getTypeID()==Type::PointerTyID){
        return;
    }

    if(T->getTypeID()==Type::PointerTyID && isa<LoadInst>(what)){
        Instruction* I = dyn_cast<Instruction>(what);
        ptr_dump = I->getOperand(0);
    }

    TypeSize BitsNum = T->getPrimitiveSizeInBits();

    if(BitsNum > 64) return;
    size_t SizeIndex = TypeSizeToSizeIndex(BitsNum);
    
    Value *TN = IRB.CreateGlobalStringPtr(type_name);

    auto fn_chosen = SizeIndex == 0 ?cov_enum_0:(SizeIndex == 1?cov_enum_1:(SizeIndex == 2?cov_enum_2:cov_enum_3));
   
    auto null_chosen = SizeIndex == 0 ?null_i8:    (SizeIndex == 1?null_i16:   (SizeIndex == 2?null_i32:   null_i64   ));

    Value* ptr = ptr_dump!=nullptr ? ptr_dump : null_chosen;

    const DebugLoc dbl = instr->getDebugLoc();
    unsigned line = (dbl)? dbl->getLine(): -1;

    ConstantInt * ori_id     = IRB.getInt32(oid);
    ConstantInt * cov_id     = IRB.getInt32(shStatsPtr->getNewCovID());
    ConstantInt * line_value = IRB.getInt32(line);

    auto CI = IRB.CreateCall(fn_chosen, ArrayRef<Value*>{TN,what,line_value,cov_id,ori_id});

    CI->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(*C, None));
    
    return;   
}

//   ___         _                          _           ___
//  |_ _|_ _  __| |_ _ _ _  _ _ __  ___ _ _| |_ ___ _ _| _ ) __ _ ___ ___
//   | || ' \(_-<  _| '_| || | '  \/ -_) ' \  _/ -_) '_| _ \/ _` (_-</ -_)
//  |___|_||_/__/\__|_|  \_,_|_|_|_\___|_||_\__\___|_| |___/\__,_/__/\___|
//

void DumpInstrumenterBase::injectRTDumpEnum(Instruction* where, std::string type_name, std::string name, Value* what, Value* what_ptr){
    if(!where || !what ) return;
    BasicBlock* bb = where->getParent();
    if(!bb)return;
    Instruction* instr = dyn_cast<Instruction>(where);
    llvm::IRBuilder<> IRB(bb);
    IRB.SetInsertPoint(instr->getNextNode());
    
    Value* ptr_dump = what_ptr;

    Type *T = what->getType();
    
    if(T->getTypeID()!=Type::PointerTyID && T->getTypeID()!=Type::IntegerTyID){
        errs()<<"Type ID not handled: "<<T->getTypeID()<<"\n";
        return;
    }

    // INFO! We dont need to dereference a pointer to an enum value
    // this because the compiler will do this automagically if the 
    // value stored by the pointers is used, so we need to track it
    // but we don't need to dereference it.
    if(T->getTypeID()==Type::PointerTyID){
        return;
    }

    if(T->getTypeID()==Type::PointerTyID && isa<LoadInst>(what)){
        Instruction* I = dyn_cast<Instruction>(what);
        ptr_dump = I->getOperand(0);
    }

    TypeSize BitsNum = T->getPrimitiveSizeInBits();

    if(BitsNum > 64) return;
    size_t SizeIndex = TypeSizeToSizeIndex(BitsNum);
    
    Value *N = IRB.CreateGlobalStringPtr(name);
    Value *TN = IRB.CreateGlobalStringPtr(type_name);

    auto fn_chosen = SizeIndex == 0 ?dump_enum_0:(SizeIndex == 1?dump_enum_1:(SizeIndex == 2?dump_enum_2:dump_enum_3));
    auto null_chosen = SizeIndex == 0 ?null_i8:    (SizeIndex == 1?null_i16:   (SizeIndex == 2?null_i32:   null_i64   ));

    Value* ptr = ptr_dump!=nullptr ? ptr_dump : null_chosen;

    auto CI = IRB.CreateCall(fn_chosen, ArrayRef<Value*>{TN,N, what, ptr});
    CI->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(*C, None));
    
    return;    
}

void DumpInstrumenterBase::injectRTDeclareEnum(Instruction* where, std::string type_name, std::string name){
    if(!where ) return;

    Instruction* instr = dyn_cast<Instruction>(where);

    llvm::IRBuilder<> IRB(where);

    Value *N = IRB.CreateGlobalStringPtr(name);
    Value *T = IRB.CreateGlobalStringPtr(type_name);

    auto CI = IRB.CreateCall(dumpEnumDeclFn, ArrayRef<Value*>{T,N});
    CI->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(*C, None));
}

void DumpInstrumenterBase::injectEnumBlocks(Instruction* where, Value* what, std::set<int> declaredValues){
    if(!where || !what ) return;
    if(isa<Constant>(what)) return;
    if(declaredValues.size() == 0) return;
    BasicBlock* bb = where->getParent();
    if(!bb)return;
    Instruction* instr = dyn_cast<Instruction>(where);
    llvm::IRBuilder<> IRB(bb);
    IRB.SetInsertPoint(instr->getNextNode());
    
    Type *T = what->getType();
    
    if(T->getTypeID()!=Type::PointerTyID && T->getTypeID()!=Type::IntegerTyID){
        errs()<<"Type ID not handled: "<<T->getTypeID()<<"\n";
        return;
    }
    
    // INFO! We dont need to dereference a pointer to an enum value
    // this because the compiler will do this automagically if the 
    // value stored by the pointers is used, so we need to track it
    // but we don't need to dereference it.
    if(T->getTypeID()==Type::PointerTyID){
        return;
    }

    TypeSize BitsNum = T->getPrimitiveSizeInBits();

    if(BitsNum > 64) return;
    
    int conterValueDummy = 1;
    for(int definedValue : declaredValues){
        ConstantInt* current_chk_value = IRB.getIntN(BitsNum , definedValue);
        Value* cmp = IRB.CreateICmpEQ(what, current_chk_value);

        Instruction *ThenTerm , *ElseTerm ;

        SplitBlockAndInsertIfThenElse(cmp, &*IRB.GetInsertPoint(), &ThenTerm, &ElseTerm);
        IRB.SetInsertPoint(ThenTerm);

        // auto CI = IRB.CreateCall(noop_function, {});
        // CI->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(*C, None));        
        incrementVolatile(&IRB, noop_volatile, conterValueDummy);
        conterValueDummy++;

        IRB.SetInsertPoint(ElseTerm);

    }
    
    incrementVolatile(&IRB, noop_volatile);
    // auto CI = IRB.CreateCall(noop_function, {});
    // CI->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(*C, None));

    block_inserted += declaredValues.size() + 1;
    return;    
}


inline void DumpInstrumenterBase::incrementVolatile(IRBuilderBase *IRB, GlobalValue* globalToIncrement, int incVal /*default value in relative hpp*/){
    LoadInst *loadNoopVolatile = IRB->CreateLoad(Int32Ty, globalToIncrement);
    loadNoopVolatile->setVolatile(true);
    Value *updatedNoopValue = IRB->CreateAdd(loadNoopVolatile, ConstantInt::get(Int32Ty, incVal));
    StoreInst *storeNoopVolatile = IRB->CreateStore(updatedNoopValue, globalToIncrement);
    storeNoopVolatile->setVolatile(true);
}

std::set<Value*> DumpInstrumenterBase::getPointersAlias(Value* val){
    std::set<Value*> pointer_alias = {};
    
    Instruction* instr = dyn_cast<Instruction>(val);
    if(!instr)return pointer_alias;

    BasicBlock* BB = instr->getParent();
    if(!BB)return pointer_alias;

    Function* F = BB->getParent();
    if(!F)return pointer_alias;

    AAResults &aa = FAM->getResult<AAManager>(*F);
    // Value *Obj = val->stripPointerCasts();
    std::set<Instruction*>ptrs_visited = {};

    pointer_alias.insert(val);
    ptrs_visited.insert(instr);

    for(auto &cursorI:instructions(*F)){
        if(cursorI.getType()->isPointerTy()){
            // dbgs()<<"pts\n";
            if(ptrs_visited.count(&cursorI)==0)continue;
            ptrs_visited.insert(&cursorI);

            auto res = aa.alias(instr, &cursorI);
            // if(res!=llvm::AliasResult::MustAlias  && res!=llvm::AliasResult::MayAlias)continue;
            if(res!=llvm::AliasResult::MustAlias)continue;

            pointer_alias.insert(&cursorI);
        }
    }
    
    return pointer_alias;
}

std::set<Value*> DumpInstrumenterBase::getPointersAliasOfGlobal(Value* val){
    std::set<Value*> pointer_alias = {};

    Instruction* instr = dyn_cast<Instruction>(val);
    if(!instr)return pointer_alias;
    
    // Value *Obj = val->stripPointerCasts();

    std::map<Function*, std::set<User*>> map_f_to_use = {};
    std::set<Function*> function_touched = {};

    for(auto U:val->users()){
        Instruction * tmp_i = dyn_cast<Instruction>(U);
        if(!tmp_i)continue;
        BasicBlock* BB = tmp_i->getParent();
        if(!BB)continue; 
        Function* F = BB->getParent();
        if(!F)continue;
        function_touched.insert(F);
        map_f_to_use[F].insert(U);
    }

    std::set<Instruction*>ptrs_visited = {};
    ptrs_visited.insert(instr);
    
    for(auto [F, setU]:map_f_to_use){
        AAResults &aa = FAM->getResult<AAManager>(*F);

        User* U = (User*) &*setU.begin();
        Instruction* instr = dyn_cast<Instruction>(U);
        for(auto &cursorI:instructions(*F)){
            if(!cursorI.getType()->isPointerTy())continue;
            if(ptrs_visited.count(&cursorI)==0)continue;
            ptrs_visited.insert(&cursorI);

            if(setU.count(&cursorI)!=0)continue;
            auto res = aa.alias(instr, &cursorI);
            // if(res!=llvm::AliasResult::MustAlias  && res!=llvm::AliasResult::MayAlias)continue;
            if(res!=llvm::AliasResult::MustAlias)continue;
            pointer_alias.insert(&cursorI);
        }
    }

    //include global in alias;
    pointer_alias.insert(val);
    
    return pointer_alias;
}
