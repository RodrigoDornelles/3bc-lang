#ifndef H_TYPES_TTY_TBC
#define H_TYPES_TTY_TBC

#include "types_func.h"

enum ___tbc_stream_type_e {
    STREAM_TYPE_NONE = 0,
    STREAM_TYPE_SILENT,
    STREAM_TYPE_ARDUINO_SERIAL,
    STREAM_TYPE_ARDUINO_FILE,
    STREAM_TYPE_COMPUTER_STD,
    STREAM_TYPE_COMPUTER_FILE,
    STREAM_TYPE_FUNCTION_CALL,
    STREAM_TYPE_CLONE_TTY,
    STREAM_TYPE_FIXED_ARRAY_1D
};

/**
 * NOTE: mixed type
 * when can be primitive, struct, union...
 */
typedef FILE tbc_file_mt;

#ifdef __cplusplus
#define tbc_stream_type_et enum ___tbc_stream_type_e
#define tbc_stream_io_ut union ___tbc_stream_io_u
#define tbc_tty_st struct ___tbc_tty_s
#else
typedef enum ___tbc_stream_type_e tbc_stream_type_et;
typedef union ___tbc_stream_io_u tbc_stream_io_ut;
typedef struct ___tbc_tty_s tbc_tty_st;
#endif

#if defined(__cplusplus) && defined(TBC_OPT_ULTRA_COMPACT)
#define tbc_cin_mt union ___tbc_cin_u
#define tbc_cout_mt union ___tbc_cout_u
#elif defined(__cplusplus) && !defined(TBC_OPT_ULTRA_COMPACT)
#define tbc_cin_mt struct ___tbc_cin_s
#define tbc_cout_mt struct ___tbc_cout_s
#elif defined(TBC_OPT_ULTRA_COMPACT)
/**
 * C STANDARD INPUT
 *
 * NOTE: mixed type
 * when can be struct or union
 */
typedef union ___tbc_cin_u tbc_cin_mt;
/**
 * C STANDARD OUTPUT
 *
 * NOTE: mixed type
 * when can be struct or union
 */
typedef union ___tbc_cout_u tbc_cout_mt;
#else
/**
 * C STANDARD INPUT
 *
 * NOTE: mixed type
 * when can be struct or union
 */
typedef struct ___tbc_cin_s tbc_cin_mt;
/**
 * C STANDARD OUTPUT
 *
 * NOTE: mixed type
 * when can be struct or union
 */
typedef struct ___tbc_cout_s tbc_cout_mt;
#endif

union ___tbc_stream_io_u {
    tbc_file_mt* file;
    tbc_file_mt* stream;
    tbc_func_ft lambda;
    tbc_tty_st* tty;
    tbc_u8_t* buf;
};

struct ___tbc_tty_s {
    tbc_stream_type_et type;
    tbc_stream_io_ut io;
};

union ___tbc_cin_u {
    tbc_tty_st tty_input;
    tbc_tty_st tty_source;
};

union ___tbc_cout_u {
    tbc_tty_st tty_debug;
    tbc_tty_st tty_output;
    tbc_tty_st tty_keylog;
    tbc_tty_st tty_error;
};

struct ___tbc_cin_s {
    tbc_tty_st tty_input;
    tbc_tty_st tty_source;
};

struct ___tbc_cout_s {
    tbc_tty_st tty_debug;
    tbc_tty_st tty_output;
    tbc_tty_st tty_keylog;
    tbc_tty_st tty_error;
};

#endif
