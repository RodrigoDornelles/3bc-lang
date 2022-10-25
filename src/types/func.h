#ifndef H_FUNC_TYPES_TBC
#define H_FUNC_TYPES_TBC

typedef ___tbc_func_u tbc_func_ft;

union ___tbc_func_u {
    /** any pointer **/
    void* anyptr;
    /** void func(char*) **/
    void (*tbc_pstr_rvoid_f)(char*);
};

#endif