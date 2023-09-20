cmake_minimum_required(VERSION 3.10.2)
project(potato)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

#set(CLANG_INCLUDE_DIRS "/home/tiziano/Documents/llvm-project/clang/include")
#set(CLANG_LIBS clang)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/)

link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(lib)
