#!/bin/bash
set -e

##
# Pre-requirements:
# - env FUZZER: path to fuzzer work dir
##
echo "BUILDING AFLPlusPlus -------------------------------------------------------------------------"
if [ ! -d "$FUZZER/repo" ]; then
    echo "fetch.sh must be executed first."
    exit 1
fi

cd "$FUZZER/repo"
export CC=clang-13
export CXX=clang++-13
export LLVM_CONFIG=llvm-config-13
export AFL_NO_X86=1
export PYTHON_INCLUDE=/
make -j$(nproc) || exit 1
make -C utils/aflpp_driver || exit 1

mkdir -p "$OUT/afl" "$OUT/cmplog"

echo "BUILDING ENUMETRIC ---------------------------------------------------------------------------"


cd "$FUZZER/fuzzy-potato/lib/pass/"

clang++-13 -g -Wall -fPIC -shared dbg_type_info.cpp dbg_value_info.cpp dump_instrumenter.cpp \
    fuzzy_pass.cpp instnamer_module.cpp main.cpp -o libfuzzy-pass.so $(llvm-config-13 --cxxflags -ldflags --libs) \
    -std=c++17 -I "$FUZZER/fuzzy-potato/include/"

cp ./libfuzzy-pass.so "$FUZZER/repo/"