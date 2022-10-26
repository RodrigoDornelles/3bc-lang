#ifndef H_FUNC_TYPES_TBC
#define H_FUNC_TYPES_TBC

typedef union ___tbc_func_u tbc_func_ft;

union ___tbc_func_u {
    /** any pointer **/
    void* ptr;
    /** void func(char*) **/
    void (*func_pstr_rv)(char*);
};

#endif
