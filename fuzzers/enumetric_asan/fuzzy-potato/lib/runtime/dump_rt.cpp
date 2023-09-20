#include <cstdio>
#include <mutex>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "runtime/dump_rt.hpp"

#include <unistd.h>
#include <cstdio>
#include <atomic>
#include <sys/types.h>

using namespace std;

static mutex dump_mutex;
bool multiple_outs = false;

namespace __potato_dump{
    FILE* dtrace_out = NULL;
    std::string opened_file = "";
    std::atomic<unsigned long long> ctr = 0;

    // uint8_t noop_counter = 0;

    void destroy() {
      dump_mutex.lock();
      if (dtrace_out) {
          fclose(dtrace_out);
          dtrace_out = NULL;
      }
      dump_mutex.unlock();
    }

    __attribute__((constructor, no_sanitize("address", "memory"))) void init() {
      if(getenv("POTATO_OUT_FILE_4RUN")){
        multiple_outs = true;
      }else{
        multiple_outs = false;
      }

      if (getenv("POTATO_OUT_FILE")) {
          
        char* path = getenv("POTATO_OUT_FILE");
        opened_file = path;
        if(getenv("APP")){
          dtrace_out = fopen(path, "a+");
        }else{
          dtrace_out = fopen(path, "w");
        }
          
      } else{
        opened_file = "none";
        dtrace_out = stderr;
      }
    atexit(destroy);
    }

    __attribute__((no_sanitize("address", "memory"))) void update_fout(){
        if(getenv("POTATO_OUT_FILE_4RUN")){
          pid_t pid = getpid();
          pid_t tid = gettid();
          char* path = getenv("POTATO_OUT_FILE");
          std::string final_path = path + to_string(pid)+"_"+to_string(tid);
          
          if(final_path == opened_file)return;

          dump_mutex.lock();
          if (dtrace_out) {
              fclose(dtrace_out);
              dtrace_out = NULL;
          }

          opened_file = final_path;
          dtrace_out = fopen(final_path.c_str(), "a");
          
          dump_mutex.unlock();
        }
    }
}

using namespace __potato_dump;

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_lock() {
  dump_mutex.lock();
}
extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_unlock() {
  dump_mutex.unlock();
}

// extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enter_prologue(){
//   update_fout();
//   if (dtrace_out) fprintf(dtrace_out, "[START]\n");
// }

// extern "C" __attribute__((no_sanitize("address", "memory"))) void   __potato_dump_exit_prologue(){
//   update_fout();
//   if (dtrace_out) fprintf(dtrace_out, "[END]\n");
// }

// extern "C" __attribute__((no_sanitize("address", "memory"))) void  __potato_noop(){
//   noop_counter++;
// }

// [DECL] [TYPE] option [NAME] i3
extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_declaration_enum(const char* type_name , const char* name ) {
  update_fout();
  if (dtrace_out) fprintf(dtrace_out, "[DECL] [TYPE] %s [NAME] %s\n", type_name, name);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum(const char* type_name , const char* name, int32_t value) {
  update_fout();
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %u\n", type_name, name, value);
}


extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_i8(const char* type_name , const char* name, int8_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 0);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %d\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_i16(const char* type_name , const char* name, int16_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 1);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %d\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_i32(const char* type_name , const char* name, int32_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 2);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %d\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_i64(const char* type_name , const char* name, int64_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, value, ptr, 3);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %ld\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_u8(const char* type_name , const char* name, uint8_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 0);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %u\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_u16(const char* type_name , const char* name, uint16_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 1);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %u\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_u32(const char* type_name , const char* name, uint32_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, (uint64_t)(value), ptr, 2);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %u\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_enum_u64(const char* type_name , const char* name, uint64_t value, uintptr_t ptr) {
  update_fout();
  if(ptr){
    __potato_dump_origin_place(type_name,name, value, ptr, 3);
    return;
  }
#ifdef MUTEX_ON
  lock_guard<mutex> lock(dump_mutex);
#endif
  if (dtrace_out) fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu\n", type_name, name, value);
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_dump_origin_place(const char* type_name , const char* name, uint64_t value, uintptr_t addr, int size){
  
  std::ifstream maps("/proc/self/maps");
  std::string line;

  std::list<std::pair<uintptr_t, uintptr_t>> stacks = {};
  std::list<std::pair<uintptr_t, uintptr_t>> heaps = {};
  
  while (std::getline(maps, line)) {
      std::size_t pos = line.find("-");

      if (pos == std::string::npos) {
          continue;
      }

      uintptr_t start = std::stoul(line.substr(0, pos), nullptr, 16);
      uintptr_t end = std::stoul(line.substr(pos + 1), nullptr, 16);

      if (line.find("[stack]") != std::string::npos) {
          stacks.push_front(std::make_pair(start, end));
      } else if (line.find("[heap]") != std::string::npos) {
          heaps.push_front(std::make_pair(start, end));
      }
  }
  std::string match = "[MATCH]"; 
  std::string nomatch = "[NO-MATCH]"; 
  
  int8_t*  i8ptr  = (int8_t*)  addr;
  int16_t* i16ptr = (int16_t*) addr;
  int32_t* i32ptr = (int32_t*) addr;
  int64_t* i64ptr = (int64_t*) addr;

  uint8_t*  u8ptr  = (uint8_t*)  addr;
  uint16_t* u16ptr = (uint16_t*) addr;
  uint32_t* u32ptr = (uint32_t*) addr;
  uint64_t* u64ptr = (uint64_t*) addr;

  std::string is_match = "";

  // if(*i8ptr==value || *i16ptr==value || *i32ptr==value || *i64ptr==value || *u8ptr==value || *u16ptr==value || *u32ptr==value || *u64ptr==value ){
  //   is_match = match;
  // }else{
  //   is_match = nomatch+" "+to_string(*u8ptr)+"_"+to_string(*i8ptr)+"_"+to_string(*u16ptr)+"_"+to_string(*i16ptr);
  // }

  switch(size){
    case 0:
      if(*i8ptr==value || *u8ptr==value){
        is_match = match;
      }else{
        is_match = nomatch+" 8 "+to_string(*u8ptr)+"_"+to_string(*i8ptr);
      }
      break;
    case 1:
      if(*i16ptr==value || *u16ptr==value){
        is_match = match;
      }else{
        is_match = nomatch+" 16 "+to_string(*u16ptr)+"_"+to_string(*i16ptr);
      }
      break;
    case 2:
      if(*i32ptr==value || *u32ptr==value){
        is_match = match;
      }else{
        is_match = nomatch+" 32 "+to_string(*u32ptr)+"_"+to_string(*i32ptr);
      }
      break;
    case 3:
      if(*i64ptr==value || *u64ptr==value){
        is_match = match;
      }else{
        is_match = nomatch+" 64 "+to_string(*u64ptr)+"_"+to_string(*i64ptr);
      }
      break;
    default:
      is_match = "[SIZE_NOT_VALID]";
      break;
  }
  
  lock_guard<mutex> lock(dump_mutex);

  for(auto h_p:heaps){
    // std::cout<<"[HEAP] 0x" << std::hex << h_p.first << " - 0x" << h_p.second << std::endl;
    if(addr<=h_p.second && addr>=h_p.first){
      
      if(multiple_outs){
        fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [HEAP] %s [#] %llu\n", type_name, name, value, is_match.c_str(), ctr++);
      }else{
        fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [HEAP] %s\n", type_name, name, value, is_match.c_str());
      }
      return;
    }
  }
  for(auto s_p:stacks){
    // std::cout<<"[STACK] 0x" << std::hex << s_p.first << " - 0x" << s_p.second << std::endl;
    if(addr<=s_p.second && addr>=s_p.first){
      
      if(multiple_outs){
        fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [STACK] %s [#] %llu\n", type_name, name, value, is_match.c_str(), ctr++);
      }else{
        fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [STACK] %s\n", type_name, name, value, is_match.c_str());
      }
      return;
    }
  }
  
  if(multiple_outs){
    fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [GLOBAL] %s [#] %llu\n", type_name, name, value, is_match.c_str(), ctr++);
  }else{
    fprintf(dtrace_out, "[USE] [TYPE] %s [NAME] %s [VALUE] %lu [GLOBAL] %s\n", type_name, name, value, is_match.c_str());
  }
  
  // the lock will be automatically released when the function returns
  return;
}

extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_cov_enum_i8 (const char* type_name , int8_t  value, int32_t line, uint32_t cov_id, uint32_t ori_id){
  fprintf(dtrace_out, "%s,%hhd,%d,%u,%u\n",type_name,value,line,cov_id, ori_id);
}
extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_cov_enum_i16(const char* type_name , int16_t value, int32_t line, uint32_t cov_id, uint32_t ori_id){
  fprintf(dtrace_out, "%s,%hd,%d,%u,%u\n",type_name,value,line,cov_id, ori_id);
}
extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_cov_enum_i32(const char* type_name , int32_t value, int32_t line, uint32_t cov_id, uint32_t ori_id){
  fprintf(dtrace_out, "%s,%d,%d,%u,%u\n",type_name,value,line,cov_id, ori_id);
}
extern "C" __attribute__((no_sanitize("address", "memory"))) void __potato_cov_enum_i64(const char* type_name , int64_t value, int32_t line, uint32_t cov_id, uint32_t ori_id){
  fprintf(dtrace_out, "%s,%ld,%d,%u,%u\n",type_name,value,line,cov_id, ori_id);
}

