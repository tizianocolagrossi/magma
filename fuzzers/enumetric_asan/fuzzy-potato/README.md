# fuzzy-potato

## How to Build
required
```
sudo apt install unzip cmake clang-13
git submodule init
git pull --recurse-submodules
```

In order to build llvm first install clang-13 and then
clone llvm-project and go to tag llvmorg-13.0.0
```
apt install clang-13
git clone https://github.com/llvm/llvm-project.git
git checkout tags/llvmorg-13.0.0
```

In order to build SVF 
```
cd SVF
LLVM_DIR=$(llvm-config-13 --libdir) CXX=clang++-13 source ./build.sh
```
this will setup also the following env variables
```
SVF_DIR=xxx/fuzzy-potato/SVF
LLVM_DIR=/usr/lib/llvm-13/lib
Z3_DIR=xxx/fuzzy-potato/SVF/z3.obj
```

In order to build AFLplusplus

Add this inside afl-cc.c after the line 
```c
if (compiler_mode == LLVM || compiler_mode == LTO) {
    cc_params[cc_par_cnt++] = "-Wno-unused-command-line-argument";
```

```c
    if (getenv("FUZZY_PASS")) {

#if LLVM_MAJOR >= 13                                /* use new pass manager */
  #if LLVM_MAJOR < 16
      cc_params[cc_par_cnt++] = "-fexperimental-new-pass-manager";
  #endif
      cc_params[cc_par_cnt++] =
          alloc_printf("-fpass-plugin=%s/libfuzzy-pass.so", obj_path);
#else
      WARNF(
            "FUZZY_PASS need at least llvm v13 ");
#endif

    }
```


```
cd AFLplusplus
sudo apt-get install -y build-essential python3-dev automake cmake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools cargo libgtk-3-dev
sudo apt-get install -y gcc-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-plugin-dev libstdc++-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-dev
LLVM_CONFIG=llvm-config-13 make source-only
sudo make install
```

- openssl  (openssl-3.0)
- harfbuzz (2.9.0)
- libxml2  (2.9)
- libpcap  (libpcap-1.10)
- h2o      (v2.2.4)
- libhevc  (v.1.1.0)
- bloaty   (main)
- muparser (v2.3.2)