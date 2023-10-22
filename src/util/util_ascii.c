#include "util_ascii.h"

char util_ascii(const char* const str, unsigned char size)
{
    /** @li NACK */
    char res = 0x15;

    do {
        if (str[0] != '\'') {
            break;
        }
        if (str[1] == '\\'){
            if (size <= 3) {
                break;
            }
            if (str[3] != '\'') {
                break;
            }
            /** @li NULL */
            if (str[2] == '0') {
                res = 0x00;
            }
            /** @li BELL */
            if (str[2] == 'a') {
                res = 0x07;
            }
            /** @li HT */
            if (str[2] == 't') {
                res = 0x09;
            }
            /** @li LF */
            if (str[2] == 'n') {
                res = 0x0A;
            }
            /** @li CR */
            if (str[2] == 'r') {
                res = 0x0D;
            }
            break;
        }
        if (str[2] != '\'') {
            break;
        }
        res = str[1];
    }
    while(0);

    if ((unsigned char) res >= (unsigned char) 0x80u) {
        res = 0x15;
    }

    return res;
}
