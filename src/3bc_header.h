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

/*****************************************************************************/
void cpu_bitwise_not(PARAMS_DEFINE);
void cpu_bitwise_and(PARAMS_DEFINE);
void cpu_bitwise_or(PARAMS_DEFINE);
void cpu_bitwise_xor(PARAMS_DEFINE);
void cpu_bitwise_nand(PARAMS_DEFINE);
void cpu_bitwise_nor(PARAMS_DEFINE);
void cpu_bitwise_xnor(PARAMS_DEFINE);
void cpu_bitwise_left(PARAMS_DEFINE);
void cpu_bitwise_right(PARAMS_DEFINE);
void cpu_bool_not(PARAMS_DEFINE);
void cpu_bool_and(PARAMS_DEFINE);
void cpu_bool_or(PARAMS_DEFINE);
void cpu_bool_xor(PARAMS_DEFINE);
void cpu_bool_nand(PARAMS_DEFINE);
void cpu_bool_nor(PARAMS_DEFINE);
void cpu_bool_xnor(PARAMS_DEFINE);
/*****************************************************************************/
void cpu_null(PARAMS_DEFINE);
void cpu_mode(PARAMS_DEFINE);
void cpu_not_mode(PARAMS_DEFINE);
void cpu_not_exist(PARAMS_DEFINE);
void cpu_mode_reserved(PARAMS_DEFINE);
/*****************************************************************************/
void cpu_math_sum(PARAMS_DEFINE);
void cpu_math_sub(PARAMS_DEFINE);
void cpu_math_mul(PARAMS_DEFINE);
void cpu_math_div(PARAMS_DEFINE);
void cpu_math_mod(PARAMS_DEFINE);
void cpu_math_power(PARAMS_DEFINE);
void cpu_math_root(PARAMS_DEFINE);
void cpu_math_abs(PARAMS_DEFINE);
void cpu_math_logb(PARAMS_DEFINE);
void cpu_math_logn(PARAMS_DEFINE);
void cpu_math_mul_add(PARAMS_DEFINE);
/*****************************************************************************/
void cpu_jump_goto(PARAMS_DEFINE);
void cpu_jump_fgto(PARAMS_DEFINE);
void cpu_jump_zgto(PARAMS_DEFINE);
void cpu_jump_pgto(PARAMS_DEFINE);
void cpu_jump_ngto(PARAMS_DEFINE);
/*****************************************************************************/
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
/*****************************************************************************/
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
/*****************************************************************************/
void cpu_sleep_real(PARAMS_DEFINE);
void cpu_sleep_fake(PARAMS_DEFINE);
void cpu_sleep_micr(PARAMS_DEFINE);
void cpu_sleep_mili(PARAMS_DEFINE);
void cpu_sleep_seco(PARAMS_DEFINE);
/*****************************************************************************/
void cpu_string_debug(PARAMS_DEFINE);
void cpu_string_output(PARAMS_DEFINE);
void cpu_string_input(PARAMS_DEFINE);
void cpu_string_input_silent(PARAMS_DEFINE);
void cpu_string_input_password(PARAMS_DEFINE);
/*****************************************************************************/
void driver_tty_init(void);
void driver_tty_exit(void);
data_3bc_t driver_tty_input(
    struct app_3bc_s* const app, struct tty_3bc_s tty, register_3bc_t type);
void driver_tty_output(struct app_3bc_s* const app, struct tty_3bc_s tty,
    register_3bc_t type, data_3bc_t val);
void driver_tty_output_raw(
    struct app_3bc_s* const app, struct tty_3bc_s tty, const char* string);
/*****************************************************************************/
void driver_gpio_setup(
    struct app_3bc_s* const app, memory_conf_t conf, address_3bc_t pin);
void driver_gpio_output(struct app_3bc_s* const app, memory_conf_t conf,
    address_3bc_t pin, data_3bc_t data);
data_3bc_t driver_gpio_input(struct app_3bc_s* const app, memory_conf_t conf,
    address_3bc_t pin, data_3bc_t default_data);
/*****************************************************************************/
bool driver_idle(struct app_3bc_s* const app);
/*****************************************************************************/
bool driver_interrupt(struct app_3bc_s* const app);
/*****************************************************************************/
void driver_memory_data_set(
    struct app_3bc_s* const app, address_3bc_t address, data_3bc_t value);
void driver_memory_conf_set(
    struct app_3bc_s* const app, address_3bc_t address, data_3bc_t conf);
data_3bc_t driver_memory_data_get(
    struct app_3bc_s* const app, address_3bc_t address);
data_3bc_t driver_memory_conf_get(
    struct app_3bc_s* const app, address_3bc_t address);
address_3bc_t driver_memory_pointer(
    struct app_3bc_s* const app, address_3bc_t address);
void driver_memory_validate(struct app_3bc_s* const app, memory_conf_t conf);
void driver_memory_free(struct app_3bc_s* const app, address_3bc_t address);
/*****************************************************************************/
void driver_mode_set(struct app_3bc_s* const app, cpumode_3bc_t value);
/*****************************************************************************/
#ifdef SIGINT
struct app_3bc_s* const driver_power_init(int argc, char** argv);
#else
struct app_3bc_s* const driver_power_init();
#endif
void driver_power_signal(int sig);
void driver_power_exit(struct app_3bc_s* const app);
/*****************************************************************************/
void driver_program_error(
    struct app_3bc_s* const app, enum error_3bc_e error_code);
void driver_program_tick(struct app_3bc_s* const app);
/*****************************************************************************/
void ds_procedure_lifo_push(struct app_3bc_s* const app);
struct line_node_s* ds_procedure_lifo_pop(struct app_3bc_s* const app);
/*****************************************************************************/
/** TODO: move **/
int interpreter(struct app_3bc_s* const app);
void driver_custom_set(
    cpumode_3bc_t cpu_mode, register_3bc_t reg, function_3bc_t lambda);
void driver_custom_call(struct app_3bc_s* const app, register_3bc_t reg,
    address_3bc_t address, data_3bc_t value);
/*****************************************************************************/
data_aux_3bc_t driver_accumulator_get(struct app_3bc_s* const app);
void driver_accumulator_set(struct app_3bc_s* const app, data_aux_3bc_t value);
/*****************************************************************************/
struct app_3bc_s* const ds_hypervisor_darray_new(void);
struct app_3bc_s* const ds_hypervisor_darray_get_one(app_3bc_id app);
struct app_3bc_s** ds_hypervisor_darray_get_all(void);
/*****************************************************************************/
void ds_label_hash_jump(label_3bc_t label);
void ds_label_hash_insert(struct app_3bc_s* const app, label_3bc_t label);
struct label_node_s* ds_label_hash_search(
    struct app_3bc_s* const app, label_3bc_t label);
/*****************************************************************************/
data_3bc_t ds_memory_llrbt_data_get(app_3bc_id app_id, address_3bc_t address);
data_3bc_t ds_memory_llrbt_conf_get(app_3bc_id app_id, address_3bc_t address);
void ds_memory_llrbt_data_set(
    app_3bc_id app_id, address_3bc_t address, data_3bc_t value);
void ds_memory_llrbt_conf_set(
    app_3bc_id app_id, address_3bc_t address, data_3bc_t conf);
struct memory_node_s* ds_memory_llrbt_create_node(address_3bc_t address);
struct memory_node_s* ds_memory_llrbt_rotate_left(struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_rotate_right(struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_smallest_child(
    struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_access(
    struct app_3bc_s* const app, address_3bc_t address);
struct memory_node_s* ds_memory_llrbt_insert(
    address_3bc_t address, struct memory_node_s* node);
struct memory_node_s* ds_memory_llrbt_clear(
    address_3bc_t address, struct memory_node_s* node);
void ds_memory_llrbt_swap_colors(
    struct memory_node_s* node1, struct memory_node_s* node2);
void ds_memory_llrbt_destroy(struct app_3bc_s* const app);
void ds_memory_llrbt_delete(struct memory_node_s* node);
/*****************************************************************************/
void ds_program_fifo_resize(struct app_3bc_s* const app);
void ds_program_fifo_destroy(struct app_3bc_s* const app);
void ds_program_fifo_line_add(struct app_3bc_s* const app, register_3bc_t reg,
    address_3bc_t mem, data_3bc_t val);
bool ds_program_fifo_avaliable(struct app_3bc_s* const app);
/*****************************************************************************/
bool interpreter_parser_strchar(
    struct app_3bc_s* const app, const char* string, signed long int* value);
bool interpreter_parser_strhash(const char* string, signed long int* value);
bool interpreter_parser_strtol(
    struct app_3bc_s* const app, const char* string, signed long int* value);
int interpreter_parser_skip();
/*****************************************************************************/
char* interpreter_readln(struct app_3bc_s* const app, char* line);
/*****************************************************************************/
bool interpreter_syntax_constants(
    struct app_3bc_s* const app, const char* string, signed long int* value);
bool interpreter_syntax_registers(
    struct app_3bc_s* const app, const char* string, signed long int* value);
/*****************************************************************************/
bool interpreter_tokens(
    char* line, char** reg, char** mem, char** val, char** line_end);
/*****************************************************************************/
int interpreter_ticket(struct app_3bc_s* const app);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
