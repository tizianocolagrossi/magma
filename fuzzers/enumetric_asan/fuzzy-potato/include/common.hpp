#pragma once

#define DEBUG_PRINT
#define COLORLESS

//#define OUT_MULTIPLE_FILES
#define OUT_ON_FILE

//#define DUMP_VALUES                
#define INJECT_INSTRUMENTATION    
#define DUMP_MODULE_NAME          0
#define DUMP_ALLTYPE_MAP          0
#define DUMP_ENUMS_IN_TYPE_MAP    1 // 1
#define DUMP_COST_VALUE_MAP       0
#define DUMP_ORIGINS_INSTRU       0

// scan for origin memory place 
#define ORIGIN_MEMORY_PLACE
// insert origin id in dump
#define USE_ORIGIN_ID_IN_DUMP

// choose what kind value mus be instrumented
#define INSTR_ENUMS
// #define INSTR_GLOBALS
// #define INSTR_GEP_OFF



#ifdef DEBUG_PRINT
#define DP(type, x) if(type){DUMPPOS() x;}
#define D(type, x)  if(type){x;}
#else
#define DP(x)
#define D(x)
#endif // DEBUG

// colors
#ifndef COLORLESS
#define ANS_CBL "\x1b[30m"
#define ANS_CR  "\x1b[31m"
#define ANS_CG  "\x1b[32m"
#define ANS_CY  "\x1b[33m"
#define ANS_CB  "\x1b[34m"
#define ANS_CM  "\x1b[35m"
#define ANS_CC  "\x1b[36m"
#define ANS_CW  "\x1b[37m"
#define ANS_RST "\x1b[0m"

#define ANS_BGBL "\x1b[40m"
#define ANS_BGR  "\x1b[41m"
#define ANS_BGG  "\x1b[42m"
#define ANS_BGY  "\x1b[43m"
#define ANS_BGB  "\x1b[44m"
#define ANS_BGM  "\x1b[45m"
#define ANS_BGC  "\x1b[46m"
#define ANS_BGW  "\x1b[47m"
#else
#define ANS_CBL  ""
#define ANS_CR   ""
#define ANS_CG   ""
#define ANS_CY   ""
#define ANS_CB   ""
#define ANS_CM   ""
#define ANS_CC   ""
#define ANS_CW   ""
#define ANS_RST  ""

#define ANS_BGBL ""
#define ANS_BGR  ""
#define ANS_BGG  ""
#define ANS_BGY  ""
#define ANS_BGB  ""
#define ANS_BGM  ""
#define ANS_BGC  ""
#define ANS_BGW  ""
#endif 

#define SEPARATOR "===-------------------------------------------------------------------------===\n"
#define ERRSEP    "================================---------------================================\n"