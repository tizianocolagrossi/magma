#!/bin/bash
set -e

export DEBIAN_FRONTEND=noninteractive

apt-get update -y && apt-get upgrade -y && \
    apt-get install -y make build-essential git wget gnupg lsb-release software-properties-common cmake

#apt install -y lsb-release wget software-properties-common gnupg
# Install cmake

#clang++-13 -g -Wall -fPIC -shared dbg_type_info.cpp dbg_value_info.cpp dump_instrumenter.cpp fuzzy_pass.cpp instnamer_module.cpp main.cpp -o fuzzy-pass.so $(llvm-config-13 --cxxflags -ldflags --libs) -std=c++17 -I ../../include/

# Anything below llvm 13 is disabling good afl++ instrumentation features
# and would make a comparison of afl++ to other fuzzers pointless.
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
./llvm.sh 13
rm -f llvm.sh

apt-get -y install libclang-13-dev



#apt-get install -y libc++-13-dev libc++abi-13-dev

apt-get clean -y

