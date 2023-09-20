#include "pass/dbg_type_info.hpp"
    
#include "common.hpp"

using namespace llvm;

DbgTypeInfo::DbgTypeInfo(DIType* type){
    name = type->getName();
    if(name=="")name="not_available";
    sizeInBits = type->getSizeInBits();
    offset = type->getOffsetInBits();
    collectTypeTrace(type);
}

DbgTypeInfo::DbgTypeInfo(const DbgTypeInfo &I){
    name       = I.name;
    sizeInBits = I.sizeInBits;
    offset     = I.offset;
    type_trace = std::list<llvm::DIType*>(I.type_trace);
}

DbgTypeInfo::DbgTypeInfo(const DbgTypeInfo *I){
    name       = I->name;
    sizeInBits = I->sizeInBits;
    offset     = I->offset;
    type_trace = std::list<llvm::DIType*>(I->type_trace);
}

void DbgTypeInfo::dump(llvm::raw_ostream &OS) const{
      OS<<"TypeName: "<<ANS_CG<<name<<ANS_RST<<" "
              <<"facial: "<<dwarf::TagString(this->getFaceTTag())
              <<"\nactual: "<<ANS_CG<<dwarf::TagString(this->getActualTTag())<<ANS_RST<<" "
              <<"size: "<<sizeInBits<<"bit offset@"<<offset<<"\n";
}

void DbgTypeInfo::collectTypeTrace(llvm::DIType *in){
    // dbgs()<<"========================================NEW COLLECT=====================\n";
    type_trace.push_front(in);
    while(auto DT = dyn_cast<DIDerivedType>(type_trace.front())){
        DIType* base = DT->getBaseType();
        if(!base)return;
        type_trace.push_front(base);
    }
}