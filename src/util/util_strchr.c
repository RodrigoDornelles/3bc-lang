#include "types/types_null.h"
#include "util/util_strchr.h"

/**
 * @brief Locate the first occurrence of a character in a string.
 * @param[in] str The input string to search.
 * @param[in] character The character to locate.
 * @return Pointer to the first occurrence of the character in the string.
 * @retval NULL If the character is not found in the string.
 */
char* util_strchr(const char* str, int character)
{
    char* res = NULL;

    while (*str != '\0') {
        if (*str == character) {
            res = (char*) str;
            break;
        }
        str++;
    }
    
    if (character == '\0') {
        res = (char*) str;
    }
    
    return res;
}
