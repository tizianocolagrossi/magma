#pragma once

#include <cstdlib>
#include <new>  // for placement new
#include <iostream>
#include <sys/mman.h>
#include <atomic>


class SharedStats {
    
    std::atomic<int> module_counter;
    std::atomic<unsigned> origin_counter;
    std::atomic<int> origin_global_counter;
    std::atomic<int> origin_local_counter;
    std::atomic<unsigned> id_cov_places;

public:
    SharedStats();
    ~SharedStats();

    void addModule() {module_counter++;}
    // void addOrigin() {origin_counter++;}
    void addGlobalO(){origin_global_counter++;}
    void addLocalO() {origin_local_counter++;}

    // int  getOriginC(){return origin_counter.load();}
    int  getModuleC(){return module_counter.load();}
    unsigned  getNewCovID(){
        return id_cov_places.fetch_add(1, std::memory_order_relaxed) + 1;
    }
    unsigned  getNewOrigID(){
        return origin_counter.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    void printStats();
};
