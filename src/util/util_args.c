#include "util_args.h"
#include "types/types_null.h"

/**
 * @brief verify if exist a flag
 * @details can be use has @c -h or @c -v for help or version.
 * @param[in] argc number of arguments
 * @param[in] argv array of arguments
 * @param[in] key single char flag
 * @return pointer to argument
 * @retval NULL when not found
 * @startebnf
 * single_flag                                                                \
 *  = "-"                                                                     \
 *  , "a-zA-Z" (* any key *)                                                  \
 *  ;
 * @endebnf
 */
char* util_args_has(int argc, char** argv, char key) {
    char* ret = NULL;
    int i = 1;
    
    if (argc > 1 && argv != NULL) {
        while (i < argc) {
            if (argv[i][0] == '-' && argv[i][1] == key) {
                ret = argv[i];
                break;
            }
            ++i;
        }
    }

    return ret;
}

/**
 * @brief get value of a compound flag
 * @details can be use has @c -o @c value for ouput some file.
 * @param[in] argc number of arguments
 * @param[in] argv array of arguments
 * @param[in] key single char flag
 * @return pointer to argument
 * @retval NULL when not found
 * @startebnf
 * composite_flag                                                             \
 *  = "-"                                                                     \
 *  , "a-zA-Z" (* any key *)                                                  \
 *  , text (* cannot start with "-" *)                                        \
 *  ;
 * @endebnf
 */
char* util_args_get(int argc, char** argv, char key) {
    char* ret = NULL;
    int i = 1;

    if (argc > 1 && argv != NULL) {
        while (i < (argc - 1)) {
            if (argv[i][0] == '-' && argv[i][1] == key && argv[i + 1][0] != '-') {
                ret = argv[i + 1];
                break;
            }
            ++i;
        }
    }

    return ret;
}

/**
 * @brief get a ordered param
 * @see take care when using @ref util_args_get
 * @param[in] argc number of arguments
 * @param[in] argv array of arguments
 * @param[in] ignore_keys a list of compound flags to ignore
 * @param[in] param_pos position of parameter started by 0
 * @return pointer to argument
 * @retval NULL when not found
 */
char* util_args_param(int argc, char** argv, char* ignore_keys, int param_pos) {
    char* ret = NULL;
    int pos = 0;
    int i = 1;
    int j = 0;

    if (argc > 1 && argv != NULL) {
        /* i!=0 prevent infinity loop (overflow) */
        while (i != 0 && i < argc) {
            if (argv[i][0] == '-' && ignore_keys != NULL) {
                j = 0;
                while(ignore_keys[j] != '\0') {
                    if (ignore_keys[j] == argv[i][1]) {
                        ++i;
                        break;
                    }
                    ++j;
                }
                ++i;
                continue;
            }

            if (param_pos == pos) {
                ret = argv[i];
                break;
            }

            ++pos;
            ++i;
        }
    }

    return ret;
}
