#pragma once
#define PARAMS_DEFINE           mem_t addres, val_t value
#define PARAMS_USE              addres,value
#define CPU_PACK_PROTECTED()    {&cpu_null,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode}
#define CPU_PACK0()             {&cpu_null,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_mode}
#define CPU_PACK1(a)            {&cpu_null,&a,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK2(a,b)          {&cpu_null,&a,&b,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK3(a,b,c)        {&cpu_null,&a,&b,&c,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK4(a,b,c,d)      {&cpu_null,&a,&b,&c,&d,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK5(a,b,c,d,e)    {&cpu_null,&a,&b,&c,&d,&e,&cpu_not_exist,&cpu_mode}
#define CPU_PACK6(a,b,c,d,e,f)  {&cpu_null,&a,&b,&c,&d,&e,&f,&cpu_mode}
#define VALIDATE_NOT_DUALITY    if(addres&&value)cpu_not_duality(addres,value);
#define VALIDATE_NOT_ADRESS     if(addres)cpu_not_addres(addres,value);
#define VALIDATE_NOT_VALUES     if(value)cpu_not_value(addres,value);
#define MEMORY_SAFE_LIMIT       255
#define AUX_USE_ANY_PARAM       if(addres)cpu_memory_aux(0,addres);else internal_memory_aux_set(0,value);
#define AUX                     internal_memory_aux_get(0,0)
#define CMODE                   internal_memory_cpu_mode_get(0,0)

typedef unsigned char reg_t;
typedef unsigned char mem_t;
typedef unsigned char val_t;


struct line_s {
    reg_t reg;
    mem_t adr;
    mem_t dta;
};

// FILE: cpu_common.c
void cpu_null(PARAMS_DEFINE);
void cpu_mode(PARAMS_DEFINE);
void cpu_not_mode(PARAMS_DEFINE);
void cpu_not_duality(PARAMS_DEFINE);
void cpu_not_exist(PARAMS_DEFINE);
void cpu_not_addres(PARAMS_DEFINE);
void cpu_not_value(PARAMS_DEFINE);
void cpu_mode_protected(PARAMS_DEFINE);

// FILE: cpu_debug.c
void cpu_debug_stri(PARAMS_DEFINE);
void cpu_debug_strc(PARAMS_DEFINE);
void cpu_debug_stro(PARAMS_DEFINE);
void cpu_debug_strx(PARAMS_DEFINE);

// FILE: cpu_input.c
void cpu_input_stri(PARAMS_DEFINE);
void cpu_input_strc(PARAMS_DEFINE);
void cpu_input_stro(PARAMS_DEFINE);
void cpu_input_strx(PARAMS_DEFINE);
void cpu_input_silent_stri(PARAMS_DEFINE);
void cpu_input_silent_strc(PARAMS_DEFINE);
void cpu_input_silent_stro(PARAMS_DEFINE);
void cpu_input_silent_strx(PARAMS_DEFINE);
void cpu_input_password_stri(PARAMS_DEFINE);
void cpu_input_password_strc(PARAMS_DEFINE);
void cpu_input_password_stro(PARAMS_DEFINE);
void cpu_input_password_strx(PARAMS_DEFINE);
void internal_input_stri(PARAMS_DEFINE);
void internal_input_strc(PARAMS_DEFINE);
void internal_input_stro(PARAMS_DEFINE);
void internal_input_strx(PARAMS_DEFINE);

// FILE: cpu_memory.c
void cpu_memory_free(PARAMS_DEFINE);
void cpu_memory_aloc(PARAMS_DEFINE);
void cpu_memory_copy(PARAMS_DEFINE);
void cpu_memory_size_get(PARAMS_DEFINE);
void cpu_memory_size_set(PARAMS_DEFINE);
void cpu_memory_aux(PARAMS_DEFINE);
val_t internal_memory_aux_get(PARAMS_DEFINE);
void internal_memory_aux_set(PARAMS_DEFINE);
val_t internal_memory_cpu_mode_get(PARAMS_DEFINE);
void internal_memory_cpu_mode_set(PARAMS_DEFINE);

// FILE: cpu_string.c
void cpu_string_stri(PARAMS_DEFINE);
void cpu_string_strc(PARAMS_DEFINE);
void cpu_string_stro(PARAMS_DEFINE);
void cpu_string_strx(PARAMS_DEFINE);
