#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void __potato_dump_lock();
void __potato_dump_unlock();

void __potato_dump_enter_prologue();
void   __potato_dump_exit_prologue();

void   __potato_noop();

void __potato_declaration_enum(const char* type_name, const char* name);
void __potato_dump_enum(const char* type_name , const char* name, int32_t value);

void __potato_dump_enum_i8 (const char* type_name , const char* name, int8_t   value, uintptr_t ptr);
void __potato_dump_enum_i16(const char* type_name , const char* name, int16_t  value, uintptr_t ptr); 
void __potato_dump_enum_i32(const char* type_name , const char* name, int32_t  value, uintptr_t ptr); 
void __potato_dump_enum_i64(const char* type_name , const char* name, int64_t  value, uintptr_t ptr); 
void __potato_dump_enum_u8 (const char* type_name , const char* name, uint8_t  value, uintptr_t ptr); 
void __potato_dump_enum_u16(const char* type_name , const char* name, uint16_t value, uintptr_t ptr); 
void __potato_dump_enum_u32(const char* type_name , const char* name, uint32_t value, uintptr_t ptr); 
void __potato_dump_enum_u64(const char* type_name , const char* name, uint64_t value, uintptr_t ptr); 

void __potato_dump_origin_place(const char* type_name , const char* name, uint64_t value, uintptr_t addr, int size); 

void __potato_cov_enum_i8 (const char* type_name , int8_t  value, int32_t line, uint32_t cov_id, uint32_t ori_id);
void __potato_cov_enum_i16(const char* type_name , int16_t value, int32_t line, uint32_t cov_id, uint32_t ori_id);
void __potato_cov_enum_i32(const char* type_name , int32_t value, int32_t line, uint32_t cov_id, uint32_t ori_id);
void __potato_cov_enum_i64(const char* type_name , int64_t value, int32_t line, uint32_t cov_id, uint32_t ori_id);

#ifdef __cplusplus
} // extern "C"
#endif