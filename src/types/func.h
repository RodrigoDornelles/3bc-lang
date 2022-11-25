#ifndef H_FUNC_TYPES_TBC
#define H_FUNC_TYPES_TBC

typedef union ___tbc_func_u tbc_func_ft;

union ___tbc_func_u {
    /** any pointer **/
    void* ptr;
    /** void func(char*) **/
    void (*func_pstr_rv)(char*);
    /** bool func(uint8_t, uint8_t, uint8_t) **/
    bool (*func_p8u_p8u_p8u_rb)(tbc_uint8_t, tbc_uint8_t, tbc_uint8_t);
};

#endif
