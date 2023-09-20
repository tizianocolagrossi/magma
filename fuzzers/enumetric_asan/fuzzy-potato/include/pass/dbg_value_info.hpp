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
    unsigned line;
    //unsigned col;
    DbgTypeInfo *typeInfo = nullptr;
    llvm::StringRef name = "";
    llvm::Value* val = nullptr;
    llvm::StringRef directory = "";
    llvm::StringRef file = "";

    void finalize(){
        if(directory.startswith("./")){
            directory = directory.substr(2);
        }
        if(file.startswith("./")){
            file = file.substr(2);
            
        }
    };

public:
    DbgValueInfo(llvm::CallBase *callBaseDeclare);
    DbgValueInfo(llvm::GlobalVariable *GV);
    DbgValueInfo(llvm::GetElementPtrInst *I, DbgTypeInfo tyinfo);
    ~DbgValueInfo(){if(typeInfo)delete typeInfo;}

    Value* get(){return val;}
    llvm::StringRef getDir(){return directory;};
    llvm::StringRef getFile(){return file;};
    unsigned  getLine(){return line;};
    DbgTypeInfo* getTypeInfo(){return typeInfo;};
    llvm::dwarf::Tag getActualTTag(){
        if(!typeInfo)return dwarf::Tag::DW_TAG_null;
        return typeInfo->getActualTTag();
    };

    DbgValueInfo(const DbgValueInfo &I){
        line      = I.line;
        name      = I.name;
        val       = I.val;
        directory = I.directory;
        file      = I.file;
        typeInfo  = new DbgTypeInfo(*I.typeInfo);
        is_a_copy = true;
    };

    friend bool operator== (DbgValueInfo &lhs, DbgValueInfo &rhs){
        bool eq = true;
        eq &= lhs.name==rhs.name;
        eq &= lhs.line==rhs.line;
        eq &= lhs.directory==rhs.directory;
        eq &= lhs.file==rhs.file;
        eq &= lhs.val==rhs.val;

        return eq;
    }
    friend bool operator== (const DbgValueInfo &lhs, const DbgValueInfo &rhs){
        bool eq = true;
        eq &= lhs.name==rhs.name;
        eq &= lhs.line==rhs.line;
        eq &= lhs.directory==rhs.directory;
        eq &= lhs.file==rhs.file;
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