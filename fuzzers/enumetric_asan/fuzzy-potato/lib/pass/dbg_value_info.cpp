#include "pass/dbg_value_info.hpp"
#include "common.hpp"

using namespace llvm;

DbgValueInfo::DbgValueInfo(CallBase *callBaseDeclare){
    if(!callBaseDeclare){throw std::invalid_argument("must be not null");}
    if(!callBaseDeclare->getCalledFunction()){throw std::invalid_argument("callbase hot has a function");}
    
    DbgVariableIntrinsic* call = dyn_cast<DbgVariableIntrinsic>(callBaseDeclare);
    if(!call){throw std::invalid_argument("I must be a DbgVariableIntrinsic");}
    
    StringRef name = callBaseDeclare->getCalledFunction()->getName();
    if(!name.endswith("declare")){throw std::invalid_argument("I must be a declare");}

    auto declaration_location = callBaseDeclare->getDebugLoc();

    DIVariable* di_variable_declared = call->getVariable();
    if(!di_variable_declared){throw std::invalid_argument("No variable associated with dbg.declare");}
    
    Value * value_declared = call->getVariableLocationOp(0);
    if(!value_declared){throw std::invalid_argument("No value associated with dbg.declare");}

    DIScope* scope_of_declaration = di_variable_declared->getScope();

    line      = (declaration_location)? declaration_location->getLine(): 0;
    name      = di_variable_declared->getName();
    val       = value_declared;
    directory = (scope_of_declaration)? scope_of_declaration->getDirectory() : "";
    file      = (scope_of_declaration)? scope_of_declaration->getFilename()  : "";
    typeInfo  = new DbgTypeInfo(di_variable_declared->getType());

    finalize();
};

DbgValueInfo::DbgValueInfo(GlobalVariable *GV){
    if(!GV){throw std::invalid_argument("GV must be not null");}
    
    bool created = false;

    SmallVector<DIGlobalVariableExpression *, 1> GVEs;
    GV->getDebugInfo(GVEs);
    if(GVEs.size()==0)throw std::invalid_argument("GVEs size == 0");
    for (DIGlobalVariableExpression *GVE : GVEs){
        if(GVE){

            DIGlobalVariable* di_variable_declared = GVE->getVariable();
            if(!di_variable_declared){throw std::invalid_argument("No variable in GVE");}
   
            DIScope* scope_of_declaration = di_variable_declared->getScope();
   

            line      = di_variable_declared->getLine();
            name      = di_variable_declared->getName();
            val       = GV;
            directory = (scope_of_declaration)? scope_of_declaration->getDirectory() : "";
            file      = (scope_of_declaration)? scope_of_declaration->getFilename()  : "";
            typeInfo  = new DbgTypeInfo(di_variable_declared->getType());


            finalize();

            created = true;

            break;
        }
    }
    
    if(!created){throw std::invalid_argument("there is no DIGlobalVariableExpression");}


};

DbgValueInfo::DbgValueInfo(GetElementPtrInst *I, DbgTypeInfo tyinfo){
    if(!I){throw std::invalid_argument("I must be not null");}

    Value* V = dyn_cast<Value>(I);
    if(!V){throw std::invalid_argument("V must be not null");}

    DILocation* location = I->getDebugLoc();

    Function* F = I->getParent()->getParent();
    if(!F){throw std::invalid_argument("No function!");}
    DISubprogram* info_subprogram = F->getSubprogram();
    DIScope* scope_of_declaration = (info_subprogram)?info_subprogram->getScope():nullptr;

    line      = (location) ? location->getLine(): 0;
    name      = V->getName();
    val       = V;
    directory = (scope_of_declaration)? scope_of_declaration->getDirectory() : "";
    file      = (scope_of_declaration)? scope_of_declaration->getFilename()  : "";
    typeInfo  = new DbgTypeInfo(tyinfo);

    finalize();
};

void DbgValueInfo::dump(raw_ostream &OS){
    if(isa<GlobalVariable>(val)){
        OS<<ANS_BGG<<" GLOBAL "<<ANS_RST<<"\n";
    }else{
        OS<<ANS_BGM<<" LOCAL  "<<ANS_RST<<"\n";
    }
    OS<<"Name: "<<name<<" line@"<<line<<"\n";//":"<<col<<"\n";
    if(typeInfo){
        OS<<"Tag "<<ANS_BGB<<"(ACTUAL)"<<ANS_RST<<" "<<dwarf::TagString(typeInfo->getActualTTag())<<"\n";
        OS<<"Tag "<<ANS_BGR<<"(FACIAL)"<<ANS_RST<<" "<<dwarf::TagString(typeInfo->getFaceTTag())<<"\n";
    }
    OS<<"Defined with: "<<*val<<"\n";
    OS<<"Inside: "<<directory<<"/"<<file<<"\n";
}