#include "3bc.h"

/** PRIMITIVE TYPES **/
typedef unsigned short int line_3bc_t;
typedef unsigned char cpumode_3bc_t;
typedef unsigned char register_3bc_t;
typedef unsigned short address_3bc_t;
typedef unsigned char label_3bc_t;
typedef unsigned char memory_conf_t;
typedef signed int data_3bc_t;
typedef signed long data_aux_3bc_t;
typedef unsigned char app_3bc_id;

/** FILE/STREAM/INTERFACE TYPES **/
typedef FILE file_t;

enum stream_type_e {
    STREAM_TYPE_NONE = 0,
    STREAM_TYPE_SILENT,
    STREAM_TYPE_ARDUINO_SERIAL,
    STREAM_TYPE_ARDUINO_FILE,
    STREAM_TYPE_COMPUTER_STD,
    STREAM_TYPE_COMPUTER_FILE,
    STREAM_TYPE_FUNCTION_CALL,
    STREAM_TYPE_CLONE_TTY
};

union stream_file_u {
    file_t* file;
    file_t* stream;
    void (*lambda)(char*);
    struct tty_3bc_s* tty;
};

struct tty_3bc_s {
    enum stream_type_e type;
    union stream_file_u io;
};

/** FSM INTERRUPTS **/
enum fsm_3bc_e {
    FSM_3BC_DEFAULT = 0,
    FSM_3BC_READING,
    FSM_3BC_RUNNING,
    FSM_3BC_WAITING,
    FSM_3BC_IO_READ,
    FSM_3BC_IO_SEND,
    FSM_3BC_EXITING,
    FSM_3BC_STOPED
};

/** DS PROCEDURE LIFO **/
struct procedure_3bc_s {
    label_3bc_t label;
    struct line_node_s* remember;
    struct procedure_3bc_s* prev;
};

/** AUXILIARY MEMORY **/
enum sleep_3bc_e {
    SLEEP_3BC_NONE = 0,
    SLEEP_3BC_REAL_TICK,
    SLEEP_3BC_FAKE_TICK,
    SLEEP_3BC_MICROSECONDS,
    SLEEP_3BC_MILLISECONDS,
    SLEEP_3BC_SECONDS
};

struct buffer_s {
    char* storage;
    unsigned int size;
};

union cache_l1_u {
    enum sleep_3bc_e sleep_mode;
};

union cache_l2_u {
    unsigned long sleep_period;
};

union cache_l3_u {
    struct buffer_s buffer;
    unsigned long sleep_called;
};

/** PROGRAM MEMORY **/
struct label_node_s {
    label_3bc_t label;
    cpumode_3bc_t cpumode;
    struct label_node_s* next;
    struct line_node_s* point;
};

struct line_columns_s {
    register_3bc_t reg;
    address_3bc_t adr;
    data_3bc_t dta;
};

struct line_node_s {
    line_3bc_t line;
    struct line_node_s* next;
    struct line_columns_s column;
};

struct program_3bc_s {
    line_3bc_t last_line;
    cpumode_3bc_t last_cpu;
    label_3bc_t label_target;
    struct line_node_s* curr;
    struct line_node_s* head;
    struct line_node_s* tail;
    struct label_node_s* label_table[LABEL_HASH_SIZE];
    struct procedure_3bc_s* stack;
};

/** MEMORY PRIMARY **/
struct memory_node_s {
    bool color;
    memory_conf_t conf;
    data_3bc_t data;
    address_3bc_t address;
    struct memory_node_s* left;
    struct memory_node_s* right;
};

struct memory_3bc_s {
    struct memory_node_s* root;
    struct memory_node_s* cache;
    data_3bc_t (*data_get)(app_3bc_id, address_3bc_t);
    data_3bc_t (*conf_get)(app_3bc_id, address_3bc_t);
    void (*data_set)(app_3bc_id, address_3bc_t, data_3bc_t);
    void (*conf_set)(app_3bc_id, address_3bc_t, data_3bc_t);
};

/** APLICATION **/
struct app_3bc_s {
    app_3bc_id id;
    enum fsm_3bc_e state;
    data_aux_3bc_t mem_aux;
    cpumode_3bc_t cpu_mode;
    enum error_3bc_e error_code;
    union cache_l1_u cache_l1;
    union cache_l2_u cache_l2;
    union cache_l3_u cache_l3;
    struct tty_3bc_s tty_input;
    struct tty_3bc_s tty_debug;
    struct tty_3bc_s tty_output;
    struct tty_3bc_s tty_source;
    struct tty_3bc_s tty_keylog;
    struct tty_3bc_s tty_error;
    struct program_3bc_s program;
    struct memory_3bc_s memory;
};

typedef void (*function_3bc_t)(
    struct app_3bc_s* const, register_3bc_t, address_3bc_t, data_3bc_t);
