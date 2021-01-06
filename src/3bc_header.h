#include "3bc.h"
#define RETURN_OK               0x1
#define RETURN_EXIT             0x0
#define RETURN_DEFINE           char
#define PARAMS_DEFINE           mem_t addres, val_t value
#define PARAMS_USE              addres,value
#define CPU_PACK_RESERVED()     {&cpu_null,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode}
#define CPU_PACK_PROTECTED()    {&cpu_null,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode}
#define CPU_PACK0()             {&cpu_null,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_mode}
#define CPU_PACK1(a)            {&cpu_null,&a,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK2(a,b)          {&cpu_null,&a,&b,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK3(a,b,c)        {&cpu_null,&a,&b,&c,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK4(a,b,c,d)      {&cpu_null,&a,&b,&c,&d,&cpu_not_exist,&cpu_not_exist,&cpu_mode}
#define CPU_PACK5(a,b,c,d,e)    {&cpu_null,&a,&b,&c,&d,&e,&cpu_not_exist,&cpu_mode}
#define CPU_PACK6(a,b,c,d,e,f)  {&cpu_null,&a,&b,&c,&d,&e,&f,&cpu_mode}
#define VALIDATE_NOT_DUALITY    if(addres!=0&&value!=0)lang_driver_error(ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS     if(addres!=0)lang_driver_error(ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES     if(value!=0)lang_driver_error(ERROR_PARAM_BLOCKED_VALUE);
#define REQUIRED_ADDRESS        if(addres==0)lang_driver_error(ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE          if(value==0)lang_driver_error(ERROR_PARAM_REQUIRE_VALUE);
#define MEMORY_SAFE_LIMIT       (255)
#define GET_ANY_PARAM           (addres?tape_memory_get(addres):value)
#define AUX_USE_ANY_PARAM       if(addres)cpu_memory_aux_push(addres,0);else cpu_memory_aux_aloc(0,value);
#define AUX                     tape_aux_get()              /** memory auxilary **/
#define CMODE                   tape_router_cpu_get()       /** current cpu mode **/
#define CLINE                   tape_program_line_get()     /** current line **/
#define CELNE                   tape_program_line_end()     /** current end of lines **/
#define MEM_CONFIG_SIGNED       0b0001
#define MEM_CONFIG_MAX_VALUE    0b0010
#define MEM_CONFIG_MIN_VALUE    0b0100
#define MEM_CONFIG_NORMALIZE    0b1000

/**  types **/
typedef unsigned int compass_t;
typedef unsigned char reg_t;
typedef unsigned char mem_t;
typedef unsigned char val_t;
typedef unsigned char cch_t;
typedef unsigned char conf_t;
typedef FILE file_t;

/** FILE: cpu_common.c **/
RETURN_DEFINE cpu_null(PARAMS_DEFINE);
RETURN_DEFINE cpu_mode(PARAMS_DEFINE);
RETURN_DEFINE cpu_not_mode(PARAMS_DEFINE);
RETURN_DEFINE cpu_not_exist(PARAMS_DEFINE);
RETURN_DEFINE cpu_mode_reserved(PARAMS_DEFINE);
RETURN_DEFINE cpu_mode_protected(PARAMS_DEFINE);

/** FILE: cpu_debug.c **/
RETURN_DEFINE cpu_debug_stri(PARAMS_DEFINE);
RETURN_DEFINE cpu_debug_strc(PARAMS_DEFINE);
RETURN_DEFINE cpu_debug_stro(PARAMS_DEFINE);
RETURN_DEFINE cpu_debug_strx(PARAMS_DEFINE);
RETURN_DEFINE cpu_debug_stru(PARAMS_DEFINE);

/** FILE: cpu_input.c **/
RETURN_DEFINE cpu_input_stri(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_strc(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_stro(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_strx(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_silent_stri(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_silent_strc(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_silent_stro(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_silent_strx(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_password_stri(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_password_strc(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_password_stro(PARAMS_DEFINE);
RETURN_DEFINE cpu_input_password_strx(PARAMS_DEFINE);

/** FILE: cpu_math.c **/
RETURN_DEFINE cpu_math_sum(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_sub(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_mul(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_div(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_mod(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_power(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_root(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_percentage(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_abs(PARAMS_DEFINE);
RETURN_DEFINE cpu_math_average(PARAMS_DEFINE);
void before_mode_math_average(void);

/** FILE: cpu_jump.c **/
RETURN_DEFINE cpu_jump_goto(PARAMS_DEFINE);
RETURN_DEFINE cpu_jump_fgto(PARAMS_DEFINE);
RETURN_DEFINE cpu_jump_zgto(PARAMS_DEFINE);
RETURN_DEFINE cpu_jump_pgto(PARAMS_DEFINE);
RETURN_DEFINE cpu_jump_ngto(PARAMS_DEFINE);

/** FILE: cpu_memory.c **/
RETURN_DEFINE cpu_memory_free(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_aloc(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_tcfg(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_tmin(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_tmax(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_aux_free(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_aux_aloc(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_aux_pull(PARAMS_DEFINE);
RETURN_DEFINE cpu_memory_aux_push(PARAMS_DEFINE);

/** FILE: cpu_string.c **/
RETURN_DEFINE cpu_string_stri(PARAMS_DEFINE);
RETURN_DEFINE cpu_string_strc(PARAMS_DEFINE);
RETURN_DEFINE cpu_string_stro(PARAMS_DEFINE);
RETURN_DEFINE cpu_string_strx(PARAMS_DEFINE);
RETURN_DEFINE cpu_string_stru(PARAMS_DEFINE);

/** FILE: lang_line.c **/
void lang_line(reg_t reg, mem_t mem, val_t val);

/** FILE: lang_driver.c **/
int getch(void);
int getch_parser(const char *format);
void lang_driver_run(void);
void lang_driver_init(int argc, char **argv);
void lang_driver_exit(int sig);
void lang_driver_output_1(reg_t type, val_t value);
void lang_driver_output_2(reg_t type, val_t value);
void lang_driver_error(error_t error_code);

/** FILE: lang_interpreter.c **/
char lang_interpreter_line(file_t* stream);
reg_t lang_interpreter_world(const char text_reg[5]);
signed int lang_interpreter_value(const char text_value[12]);

/** FILE: tape_aux.c **/
val_t tape_aux_get(void);
void tape_aux_set(val_t value);
void tape_aux_free(void);
val_t *tape_aux_ptr(void);

/** FILE: tape_memory.c **/
void tape_memory_type_set(mem_t addres, val_t value);
void tape_memory_value_min(mem_t addres, val_t value);
void tape_memory_value_max(mem_t addres, val_t value);
val_t tape_memory_get(mem_t addres);
void tape_memory_set(mem_t addres, val_t value);
void tape_memory_resize(mem_t addres);
void tape_memory_free(mem_t addres);
void tape_memory_destroy(void);
void tape_memory_safe(mem_t addres);

/** FILE: tape_program.c **/
void tape_program_resize(void);
RETURN_DEFINE tape_program_exe(void);
void tape_program_destroy(void);
void tape_program_line_set(compass_t line);
void tape_program_line_add(reg_t reg, mem_t mem, val_t val);
void tape_program_label_add(compass_t line, compass_t label);
compass_t tape_program_line_get();
compass_t tape_program_line_end();
void tape_program_target_label(compass_t label);
void tape_program_target_line(compass_t line);
bool tape_program_avaliable(void);

/** FILE: tape_router.c **/
void tape_router_cpu_set(cch_t value);
cch_t tape_router_cpu_get(void);