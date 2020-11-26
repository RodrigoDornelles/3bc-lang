#pragma once
#include "header.h"
#define CPU_PACK(a,b,c,d)   {&cpu_null,&a,&b,&c,&d,&cpu_null,&cpu_null,&cpu_null}

#define NILL 0x00
#define MODE 0X07
#define STRI 0x01
#define STRC 0x02
#define STRO 0x01   
#define STRX 0x04

void (*instructions[][8]) (mem_t addres, mem_t value) = {
    CPU_PACK(cpu_string_stri, cpu_string_strc, cpu_string_stro, cpu_string_strx)
};
