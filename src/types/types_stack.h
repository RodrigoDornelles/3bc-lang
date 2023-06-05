#ifndef H_TYPES_STACK_TBC
#define H_TYPES_STACK_TBC

/**
 * @brief VM basic program struct
 * @note for @b minimal-stack
 */
struct ___tbc_stack_basic_prog_s {
    /**
     * @brief program counter
     */
    tbc_u16_t index;
    /**
     * @brief program lenght
     */
    tbc_u16_t size;
};

/**
 * @brief VM stack brute
 */
struct ___tbc_stack_raw_s {
    /**
     * @brief raw pointer to stack
     * @pre first byte must be a @b size of buffer
     * @pre the minimal @b size is a 8 bytes. 
     * @pre the maximum @b size is a 255 bytes. 
     */
    tbc_u8_t* buffer;
};

/**
 * @brief VM stack access
 */
struct ___tbc_stack_mem_s {
    /** 
     * @brief stack tail
     * @details define a stack size
     */
    tbc_u8_t st;
    /**
     * @brief stack pointer
     * @details define stack used
     */
    tbc_u8_t sp;
    /**
     * @brief stack data
     * @details storage of stack
     */
    tbc_u8_t data[];
};

/**
 * @brief VM initial configs in the stack
 */
struct ___tbc_stack_cfg_s {
    /**
     * @attention not use @b ___pad0;
     */
    void* ___pad0;
    /**
     * @brief program memory config
     * @details for counting and reading
     * @pre first field must be @b index with 16 bits.
     */
    void* prog;
    /**
     * @brief heap memory config
     * @details basically ram
     * @pre first field must be @b index with 16 bits.
     * @pre second field must be @b size with 16 bits.
     */
    void* heap;
    /**
     * @brief label memory config
     * @details for conditional jumps and procedures.
     */
    void* interpreter;
};

/**
 * @brief VM initial configs in the stack
 * @note for @b minimal-stack
 */
struct ___tbc_stack_cfgmin_s {
    /**
     * @brief alignment
     * @attention not use @b ___pad0;
     */
    void* ___pad0;
    /**
     * @brief program memory config
     * @details for counting and reading
     * @note @c prog points to @c @prog_index and @c prog_size 
     * when @b minimal-stack configuration is activated.
     */
    struct ___tbc_stack_basic_prog_s* prog;
    /**
     * @brief program counter
     * @note @c prog_index is used in @b minimal-stack
     */
    tbc_u16_t prog_index;
    /**
     * @brief program length
     * @note @c prog_size is used in @b minimal-stack
     */
    tbc_u16_t prog_size;
};

/**
 * @brief VM stack
 */
union ___tbc_stack_root_u {
    /**
     * @brief configuration
     */
    struct ___tbc_stack_cfg_s cfg;
    /**
     * @brief rawpointer stack
     */
    struct ___tbc_stack_raw_s raw;
    /**
     * @brief friendly stack access
     */
    struct ___tbc_stack_mem_s* mem;
    /**
     * @brief configuration when @b stack-minimal
     * @note force union size to @b (3pointers+32bits)
     */
    struct ___tbc_stack_cfgmin_s cfgmin;
};

#endif
