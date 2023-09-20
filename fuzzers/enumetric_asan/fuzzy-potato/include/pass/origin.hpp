#pragma once 

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include "pass/dbg_type_info.hpp"
#include <set>

using namespace llvm;

bool inline isInput(size_t x)   { return (bool) ( 1&x); }
bool inline isOutput(size_t x)  { return (bool) ( 2&x); }
bool inline isEnum(size_t x)    { return (bool) ( 4&x); }
bool inline isCmp(size_t x)     { return (bool) ( 8&x); }
bool inline isGepOff(size_t x)  { return (bool) (16&x); }

//Enum with different types of functions.
enum OriginType {
    ORIG_NONVALID =  0,
    ORIG_INPUT   =   1,
    ORIG_OUTPUT  =   2,
    ORIG_ENUM    =   4,
    ORIG_CMP     =   8,
    ORIG_GEP_OFF =  16,
    ORIG_GLOBAL  =  32,
    ORIG_ALLFUN  =  64,
};

class Origin{
    Value* val = nullptr;
    std::list<DbgTypeInfo> type_info = {};
    std::set<int> possible_values = {};
    OriginType type = OriginType::ORIG_NONVALID;
    int operandIndex = -1;
public:
    Origin(){};
    
    Origin(Value* arg, OriginType in_type, DbgTypeInfo dbg_info, std::set<int> DefinedValues){
        val=arg;
        type_info.push_front(dbg_info);
        possible_values = DefinedValues;
        type = in_type;
    };

    Origin(Value* arg, OriginType in_type, int index){
        val=arg;
        type = in_type;
        operandIndex = index;
    };

    Origin(const Origin &O){
        val = O.val;
        type = O.type;
        type_info = O.type_info;
        possible_values = O.possible_values;
    }
    
    Value* get(){return val;}
    OriginType getType(){return type;}
    DbgTypeInfo* getDbgTypeInfo(){
        if(type_info.size()==0)
            return nullptr;
        return &type_info.front();}

    int getOperandIndex(){
        if(type==OriginType::ORIG_ALLFUN){
            return operandIndex;
        }else{
            //this can be removes since is initizliezed
            return -1;
        }
    }

    std::set<int> getPossibleValues(){return possible_values;}

    friend bool operator== (Origin &lhs, Origin &rhs){
        bool eq = true;
        eq &= lhs.val==rhs.val;
        eq &= lhs.type==rhs.type;
        return eq;
    }
    friend bool operator== (const Origin &lhs, const Origin &rhs){
        bool eq = true;
        eq &= lhs.val==rhs.val;
        eq &= lhs.type==rhs.type;
        return eq;
    }
    friend bool operator!=(Origin &lhs, Origin &rhs){
        return !(lhs==rhs);
    }
    friend bool operator!=(const Origin &lhs, const Origin &rhs){
        return !(lhs==rhs);
    }

    friend bool operator< (Origin &lhs, Origin &rhs){
        return (lhs.val+lhs.type*31)<(rhs.val+rhs.type*31);
    };
    friend bool operator< (const Origin &lhs, const Origin &rhs){
        return (lhs.val+lhs.type*31)<(rhs.val+rhs.type*31);
    };

    friend bool operator> (Origin &lhs, Origin &rhs){
        return (lhs.val+lhs.type*31)>(rhs.val+rhs.type*31);
    };
    friend bool operator> (const Origin &lhs, const Origin &rhs){
        return (lhs.val+lhs.type*31)>(rhs.val+rhs.type*31);
    };
    friend bool operator<= (Origin &lhs, Origin &rhs){
        return !(lhs>rhs);
    };
    friend bool operator<= (const Origin &lhs, const Origin &rhs){
        return !(lhs>rhs);
    };
    friend bool operator>= (Origin &lhs, Origin &rhs){
        return !(lhs<rhs);
    };
    friend bool operator>= (const Origin &lhs, const Origin &rhs){
        return !(lhs<rhs);
    };
};