Code standard
=============

code security
--------------

required safety codes.

 * use xor zeoirze `var ^= var` to reset a value in place of assignment `var = 0` in all cases 
    * except NULL pointers.
    * this counts as **code optimization** compliance as well.

 * any allocated dynamic memory must be checked to see if it succeeded.
    * it would be better not to use dynamic memory to comply with **MISRA** standards.

    ```c
    unsigned char* buffer = (unsigned char*) malloc(128);
    memset(src, 0, 128);
    /* incorrect pattern! */
    ```

    ```c
    unsigned char* buffer = (unsigned char*) malloc(128);
    if (buffer != NULL) {
        memset(src, 0, 128);
    }
    /* correct pattern! */
    ```

code compatibility
------------------

compatibility requirements between **ANSI C** and modern **C++** compilers.

 * declare variables only at the beginning of the body of scopes.
    * when the variable occupies more than 1 byte, make sure you need it on the stack, prefer to use heap shared memory (cache_l1, cache_l2...) or global static memory.
        * global static memory is only allowed when you are on hardware that does not support multiple virtual machines at the same time.
    * loose scopes are allowed!
        * hint, you can use scope to separate the code steps well and save your stack consciously.

    ```c
    void func0()
    {
        unsigned char a = func1();
        func2(a);
        unsigned char b = func3();
        func4(b);
        /* incorrect pattern! */
    }
    ```

    ```c
    void func0()
    {
        unsigned char a;
        unsigned char b;
        a = func1();
        func2(a);
        b = func3();
        func4(b);
        /* correct pattern! */
    }
    ```

    ```c
    void func0()
    {
        unsigned char a = func1();
        func2(a);
        {
            unsigned char b = func3();
            func4(b);
        }
        /* correct pattern! */
    }
    ```

 * all masks must use a hexadecimal base, and have documentation for each of its bits.
    * binary base is strictly prohibited as it is not a POSIX standard.

    ```c
    while (thing | 0b100) {
        func();
    }
    /* incorrect pattern! */
    ```

    ```c
    /**
        * @brief wait until **another thing** else is done.
        * @li bit 0 - thing 
        * @li bit 1 - other thing
        * @li bit 2 - another thing
        * @c 0b100
        */
    while (thing | 0x4) {
        func();
    }
    /* correct pattern! */
    ```

 * `void*` are prohibited, for reasons of compatibility with C++ compilers.
    * hint you can use the @ref tbc_func_ft type to receive function pointers.
    * basically use casting whenever you get anypointer.

    ```c
    unsigned char* buffer = malloc(128);
    /* incorrect pattern! */
    ```

    ```c
    unsigned char* buffer = (unsigned char*) malloc(128);
    /* correct pattern! */
    ```

code optimize
-------------

Essential optimizations to improve runtime.
    
 * use prefix increment `++i` instead of suffix increment `i++` in all cases.
    * sometimes the compiler may not have frontend optimizations. [cc65](https://cc65.github.io/doc/coding.html#s9)
 * create _pipelines_ and _state machines_ whenever you can to decreasing stack depth.

code coverage
-------------

implementations prohibited due to impediment to coverage analysis.

 * Ternary operators `?:`, are also ugly.

    ```c
    int foo = bar? x: y;
    /* incorrect pattern! */
    ```

    ```c
    int foo;

    if(bar) {
        foo = x;
    } else {
        foo = y;
    }
    /* correct pattern! */
    ```

 * branch loop `for` for being confusing with prefix assignments operators, and it's better to separate things.

    ```c
    for (int i; i < j; i++) {
        func();
    }
    /* incorrect pattern! */
    ```

    ```c
    int i;

    while(i < j)
    {
        func();
        ++i;
    }
    /* correct pattern! */
    ```
    
 * branch conditionals `||` (byte or) is forbidden terminating within `if`, please consider making a negation following the example below.

    ```c
    if (cond1 || cond2) {
        func();
    }
    /* incorrect pattern! */
    ```

    ```c
    do {
        if (!cond1) {
            break;
        }

        if (!cond2) {
            break;
        }

        func();
    }
    while(0);
    /* correct pattern! */
    ```
