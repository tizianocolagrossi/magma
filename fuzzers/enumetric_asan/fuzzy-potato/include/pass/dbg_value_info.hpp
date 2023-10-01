#pragma once

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm//IR/CFG.h"
#include "llvm/ADT/Twine.h"
#include "llvm/ADT/SmallVector.h"

#include <map>
#include <set>
#include <list>

#include "pass/dbg_type_info.hpp"


class DbgValueInfo{
private:
    bool is_a_copy = false;
    DbgTypeInfo *typeInfo = nullptr;
    llvm::Value* val = nullptr;

public:
    DbgValueInfo(llvm::Value* value_declared, DIVariable* di_variable_declared);
    DbgValueInfo(llvm::GlobalVariable *GV, DIGlobalVariable* di_variable_declared);
    DbgValueInfo(llvm::GetElementPtrInst *I, DbgTypeInfo tyinfo);
    ~DbgValueInfo(){if(typeInfo)delete typeInfo;}

    Value* get(){return val;}
    DbgTypeInfo* getTypeInfo(){return typeInfo;};
    llvm::dwarf::Tag getActualTTag(){
        if(!typeInfo)return dwarf::Tag::DW_TAG_null;
        return typeInfo->getActualTTag();
    };

    DbgValueInfo(const DbgValueInfo &I){
        val       = I.val;
        typeInfo  = new DbgTypeInfo(*I.typeInfo);
        is_a_copy = true;
    };

    friend bool operator== (DbgValueInfo &lhs, DbgValueInfo &rhs){
        bool eq = true;
        eq &= lhs.val==rhs.val;

        return eq;
    }
    friend bool operator== (const DbgValueInfo &lhs, const DbgValueInfo &rhs){
        bool eq = true;
        eq &= lhs.val==rhs.val;

        return eq;
    }

    friend bool operator!=(DbgValueInfo &lhs, DbgValueInfo &rhs){
        return !(lhs==rhs);
    }
    friend bool operator!=(const DbgValueInfo &lhs, const DbgValueInfo &rhs){
        return !(lhs==rhs);

    }
    
    void dump(llvm::raw_ostream &OS);

};