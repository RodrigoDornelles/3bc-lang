#pragma once
#define CPU_PACK(a,b,c,d)       {&cpu_null,&a,&b,&c,&d,&cpu_null,&cpu_null,&cpu_mode}
#define VALIDATE_NOT_DUALITY    if(addres&&value)cpu_not_duality(addres,value);

typedef unsigned char reg_t;
typedef unsigned char mem_t;

struct line_s {
    reg_t reg;
    mem_t adr;
    mem_t dta;
};

// FILE: cpu_common.c
void cpu_null(mem_t addres, mem_t value);
void cpu_mode(mem_t addres, mem_t value);
void cpu_not_mode(mem_t addres, mem_t value);
void cpu_not_duality(mem_t addres, mem_t value);

// FILE: cpu_debug.c
void cpu_debug_stri(mem_t addres, mem_t value);
void cpu_debug_strc(mem_t addres, mem_t value);
void cpu_debug_stro(mem_t addres, mem_t value);
void cpu_debug_strx(mem_t addres, mem_t value);

// FILE: cpu_memory.c
void cpu_memory_free(mem_t addres, mem_t value);
void cpu_memory_aloc(mem_t addres, mem_t value);
void cpu_memory_copy(mem_t addres, mem_t value);

// FILE: cpu_string.c
void cpu_string_stri(mem_t addres, mem_t value);
void cpu_string_strc(mem_t addres, mem_t value);
void cpu_string_stro(mem_t addres, mem_t value);
void cpu_string_strx(mem_t addres, mem_t value);