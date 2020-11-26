#pragma once
#include "header.h"

#define MODE_EMPUTY 0x0
#define MODE_DEBUG 0x1
#define MODE_STRING 0x2
#define MODE_MEMORY 0x3

#define NILL 0x00
#define MODE 0X07

#define STRI 0x01
#define STRC 0x02
#define STRO 0x01   
#define STRX 0x04

void (*instructions[][8]) (PARAMS) = {
    CPU_PACK0(),
    CPU_PACK4(cpu_debug_stri, cpu_debug_strc, cpu_debug_stro, cpu_debug_strx),
    CPU_PACK4(cpu_string_stri, cpu_string_strc, cpu_string_stro, cpu_string_strx),
    CPU_PACK5(cpu_memory_free, cpu_memory_aloc, cpu_memory_copy, cpu_memory_size_get, cpu_memory_size_set)
};
