#pragma once
typedef unsigned char reg_t;
typedef unsigned char mem_t;

struct line_s {
    reg_t reg;
    mem_t adr;
    mem_t dta;
};

// FILE: cpu_common.c
void cpu_null(mem_t addres, mem_t value);


// FILE: cpu_string.c
void cpu_string_stri(mem_t addres, mem_t value);
void cpu_string_strc(mem_t addres, mem_t value);
void cpu_string_stro(mem_t addres, mem_t value);
void cpu_string_strx(mem_t addres, mem_t value);