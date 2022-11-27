#ifndef H_TYPES_PKG_TBC
#define H_TYPES_PKG_TBC

typedef struct ___tbc_pkg_prog_s tbc_pkg_prog_st;
typedef struct ___tbc_pkg_std_s tbc_pkg_std_st;
typedef struct ___tbc_pkg_s tbc_pkg_st;

struct ___tbc_pkg_prog_s {
    void (*load)(tbc_app_st *const);
    void (*next)(tbc_app_st *const);
    void (*clean)(tbc_app_st *const);
    void (*insert)(tbc_app_st *const);
};

struct ___tbc_pkg_std_s {
    void (*put)(tbc_app_st *const, tbc_u8_t, const char*);
};

struct ___tbc_pkg_s {
    tbc_pkg_prog_st prog;
    tbc_pkg_std_st std;
};

#endif
