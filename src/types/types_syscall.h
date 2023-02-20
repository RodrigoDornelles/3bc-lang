#ifndef H_TYPES_SYSCALL_TBC
#define H_TYPES_SYSCALL_TBC

enum ___tbc_syscall_e {
    TBC_SYS_NONE = 0,
    TBC_SYS_MEM_READ = 1,
    TBC_SYS_MEM_WRITE = 2,
    TBC_SYS_IO_READ = 3,
    TBC_SYS_IO_WRITE = 4,
    TBC_SYS_WAIT = 5,
    TBC_SYS_END = 255
};

typedef enum ___tbc_syscall_e tbc_syscall_et;

#endif
