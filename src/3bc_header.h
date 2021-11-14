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

/** FILE: cpu_bool.c **/
void cpu_bool_not(PARAMS_DEFINE);
void cpu_bool_and(PARAMS_DEFINE);
void cpu_bool_or(PARAMS_DEFINE);
void cpu_bool_xor(PARAMS_DEFINE);
void cpu_bool_nand(PARAMS_DEFINE);
void cpu_bool_nor(PARAMS_DEFINE);
void cpu_bool_xnor(PARAMS_DEFINE);
void cpu_bool_and_not(PARAMS_DEFINE);
void cpu_bool_or_not(PARAMS_DEFINE);

/** FILE: cpu_common.c **/
void cpu_null(PARAMS_DEFINE);
void cpu_mode(PARAMS_DEFINE);
void cpu_not_mode(PARAMS_DEFINE);
void cpu_not_exist(PARAMS_DEFINE);
void cpu_mode_reserved(PARAMS_DEFINE);

/** FILE: cpu_debug.c **/
void cpu_debug_strb(PARAMS_DEFINE);
void cpu_debug_stri(PARAMS_DEFINE);
void cpu_debug_strc(PARAMS_DEFINE);
void cpu_debug_stro(PARAMS_DEFINE);
void cpu_debug_strx(PARAMS_DEFINE);
void cpu_debug_stru(PARAMS_DEFINE);

/** FILE: cpu_helper.c **/
void cpu_helper_average(PARAMS_DEFINE);
void cpu_helper_max(PARAMS_DEFINE);
void cpu_helper_min(PARAMS_DEFINE);
void cpu_helper_percentage(PARAMS_DEFINE);
void cpu_helper_reverse(PARAMS_DEFINE);
void cpu_helper_log10(PARAMS_DEFINE);
void cpu_helper_log2(PARAMS_DEFINE);
void cpu_helper_mul_add(PARAMS_DEFINE);
void cpu_helper_sign(PARAMS_DEFINE);
void before_helper_average(void);
void before_helper_maxmin(void);
void after_helper_maxmin(void);

/** FILE: cpu_input.c **/
void cpu_input_strb(PARAMS_DEFINE);
void cpu_input_stri(PARAMS_DEFINE);
void cpu_input_strc(PARAMS_DEFINE);
void cpu_input_stro(PARAMS_DEFINE);
void cpu_input_strx(PARAMS_DEFINE);
void cpu_input_silent_strb(PARAMS_DEFINE);
void cpu_input_silent_stri(PARAMS_DEFINE);
void cpu_input_silent_strc(PARAMS_DEFINE);
void cpu_input_silent_stro(PARAMS_DEFINE);
void cpu_input_silent_strx(PARAMS_DEFINE);
void cpu_input_password_strb(PARAMS_DEFINE);
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
void cpu_memory_moff(PARAMS_DEFINE);
void cpu_memory_muse(PARAMS_DEFINE);
void cpu_memory_ptr_free(PARAMS_DEFINE);
void cpu_memory_ptr_aloc(PARAMS_DEFINE);
void cpu_memory_ptr_pull(PARAMS_DEFINE);
void cpu_memory_ptr_push(PARAMS_DEFINE);
void cpu_memory_ptr_spin(PARAMS_DEFINE);
void cpu_memory_aux_free(PARAMS_DEFINE);
void cpu_memory_aux_aloc(PARAMS_DEFINE);
void cpu_memory_aux_pull(PARAMS_DEFINE);
void cpu_memory_aux_push(PARAMS_DEFINE);
void cpu_memory_aux_spin(PARAMS_DEFINE);

/** FILE: cpu_procedure.c **/
void cpu_procedure_call(PARAMS_DEFINE);
void cpu_procedure_back(PARAMS_DEFINE);
void cpu_procedure_fcal(PARAMS_DEFINE);
void cpu_procedure_zcal(PARAMS_DEFINE);
void cpu_procedure_pcal(PARAMS_DEFINE);
void cpu_procedure_ncal(PARAMS_DEFINE);
void cpu_procedure_fret(PARAMS_DEFINE);
void cpu_procedure_zret(PARAMS_DEFINE);
void cpu_procedure_pret(PARAMS_DEFINE);
void cpu_procedure_nret(PARAMS_DEFINE);

/** FILE: cpu_string.c **/
void cpu_string_strb(PARAMS_DEFINE);
void cpu_string_stri(PARAMS_DEFINE);
void cpu_string_strc(PARAMS_DEFINE);
void cpu_string_stro(PARAMS_DEFINE);
void cpu_string_strx(PARAMS_DEFINE);
void cpu_string_stru(PARAMS_DEFINE);

/** FILE: driver_tty.c **/
optional_inline void driver_tty_init(void);
optional_inline void driver_tty_exit(void);
data_3bc_t driver_tty_input(register_3bc_t type, address_3bc_t addres);
void driver_tty_output(struct tty_3bc_s tty, register_3bc_t type, data_3bc_t val);
void driver_tty_output_raw(struct tty_3bc_s tty,const char* string);
#ifdef _3BC_COMPUTER
void driver_tty_signal(int sig);
#endif

/** FILE: driver_.c **/
void driver_gpio_setup(memory_conf_t conf, address_3bc_t pin);
void driver_gpio_output(memory_conf_t conf, address_3bc_t pin, data_3bc_t data);
data_3bc_t driver_gpio_input(memory_conf_t conf, address_3bc_t pin, data_3bc_t default_data);

/** FILE: driver_memory.c **/
void driver_memory_data_set(address_3bc_t address, data_3bc_t value);
void driver_memory_conf_set(address_3bc_t address, data_3bc_t conf);
data_3bc_t driver_memory_data_get(address_3bc_t address);
optional_inline data_3bc_t driver_memory_conf_get(address_3bc_t address);
address_3bc_t driver_memory_pointer(address_3bc_t address);
void driver_memory_validate(memory_conf_t conf);
void driver_memory_free(address_3bc_t address);

/** FILE: driver_power.c **/
#ifdef _3BC_COMPUTER
app_3bc_t driver_power_init(int argc, char **argv);
void driver_power_exit(int sig);
void driver_power_signal(int sig);
#else
app_3bc_t driver_power_init();
void driver_power_exit();
#endif

/** FILE: driver_program.c **/
void driver_program_error(enum error_3bc_e error_code);
void driver_program_tick(app_3bc_t app);

/** FILE: ds_procedure_lifo.c **/
void ds_procedure_lifo_push(struct line_node_s* line_node, label_3bc_t label);
struct line_node_s* ds_procedure_lifo_burst(label_3bc_t label);
struct line_node_s* ds_procedure_lifo_pop();

/** FILE: interpreter_compiler.c **/
bool interpreter_compiler(struct tty_3bc_s tty);

/** FILE: interpreter_parser.c **/
bool interpreter_parser_strtol(const char* string, signed long int* value);
bool interpreter_parser_strchar(const char* string, signed long int* value);
bool interpreter_parser_strhash(const char* string, signed long int* value);
int interpreter_parser_skip();

int interpreter_read(app_3bc_t app);

/** FILE: interpreter_syntax.c **/
bool interpreter_syntax_registers(const char* string, signed long int* value);
bool interpreter_syntax_constants(const char* string, signed long int* value);

/** FILE: interpreter_tokens.c **/
bool interpreter_tokens(struct tty_3bc_s tty, char** reg, char** mem, char** val);

/** FILE: driver_accumulator.c **/
data_aux_3bc_t driver_accumulator_get(void);
void driver_accumulator_set(data_aux_3bc_t value);

/** FILE: ds_fpga_array.c **/
#if defined(_3BC_ENABLE_CUSTOM)
void ds_fpg_array_func_set(cpumode_3bc_t cpu_mode, register_3bc_t reg, function_3bc_t lambda);
void ds_fpg_array_func_call(cpumode_3bc_t cpu_mode, register_3bc_t reg, address_3bc_t address, data_3bc_t value);
#endif

/** FILE: ds_memory_llrbt.c **/
data_3bc_t ds_memory_llrbt_data_get(address_3bc_t address);
data_3bc_t ds_memory_llrbt_conf_get(address_3bc_t address);
void ds_memory_llrbt_data_set(address_3bc_t address, data_3bc_t value);
void ds_memory_llrbt_conf_set(address_3bc_t address, data_3bc_t conf);
struct memory_node_s* ds_memory_llrbt_create_node(address_3bc_t address);
struct memory_node_s* ds_memory_llrbt_rotate_left(struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_rotate_right(struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_smallest_child(struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_access(address_3bc_t address);
struct memory_node_s* ds_memory_llrbt_insert(address_3bc_t address, struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_clear(address_3bc_t address, struct memory_node_s* node);
void ds_memory_llrbt_swap_colors(struct memory_node_s* node1, struct memory_node_s* node2);
/** TODO: rename and work it **/
void tape_memory_destroy(void);

/** FILE: tape_program.c **/
void tape_program_resize(void);
void tape_program_destroy(void);
void tape_program_line_add(register_3bc_t reg, address_3bc_t mem, data_3bc_t val);
void tape_program_label_jump(label_3bc_t label);
void tape_program_label_insert(label_3bc_t label, cpumode_3bc_t cpumode, struct line_node_s* line);
struct label_node_s* tape_program_label_search(label_3bc_t label);
bool tape_program_avaliable(app_3bc_t app);

/** FILE: tape_router.c **/
void tape_router_cpu_set(cpumode_3bc_t value);
cpumode_3bc_t tape_router_cpu_get(void);

#ifdef __cplusplus
}
#endif