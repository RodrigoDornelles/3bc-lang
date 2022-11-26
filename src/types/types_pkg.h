#ifndef H_TYPES_PKG_TBC
#define H_TYPES_PKG_TBC

typedef struct __tbc_pkg_prog_s tbc_pkg_prog_st;
typedef struct __tbc_pkg_s tbc_pkg_st;

struct __tbc_pkg_prog_s {
    void (*load)(tbc_app_st *const);
    void (*next)(tbc_app_st *const);
    void (*clean)(tbc_app_st *const);
    void (*insert)(tbc_app_st *const);
};

struct __tbc_pkg_s {
    tbc_pkg_prog_st prog;
};

#endif
