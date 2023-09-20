#pragma once

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/DebugInfo.h"


#include <list>

using namespace llvm;

class DbgTypeInfo{
private:
  llvm::StringRef name;
  std::list<llvm::DIType*> type_trace = {};
  uint64_t sizeInBits = 0;
  uint64_t offset = 0;

  void collectTypeTrace(llvm::DIType *in);

public:
  DbgTypeInfo(DIType* type);
  DbgTypeInfo(const DbgTypeInfo &I);
  DbgTypeInfo(const DbgTypeInfo *I);


  dwarf::Tag getActualTTag()const{ return type_trace.front()->getTag();}
  DIType* getActualType()const{ return type_trace.front();}
  dwarf::Tag getFaceTTag()const{ return type_trace.back()->getTag();}
  DIType* getFaceType()const{ return type_trace.back();}
  llvm::StringRef getName()const{ return name;}
  uint64_t getSize()const {return sizeInBits;}
  uint64_t getOffset()const {return offset;}


/// Comparators

    friend bool operator== (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
        bool eq = true;
        eq &= lhs.name==rhs.name;
        eq &= lhs.sizeInBits==rhs.sizeInBits;
        eq &= lhs.offset==rhs.offset;
        
        if(lhs.type_trace.size()!=rhs.type_trace.size())
          return false;
        
        auto lhs_it = lhs.type_trace.begin();
        auto rhs_it = rhs.type_trace.begin();

        while(lhs_it != lhs.type_trace.end() 
           && rhs_it != rhs.type_trace.end() ){
          
          llvm::DIType* lhs_ty = *lhs_it;
          llvm::DIType* rhs_ty = *rhs_it;
          if(lhs_ty->getTag()!=rhs_ty->getTag())
            return false;
          
          lhs_it++;
          rhs_it++;
        }

        return eq;
    };

    friend bool operator== (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
        bool eq = true;
        eq &= lhs.name==rhs.name;
        eq &= lhs.sizeInBits==rhs.sizeInBits;
        eq &= lhs.offset==rhs.offset;
        
        if(lhs.type_trace.size()!=rhs.type_trace.size())
          return false;
        
        auto lhs_it = lhs.type_trace.begin();
        auto rhs_it = rhs.type_trace.begin();

        while(lhs_it != lhs.type_trace.end() 
           && rhs_it != rhs.type_trace.end() ){
          
          llvm::DIType* lhs_ty = *lhs_it;
          llvm::DIType* rhs_ty = *rhs_it;
          if(lhs_ty->getTag()!=rhs_ty->getTag())
            return false;
          
          lhs_it++;
          rhs_it++;
        }

        return eq;
    };

    friend bool operator!= (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
      bool tmp = lhs==rhs;
      return !tmp;
    }
    
    friend bool operator!= (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
      bool tmp = lhs==rhs;
      return !tmp;
    }
    
    // use murmurhash
    friend bool operator< (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
        bool eq = true;
        unsigned long lns = std::hash<std::string>{}(lhs.name.str());
        unsigned long rns = std::hash<std::string>{}(rhs.name.str());
        dwarf::Tag tlhs = lhs.type_trace.front()->getTag();
        dwarf::Tag trhs = lhs.type_trace.front()->getTag(); 
        return (lns+(lhs.offset*7)+(lhs.sizeInBits*11)+(tlhs*31))<(rns+(rhs.offset*7)+(rhs.sizeInBits*11)+(trhs*31));
    };

    friend bool operator< (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
        bool eq = true;
        unsigned long lns = std::hash<std::string>{}(lhs.name.str());
        unsigned long rns = std::hash<std::string>{}(rhs.name.str());
        dwarf::Tag tlhs = lhs.type_trace.front()->getTag();
        dwarf::Tag trhs = lhs.type_trace.front()->getTag(); 
        return (lns+(lhs.offset*7)+(lhs.sizeInBits*11)+(tlhs*31))<(rns+(rhs.offset*7)+(rhs.sizeInBits*11)+(trhs*31));
    };

    friend bool operator> (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
        bool eq = true;
        unsigned long lns = std::hash<std::string>{}(lhs.name.str());
        unsigned long rns = std::hash<std::string>{}(rhs.name.str());
        dwarf::Tag tlhs = lhs.type_trace.front()->getTag();
        dwarf::Tag trhs = lhs.type_trace.front()->getTag(); 
        return (lns+(lhs.offset*7)+(lhs.sizeInBits*11)+(tlhs*31))>(rns+(rhs.offset*7)+(rhs.sizeInBits*11)+(trhs*31));
    };

    friend bool operator> (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
        bool eq = true;
        unsigned long lns = std::hash<std::string>{}(lhs.name.str());
        unsigned long rns = std::hash<std::string>{}(rhs.name.str());
        dwarf::Tag tlhs = lhs.type_trace.front()->getTag();
        dwarf::Tag trhs = lhs.type_trace.front()->getTag(); 
        return (lns+(lhs.offset*7)+(lhs.sizeInBits*11)+(tlhs*31))>(rns+(rhs.offset*7)+(rhs.sizeInBits*11)+(trhs*31));
    };

    friend bool operator>= (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
        return !(lhs<rhs);
    };

    friend bool operator>= (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
        return !(lhs<rhs);
    };

    friend bool operator<= (DbgTypeInfo &lhs, DbgTypeInfo &rhs){
        return !(lhs>rhs);       
    };

    friend bool operator<= (const DbgTypeInfo &lhs, const DbgTypeInfo &rhs){
        return !(lhs>rhs);         
    };

    void dump(llvm::raw_ostream &OS) const;    
};