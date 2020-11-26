#pragma once
#include "header.h"

#define MODE_EMPUTY             0x0
#define MODE_DEBUG              0x1
#define MODE_STRING             0x2
#define MODE_INPUT              0x3
#define MODE_INPUT_SILENT       0x4
#define MODE_INPUT_PASSWORD     0x5
#define MODE_MEMORY             0x6
#define MODE_PROTECTED          0x7

#define NILL 0x00
#define MODE 0X07

#define STRI 0x01
#define STRC 0x02
#define STRO 0x03   
#define STRX 0x04

#define FREE 0x01
#define ALOC 0x02
#define COPY 0x03
#define GETM 0x04
#define SETM 0x05
#define AUXM 0x06

void (*instructions[][8]) (PARAMS_DEFINE) = {
    CPU_PACK0(),
    CPU_PACK4(cpu_debug_stri, cpu_debug_strc, cpu_debug_stro, cpu_debug_strx),
    CPU_PACK4(cpu_string_stri, cpu_string_strc, cpu_string_stro, cpu_string_strx),
    CPU_PACK4(cpu_input_stri, cpu_input_strc, cpu_input_stro, cpu_input_strx),
    CPU_PACK4(cpu_input_silent_stri, cpu_input_silent_strc, cpu_input_silent_stro, cpu_input_silent_strx),
    CPU_PACK4(cpu_input_password_stri, cpu_input_password_strc, cpu_input_password_stro, cpu_input_password_strx),
    CPU_PACK6(cpu_memory_free, cpu_memory_aloc, cpu_memory_copy, cpu_memory_size_get, cpu_memory_size_set, cpu_memory_aux),
    CPU_PACK_PROTECTED()
};
