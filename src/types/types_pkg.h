#ifndef H_TYPES_PKG_TBC
#define H_TYPES_PKG_TBC

#include "3bc_types.h"

typedef struct ___tbc_pkg_s tbc_pkg_st;

struct ___tbc_pkg_prog_s {
    void (*load)(tbc_app_st *const);
    void (*next)(tbc_app_st *const);
    void (*clean)(tbc_app_st *const);
    void (*insert)(tbc_app_st *const);
    void (*expand)(tbc_app_st *const);
    void (*avaliable)(tbc_app_st *const);
};

struct ___tbc_pkg_io_s {
    void (*write)(tbc_app_st *const);
};

struct ___tbc_pkg_ram_s {
    void (*read)(tbc_app_st *const);
    void (*write)(tbc_app_st *const);
};

struct ___tbc_pkg_s {
    struct ___tbc_pkg_prog_s prog;
    struct ___tbc_pkg_io_s io;
    struct ___tbc_pkg_ram_s ram;
};

#endif
