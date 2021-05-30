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
#define VALIDATE_NOT_DUALITY    if(addres!=0&&value!=0)lang_driver_error(ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS     if(addres!=0)lang_driver_error(ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES     if(value!=0)lang_driver_error(ERROR_PARAM_BLOCKED_VALUE);
#define REQUIRED_ADDRESS        if(addres==0)lang_driver_error(ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE          if(value==0)lang_driver_error(ERROR_PARAM_REQUIRE_VALUE);
#define GET_ANY_PARAM           (addres?tape_memory_data_get(addres):value)
#define AUX_USE_ANY_PARAM       if(addres)cpu_memory_aux_push(addres,0);else cpu_memory_aux_aloc(0,value);

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
void cpu_helper_percentage(PARAMS_DEFINE);
void before_helper_average(void);
void before_helper_sort(void);
void before_helper_maxmin(void);
void after_helper_sort(void);
void after_helper_maxmin(void);

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
void cpu_math_abs(PARAMS_DEFINE);
void cpu_math_negative(PARAMS_DEFINE);

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
void lang_driver_exit(int sig);
#endif
#ifdef _3BC_ARDUINO
void lang_driver_init();
void lang_driver_exit();
#endif
void lang_driver_output(struct tty_3bc_s tty, register_3bc_t type, data_3bc_t value);
void lang_driver_error(int error_code);
data_3bc_t lang_driver_input(register_3bc_t type, address_3bc_t addres);
bool lang_driver_strtol(const char* string, signed long int* value);
bool lang_driver_strchar(const char* string, signed long int* value);
bool lang_driver_strhash(const char* string, signed long int* value);
bool lang_driver_strword(const char* string, signed long int* value);
int lang_driver_skip(void);

/** FILE: lang_interpreter.c **/
char lang_interpreter_line(file_t* stream);
bool lang_interpreter_world(const char text_reg[6], int* reg);
bool lang_interpreter_value(const char text_value[12], int* value);

/** FILE: tape_aux.c **/
data_aux_3bc_t tape_aux_get(void);
void tape_aux_set(data_aux_3bc_t value);

/** FILE: tape_memory.c **/
struct memory_node_s* tape_memory_llrbt_create_node(address_3bc_t address);
struct memory_node_s* tape_memory_llrbt_rotate_left(struct memory_node_s* node);
struct memory_node_s* tape_memory_llrbt_rotate_right(struct memory_node_s* node);
struct memory_node_s* tape_memory_llrbt_smallest_child(struct memory_node_s* node);
struct memory_node_s* tape_memory_llrbt_access(address_3bc_t address);
struct memory_node_s* tape_memory_llrbt_insert(address_3bc_t address, struct memory_node_s* node);
struct memory_node_s* tape_memory_llrbt_clear(address_3bc_t address, struct memory_node_s* node);
void tape_memory_llrbt_swap_colors(struct memory_node_s* node1, struct memory_node_s* node2);
void tape_memory_data_set(address_3bc_t address, data_3bc_t value);
void tape_memory_vmax_set(address_3bc_t address, data_3bc_t value);
void tape_memory_vmin_set(address_3bc_t address, data_3bc_t value);
void tape_memory_conf_set(address_3bc_t address, data_3bc_t value);
data_3bc_t tape_memory_data_get(address_3bc_t address);
data_3bc_t tape_memory_vmax_get(address_3bc_t address);
data_3bc_t tape_memory_vmin_get(address_3bc_t address);
data_3bc_t tape_memory_data_get(address_3bc_t address);
void tape_memory_lineup(struct memory_node_s* node);
void tape_memory_free(address_3bc_t address);
void tape_memory_destroy(void);

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