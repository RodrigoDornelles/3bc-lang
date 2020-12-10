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
#define VALIDATE_NOT_DUALITY    if(addres!=0&&value!=0)cpu_not_duality(addres,value);
#define VALIDATE_NOT_ADRESS     if(addres!=0)cpu_not_addres(addres,value);
#define VALIDATE_NOT_VALUES     if(value!=0)cpu_not_value(addres,value);
#define REQUIRED_ADDRESS        if(addres==0)cpu_required_addres(addres,value);
#define REQUIRED_VALUE          if(value==0)cpu_required_value(addres,value);
#define MEMORY_SAFE_LIMIT       (255)
#define AUX_USE_ANY_PARAM       if(addres)cpu_memory_aux_push(addres,0);else cpu_memory_aux_aloc(0,value);
#define AUX                     tape_aux_get()
#define CMODE                   tape_router_cpu_get()

typedef unsigned char reg_t;
typedef unsigned char mem_t;
typedef unsigned char val_t;
typedef unsigned char cch_t;

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
void cpu_required_addres(PARAMS_DEFINE);
void cpu_required_value(PARAMS_DEFINE);
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
void cpu_memory_aux_free(PARAMS_DEFINE);
void cpu_memory_aux_aloc(PARAMS_DEFINE);
void cpu_memory_aux_pull(PARAMS_DEFINE);
void cpu_memory_aux_push(PARAMS_DEFINE);

// FILE: cpu_string.c
void cpu_string_stri(PARAMS_DEFINE);
void cpu_string_strc(PARAMS_DEFINE);
void cpu_string_stro(PARAMS_DEFINE);
void cpu_string_strx(PARAMS_DEFINE);

// FILE: lang_driver.c
void lang_driver_init(void);
void lang_driver_exit(int sig);

// FILE: tape_aux.c
val_t tape_aux_get(void);
void tape_aux_set(val_t value);
void tape_aux_free(void);

// FILE: tape_memory.c
val_t tape_memory_get(mem_t addres);
void tape_memory_set(mem_t addres, val_t value);
void tape_memory_free(mem_t addres);

// FILE: tape_router.c
void tape_router_cpu_set(cch_t value);
cch_t tape_router_cpu_get(void);