#!/bin/bash
set -e

##
# Pre-requirements:
# - env FUZZER: path to fuzzer work dir
# - env TARGET: path to target work dir
# - env MAGMA: path to Magma support files
# - env OUT: path to directory where artifacts are stored
# - env CFLAGS and CXXFLAGS must be set to link against Magma instrumentation
##



export AFL_PATH="$FUZZER/repo/"
export CC="$FUZZER/repo/afl-clang-fast"
export CXX="$FUZZER/repo/afl-clang-fast++"
export AS="/usr/bin/llvm-as-13"
export AR="/usr/bin/llvm-ar-13"
export RANLIB="/usr/bin/llvm-ranlib-13"

export LIBS="$LIBS $FUZZER/repo/utils/aflpp_driver/libAFLDriver.a"

export CXXFLAGS="$CXXFLAGS -stdlib=libstdc++"
# Required to build php
export CXXFLAGS_REQUIRED=-stdlib=libstdc++


export CC=clang-13
export CXX=clang++-13

"$MAGMA/build.sh"

export LIBS="$LIBS $FUZZER/repo/utils/aflpp_driver/libAFLDriver.a"
export CC="$FUZZER/finder/build/src/finder"
export CXX="$FUZZER/finder/build/src/finder++"

export REALCC="$FUZZER/repo/afl-clang-fast"
export REALCXX="$FUZZER/repo/afl-clang-fast++"

export OUT="$OUT/afl"
export LDFLAGS="$LDFLAGS -L$OUT"

export AFL_LLVM_DICT2FILE="$OUT/afl++.dict"
export AFL_LLVM_DICT2FILE_NO_MAIN="1"


"$TARGET/build.sh"

# NOTE: We pass $OUT directly to the target build.sh script, since the artifact
#       itself is the fuzz target. In the case of Angora, we might need to
#       replace $OUT by $OUT/fast and $OUT/track, for instance.
