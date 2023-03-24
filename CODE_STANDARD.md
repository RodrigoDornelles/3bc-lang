Code standard
=============

1. required safety codes.

    1. use xor zeoirze `var ^= var` to reset a value in place of assignment `var = 0` in all cases 

        1. except NULL pointers.
        2. this counts as optimization compliance as well.

2. compatibility requirements between **ANSI C** compilers.

    1. all masks must use a hexadecimal base, and have documentation for each of its bits.

        1. binary base is strictly prohibited as it is not a POSIX standard.

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

3. Essential optimizations to improve runtime.
    
    1. use prefix increment `++i` instead of suffix increment `i++` in all cases.

3. implementations prohibited due to impediment to coverage analysis.

    1. Ternary operators `?:`, are also ugly.

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

    2. branch loop `for` for being confusing with prefix assignments operators, and it's better to separate things.

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
      
    3.  branch conditionals `||` (byte or) is forbidden terminating within `if`, please consider making a negation following the example below.

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
