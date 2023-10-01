#include "pass/dbg_value_info.hpp"
#include "common.hpp"

using namespace llvm;

DbgValueInfo::DbgValueInfo(Value* value_declared, DIVariable* di_variable_declared){

    val       = value_declared;
    typeInfo  = new DbgTypeInfo(di_variable_declared->getType());

};

DbgValueInfo::DbgValueInfo(GlobalVariable *GV, DIGlobalVariable* di_variable_declared){    

    val       = GV;
    typeInfo  = new DbgTypeInfo(di_variable_declared->getType());

};

DbgValueInfo::DbgValueInfo(GetElementPtrInst *I, DbgTypeInfo tyinfo){

    Value* V = dyn_cast<Value>(I);

    val       = V;
    typeInfo  = new DbgTypeInfo(tyinfo);

};

void DbgValueInfo::dump(raw_ostream &OS){
    if(isa<GlobalVariable>(val)){
        OS<<ANS_BGG<<" GLOBAL "<<ANS_RST<<"\n";
    }else{
        OS<<ANS_BGM<<" LOCAL  "<<ANS_RST<<"\n";
    }
    // OS<<"Name: "<<name<<" line@"<<line<<"\n";//":"<<col<<"\n";
    // if(typeInfo){
    //     OS<<"Tag "<<ANS_BGB<<"(ACTUAL)"<<ANS_RST<<" "<<dwarf::TagString(typeInfo->getActualTTag())<<"\n";
    //     OS<<"Tag "<<ANS_BGR<<"(FACIAL)"<<ANS_RST<<" "<<dwarf::TagString(typeInfo->getFaceTTag())<<"\n";
    // }
    OS<<"Defined with: "<<*val<<"\n";
    // OS<<"Inside: "<<directory<<"/"<<file<<"\n";
}