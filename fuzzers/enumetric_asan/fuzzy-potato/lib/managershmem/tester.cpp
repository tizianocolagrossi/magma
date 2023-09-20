#include <cstdlib>
#include <new>  // for placement new
#include <iostream>
#include <sys/mman.h>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>

#include "managershmem/manager.hpp"

using namespace std;

SharedStats::SharedStats(){
    cout <<"SharedStats contructed"<<endl;
}

SharedStats::~SharedStats(){
    cout <<"SharedStats destructed"<<endl;
}

void SharedStats::printStats(){
    cout <<"Modules "<<module_counter<<endl;
    cout <<"Origins "<<origin_counter<<endl;
}



volatile sig_atomic_t in_loop = 1;

void signalHandler(int signal) {
    cout << "Received signal " << signal << endl;
    cout << "Terminating manager... "<< endl;
    in_loop = 0;
}

int main(){
    signal(SIGINT, signalHandler);

    const int SHM_SIZE = sizeof(SharedStats);

    // Allocate shared memory
    int fd = shm_open("/fuzzy_shstats", O_RDWR, 0666);
    ftruncate(fd, SHM_SIZE);
    void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    // construct SharedStats inside the shared memory
    SharedStats* shStatsPtr = (SharedStats*) ptr;

    shStatsPtr->addModule();

    while (in_loop) {
        sleep(1);
    }


    
    // Unmap the shared memory
    munmap(ptr, SHM_SIZE);

    
    return 0;
}

