#ifndef H_TYPES_STACK_TBC
#define H_TYPES_STACK_TBC

struct ___tbc_stack_basic_struct_s {
    /**
     * @brief counter
     * @details struct for @c heap and @c prog when minimal stack
     */
    tbc_u16_t index;
};

struct ___tbc_stack_raw_s {
    /**
     * @brief raw pointer to stack
     * @pre first byte must be a @b size of buffer
     * @pre the minimal @b size is a 8 bytes. 
     */
    tbc_u8_t* buffer;
};

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
     */
    void* heap;
    /**
     * @brief label memory config
     * @details for conditional jumps and procedures
     * @note when using minimal stack this space is used
     * to storage @c prog and @c heap
     */
    void* interpreter;
};

struct ___tbc_stack_cfgmin_s {
    /**
     * @attention not use @b ___pad0;
     */
    void* ___pad0;
    /**
     * @brief program memory config
     * @details for counting and reading
     * @note only field index
     */
    struct ___tbc_stack_basic_struct_s prog;
    /**
     * @brief heap memory config
     * @details basically ram
     * @note only field index
     */    
    struct ___tbc_stack_basic_struct_s mem;
    /**
     * @brief force 32 bits
     * @attention not use @b ___pad4;
     */
    tbc_u8_t ___pad1[4];
};

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
