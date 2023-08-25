#ifndef H_TYPES_INTERPRETER_TBC
#define H_TYPES_INTERPRETER_TBC

enum ___tbc_interpreter_type_e {
    TBC_IT_NONE = 0,
    TBC_IT_REPL = 1,
    TBC_IT_INLINE = 2,
    TBC_IT_COMPILER = 3
};

typedef enum ___tbc_interpreter_type_e tbc_interpreter_type_et;
typedef struct ___tbc_interpreter_root_s tbc_interpreter_root_st;

union ___tbc_interpreter_open_u {
    tbc_u8_t fileid;
    char* argument;
};

struct ___tbc_interpreter_line_s {
    tbc_u8_t rx;
    tbc_u16_t ry;
    tbc_u16_t rz;
    bool pending;
};

struct ___tbc_interpreter_root_s {
    tbc_interpreter_type_et type;
    union ___tbc_interpreter_open_u io;
    /**
     * @brief points to fist segment of @c segments (when needs)
     * @li alocation size for text when @c type is @c TBC_IT_COMPILER/TBC_IT_REPL
     * @li end of line when @c type is @c TBC_IT_REPL
     */
    tbc_u8_t line_size;
    /**
     * @brief points to second segment of @c segments
     */
    tbc_u8_t index_line;
    /**
     * @brief points to thirdy segment of @c segments
     */
    tbc_u8_t index_label;
    /**
     * @li segment 1: text line string (length of line_size)
     * @li segment 2: parsed/peding lines stack (lifo)
     * @li segment 3: labels stack foward (lifo)
     */
    tbc_u8_t* segments;
};

#endif