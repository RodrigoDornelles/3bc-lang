#include "3bc.h"
#ifdef __cplusplus
/**
 * for compilation in separate static libraries,
 * preserve native C names.
 * 
 * (required for avr compiler in arduino ide)
 */
extern "C" {
#endif
#define PARAMS_DEFINE           int addres, int value
#define PARAMS_USE              addres,value
#define CPU_PACK_ZEROMODE(mode);     case(mode):switch(reg){default:return(&cpu_not_mode);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_RESERVED(mode);     case(mode):switch(reg){default:return(&cpu_mode_reserved);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_PROTECTED(mode);    case(mode):switch(reg){default:return(&cpu_mode_protected);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK1(mode,a);           case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);}
#define CPU_PACK2(mode,a,b);         case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);}
#define CPU_PACK3(mode,a,b,c);       case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);}
#define CPU_PACK4(mode,a,b,c,d);     case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);}
#define CPU_PACK5(mode,a,b,c,d,e);   case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);}
#define CPU_PACK6(mode,a,b,c,d,e,f); case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);case(0b110):return(&f);}
#define VALIDATE_NOT_DUALITY    if(addres!=0&&value!=0)lang_driver_error(ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS     if(addres!=0)lang_driver_error(ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES     if(value!=0)lang_driver_error(ERROR_PARAM_BLOCKED_VALUE);
#define REQUIRED_ADDRESS        if(addres==0)lang_driver_error(ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE          if(value==0)lang_driver_error(ERROR_PARAM_REQUIRE_VALUE);
#define MEMORY_SAFE_LIMIT       (255)
#define GET_ANY_PARAM           (addres?tape_memory_get(addres):value)
#define AUX_USE_ANY_PARAM       if(addres)cpu_memory_aux_push(addres,0);else cpu_memory_aux_aloc(0,value);
#define AUX                     tape_aux_get()              /** memory auxilary **/
#define CLINE                   tape_program_line_get()     /** current line **/
#define CELNE                   tape_program_line_end()     /** current end of lines **/
#define MEM_CONFIG_SIGNED       0b0001
#define MEM_CONFIG_MAX_VALUE    0b0010
#define MEM_CONFIG_MIN_VALUE    0b0100
#define MEM_CONFIG_NORMALIZE    0b1000

typedef unsigned int compass_t;
typedef void (*reg_f)(PARAMS_DEFINE);
typedef unsigned char conf_t;

/** FILE: cpu_common.c **/
void cpu_null(PARAMS_DEFINE);
void cpu_mode(PARAMS_DEFINE);
void cpu_not_mode(PARAMS_DEFINE);
void cpu_not_exist(PARAMS_DEFINE);
void cpu_mode_reserved(PARAMS_DEFINE);
void cpu_mode_protected(PARAMS_DEFINE);

/** FILE: cpu_debug.c **/
void cpu_debug_stri(PARAMS_DEFINE);
void cpu_debug_strc(PARAMS_DEFINE);
void cpu_debug_stro(PARAMS_DEFINE);
void cpu_debug_strx(PARAMS_DEFINE);
void cpu_debug_stru(PARAMS_DEFINE);

/** FILE: cpu_helper.c **/
void cpu_helper_average(PARAMS_DEFINE);
void cpu_helper_sort(PARAMS_DEFINE);
void cpu_helper_max(PARAMS_DEFINE);
void cpu_helper_min(PARAMS_DEFINE);
void before_helper_average(void);
void before_helper_sort(void);
void before_helper_max(void);
void before_helper_min(void);
void after_helper_sort(void);
void after_helper_max(void);
void after_helper_min(void);

/** FILE: cpu_input.c **/
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

/** FILE: cpu_math.c **/
void cpu_math_sum(PARAMS_DEFINE);
void cpu_math_sub(PARAMS_DEFINE);
void cpu_math_mul(PARAMS_DEFINE);
void cpu_math_div(PARAMS_DEFINE);
void cpu_math_mod(PARAMS_DEFINE);
void cpu_math_power(PARAMS_DEFINE);
void cpu_math_root(PARAMS_DEFINE);
void cpu_math_percentage(PARAMS_DEFINE);
void cpu_math_abs(PARAMS_DEFINE);

/** FILE: cpu_jump.c **/
void cpu_jump_goto(PARAMS_DEFINE);
void cpu_jump_fgto(PARAMS_DEFINE);
void cpu_jump_zgto(PARAMS_DEFINE);
void cpu_jump_pgto(PARAMS_DEFINE);
void cpu_jump_ngto(PARAMS_DEFINE);

/** FILE: cpu_memory.c **/
void cpu_memory_free(PARAMS_DEFINE);
void cpu_memory_aloc(PARAMS_DEFINE);
void cpu_memory_tcfg(PARAMS_DEFINE);
void cpu_memory_tmin(PARAMS_DEFINE);
void cpu_memory_tmax(PARAMS_DEFINE);
void cpu_memory_aux_free(PARAMS_DEFINE);
void cpu_memory_aux_aloc(PARAMS_DEFINE);
void cpu_memory_aux_pull(PARAMS_DEFINE);
void cpu_memory_aux_push(PARAMS_DEFINE);
void cpu_memory_aux_spin(PARAMS_DEFINE);

/** FILE: cpu_string.c **/
void cpu_string_stri(PARAMS_DEFINE);
void cpu_string_strc(PARAMS_DEFINE);
void cpu_string_stro(PARAMS_DEFINE);
void cpu_string_strx(PARAMS_DEFINE);
void cpu_string_stru(PARAMS_DEFINE);

/** FILE: lang_boostrap.c **/
struct app_3bc_s* lang_bootstrap(void);

/** FILE: lang_plus.cpp **/
#ifdef _3BC_ARDUINO
void arduino_serial_begin(void);
void arduino_serial_print(unsigned char serial, const char* string);
#endif

/** FILE: lang_driver.c **/
void lang_driver_run(void);
#ifdef _3BC_COMPUTER
void lang_driver_init(int argc, char **argv);
#endif
#ifdef _3BC_ARDUINO
void lang_driver_init();
#endif
void lang_driver_exit(int sig);
void lang_driver_output_1(register_3bc_t type, data_3bc_t value);
void lang_driver_output_2(register_3bc_t type, data_3bc_t value);
void lang_driver_error(error_3bc_t error_code);
data_3bc_t lang_driver_input(register_3bc_t type, address_3bc_t addres);
bool lang_driver_strtol(const char* string, signed long int* value);

/** FILE: lang_interpreter.c **/
char lang_interpreter_line(file_t* stream);
bool lang_interpreter_world(const char text_reg[6], int* reg);
bool lang_interpreter_value(const char text_value[12], int* value);

/** FILE: tape_aux.c **/
data_3bc_t tape_aux_get(void);
void tape_aux_set(data_3bc_t value);
void tape_aux_free(void);
data_3bc_t *tape_aux_ptr(void);

/** FILE: tape_memory.c **/
data_3bc_t tape_memory_type_get(address_3bc_t addres);
data_3bc_t tape_memory_value_min_get(address_3bc_t addres);
data_3bc_t tape_memory_value_max_get(address_3bc_t addres);
void tape_memory_type_set(address_3bc_t addres, data_3bc_t value);
void tape_memory_value_min_set(address_3bc_t addres, data_3bc_t value);
void tape_memory_value_max_set(address_3bc_t addres, data_3bc_t value);
data_3bc_t tape_memory_get(address_3bc_t addres);
void tape_memory_set(address_3bc_t addres, data_3bc_t value);
void tape_memory_resize(address_3bc_t addres);
void tape_memory_free(address_3bc_t addres);
void tape_memory_init(void);
void tape_memory_destroy(void);
void tape_memory_safe(address_3bc_t addres);
void tape_memory_reset(address_3bc_t addres);

/** FILE: tape_program.c **/
void tape_program_resize(void);
bool tape_program_exe(void);
void tape_program_destroy(void);
void tape_program_line_add(register_3bc_t reg, address_3bc_t mem, data_3bc_t val);
void tape_program_label_jump(label_3bc_t label);
void tape_program_label_insert(label_3bc_t label, cpumode_3bc_t cpumode, struct line_node_s* line);
struct label_node_s* tape_program_label_search(label_3bc_t label);
bool tape_program_avaliable(void);

/** FILE: tape_router.c **/
void tape_router_cpu_set(cpumode_3bc_t value);
cpumode_3bc_t tape_router_cpu_get(void);

/** FILE: tape_sort.c **/
void tape_sort_init();
void tape_sort_destroy();
void tape_sort_insert(address_3bc_t addres);

#ifdef __cplusplus
}
#endif