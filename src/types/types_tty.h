#ifndef H_TYPES_TTY_TBC
#define H_TYPES_TTY_TBC

#include "detect/detect_opt.h"
#include "types/types_func.h"

enum ___tbc_stream_type_e {
    STREAM_TYPE_NONE = 0,
    STREAM_TYPE_SILENT,
    STREAM_TYPE_ARDUINO_SERIAL,
    STREAM_TYPE_ARDUINO_FILE,
    STREAM_TYPE_COMPUTER_STD,
    STREAM_TYPE_COMPUTER_FILE,
    STREAM_TYPE_FUNCTION_CALL,
    STREAM_TYPE_CLONE_TTY,
    STREAM_TYPE_FIXED_ARRAY_1D,
    STREAM_TYPE_POSIX_FILEID,
    STREAM_TYPE_NES_FULLSCREEN
};

#if defined(TBC_NOT_FILES)
/**
 * NOTE: mixed type
 * when can be primitive, pointer, struct, union...
 */
typedef void* tbc_file_mt;
#else
/**
 * NOTE: mixed type
 * when can be primitive, pointer, struct, union...
 */
#include <stdio.h>
typedef FILE tbc_file_mt;
#endif
typedef enum ___tbc_stream_type_e tbc_stream_type_et;
typedef union ___tbc_stream_io_u tbc_stream_io_ut;
typedef struct ___tbc_tty_s tbc_tty_st;
typedef struct ___tbc_tty_arru8_st tbc_tty_arru8_st;

#if defined(TBC_OPT_COMPACT_2)
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

/** tty dynamic array unsigned 8 bits */
struct ___tbc_tty_arru8_st {
    tbc_u8_t* ptr;
};

union ___tbc_stream_io_u {
    tbc_file_mt* file;
    tbc_file_mt* stream;
    tbc_func_ft lambda;
    tbc_tty_st* tty;
    tbc_tty_arru8_st arr;
    tbc_u8_t fid;
};

struct ___tbc_tty_s {
    tbc_stream_type_et type;
    tbc_stream_io_ut io;
};

union ___tbc_cin_u {
    tbc_tty_st tty_input;
    tbc_tty_st tty_source;
    tbc_tty_st tty_storage;
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
    tbc_tty_st tty_storage;
};

struct ___tbc_cout_s {
    tbc_tty_st tty_debug;
    tbc_tty_st tty_output;
    tbc_tty_st tty_keylog;
    tbc_tty_st tty_error;
};

#endif