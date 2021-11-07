#include "3bc.h"

/** PRIMITIVE TYPES **/
typedef void (*function_3bc_t)(int, int, int);
typedef unsigned short int line_3bc_t;
typedef unsigned char cpumode_3bc_t;
typedef unsigned char register_3bc_t;
typedef unsigned char address_3bc_t;
typedef unsigned char label_3bc_t;
typedef unsigned char memory_conf_t;
typedef signed int data_3bc_t;
typedef signed long data_aux_3bc_t;

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

/** DS PROCEDURE LIFO **/
struct procedure_3bc_s {
    label_3bc_t label;
    struct line_node_s* remember;
    struct procedure_3bc_s* prev;
};

/** AUXILIARY MEMORY **/
union cache_l1_u {
    bool max_init;
    bool min_init;
    bool maxmin_init;
    unsigned short average_count;
};

union cache_l2_u {
    data_3bc_t max_value;
    data_3bc_t min_value;
    data_3bc_t maxmin_value;
    long int average_sum;
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
    struct memory_node_s *left;
    struct memory_node_s *right;
};

struct memory_3bc_s {
    struct memory_node_s* root;
    data_3bc_t (*data_get)(address_3bc_t);
    data_3bc_t (*conf_get)(address_3bc_t);
    void (*data_set)(address_3bc_t, data_3bc_t);
    void (*conf_set)(address_3bc_t, data_3bc_t);
};

/** APLICATION **/
struct app_3bc_s {
    bool bootstrap;
    data_aux_3bc_t mem_aux;
    cpumode_3bc_t cpu_mode;
    struct memory_node_s* cache_l0;
    union cache_l1_u cache_l1;
    union cache_l2_u cache_l2;
    struct tty_3bc_s tty_input;
    struct tty_3bc_s tty_debug;
    struct tty_3bc_s tty_output;
    struct tty_3bc_s tty_source;
    struct tty_3bc_s tty_keylog;
    struct tty_3bc_s tty_error;
    struct program_3bc_s program;
    struct memory_3bc_s memory;
};