#include <cstdlib>
#include <new>  // for placement new
#include <iostream>
#include <sys/mman.h>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>

#include "common.hpp"
#include "managershmem/manager.hpp"

using namespace std;

SharedStats::SharedStats(){
    module_counter = 0;
    origin_counter = 0;
    origin_global_counter = 0;
    origin_local_counter = 0;
    id_cov_places = 0;
}

SharedStats::~SharedStats(){}

void SharedStats::printStats(){
    cout <<"Modules....."<<module_counter<<endl;
    cout <<"Origins....."<<origin_counter<<endl;
    cout <<" - globals.."<<origin_global_counter<<endl;
    cout <<" - locals..."<<origin_local_counter<<endl;
    cout <<"CovIdTotal.."<<id_cov_places<<endl;
}



volatile sig_atomic_t in_loop = 1;

void signalHandler(int signal) {
    in_loop = 0;
}

int main(){
    signal(SIGINT, signalHandler);

    const int SHM_SIZE = sizeof(SharedStats);

    // Allocate shared memory
    int fd = shm_open("/fuzzy_shstats", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHM_SIZE);
    void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    // construct SharedStats inside the shared memory
    SharedStats* shStatsPtr = new (ptr) SharedStats();

    while (in_loop) {
        sleep(1);
    }
    cout << "Terminating manager... "<< endl;

    shStatsPtr->printStats();
    // Destroy the object
    shStatsPtr->~SharedStats();
    
    // Unmap the shared memory
    munmap(ptr, SHM_SIZE);
    shm_unlink("/fuzzy_shstats");

    cout << "Manager terminated"<< endl;
    
    return 0;
}

