#ifndef H_TYPES_INTERPRETER_TBC
#define H_TYPES_INTERPRETER_TBC

enum ___tbc_interpreter_type_e {
    TBC_IT_NONE = 0,
    TBC_IT_REPL = 1,
    TBC_IT_INLINE = 2,
    TBC_IT_COMPILE = 3,
    TBC_IT_ERROR_OPEN_FILE = 4
};

typedef enum ___tbc_interpreter_type_e tbc_interpreter_type_et;
typedef struct ___tbc_interpreter_root_s tbc_interpreter_root_st;

union ___tbc_interpreter_open_u {
    tbc_u8_t fileid;
    char* argument;
};

struct ___tbc_interpreter_root_s {
    tbc_interpreter_type_et type;
    union ___tbc_interpreter_open_u io;
};

#endif