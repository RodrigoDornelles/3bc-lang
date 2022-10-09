/**
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * DESCRIPTION:
 * Code refers to input and outputs texts or buffers in teletype terminals.
 *
 * BRIEF:
 * Low-level language, tiny virtual machine, intermediate representation,
 * embeddable, easy for beginners. (Friendly Punched cards)
 *
 * AUTHOR:
 * Copyright (C) 2020 Rodrigo Dornelles.
 *
 * LICENSE:
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * JOKE:
 * _\|/_ weedend alert! _\|/_
 * this code was written in a 4:20 mode.
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_USE_POSIX)
struct termios term_old_attr;
struct termios term_new_attr;
#endif

void driver_tty_init()
{
#if defined(TBC_USE_POSIX)
    /**
     * Turn possible terminal uncannonical mode
     * without conio.h in linux/unix builds
     */
    tcgetattr(0, &term_old_attr);
    tcgetattr(0, &term_new_attr);

    term_new_attr.c_lflag &= ~ICANON;
    term_new_attr.c_lflag &= ~ECHO;

    term_new_attr.c_cc[VTIME] = 0;
    term_new_attr.c_cc[VMIN] = 1;
#endif
}

void driver_tty_exit()
{
#if defined(TBC_P_COMPUTER)
    /** clear buffers **/
    fflush(stderr);
    fflush(stdout);
#endif

#if defined(TBC_USE_POSIX)
    /** reset terminal to default mode (linux/unix) **/
    tcsetattr(STDIN_FILENO, TCSANOW, &term_old_attr);
#endif
}

/**
 * detect keyboard input
 *
 * TODO: More compatible tty
 */
data_3bc_t driver_tty_input(
    struct app_3bc_s* const app, struct tty_3bc_s tty, register_3bc_t type)
{
    signed int value;
    char c[2] = "\0";
    bool invalid;

    do {
        invalid = false;

/** capture input **/
#if defined(TBC_NOT_FILES)
        
#elif defined(TBC_P_COMPUTER_OLD)
        c[0] = cgetc();
#elif defined(TBC_USE_POSIX)
        tcsetattr(STDIN_FILENO, TCSANOW, &term_new_attr);
        c[0] = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &term_old_attr);
#elif defined(TBC_USE_CONIO)
        /** exclusive function of the conio.h library **/
        c[0] = getch();
#endif

        /** validate input **/
        switch (type) {
        case STRB:
            /** made boolean confirmation **/
            switch (c[0]) {
            /** pressed YES or TRUE **/
            case 'Y':
            case 'y':
            case '1':
                value = 1;
                break;
            /** pressed YES or FALSE **/
            case 'N':
            case 'n':
            case '0':
                value = 0;
                break;
            /** pressed incorrect option **/
            default:
                invalid |= true;
                break;
            }
            break;

        case STRC:
            /** verify is a ASCII alphabet's letter/symbol **/
            invalid |= (c[0] < 0x20 || c[0] > 0x7E);
            value = c[0];
            break;

        case STRI:
            /** verify is a decimal number and cast **/
            invalid |= (c[0] < 0x30 || c[0] > 0x39);
            value = (c[0] - '0');
            break;

        case STRO:
            /** verify is a octal number and cast **/
            invalid = (c[0] < 0x30 || c[0] > 0x37);
            value = (c[0] - '0');
            break;

        case STRX:
            /** add upcase bit **/
            c[0] |= 0x20;
            /** [0-9] casting hexadecimal**/
            if (c[0] >= 0x30 && c[0] <= 0x39) {
                value = (c[0] - '0');
                break;
            }
            /** [A-F] casting hexadecimal **/
            if (c[0] >= 0x61 && c[0] <= 0x66) {
                value = (c[0] - 'a' + 0xa);
                break;
            }
            /** verified that it is wrong! */
            invalid |= true;
            break;
        }
    } while (invalid);

    return (data_3bc_t)value;
}

/**
 * stream texts to outputs
 */
void driver_tty_output(struct app_3bc_s* const app, struct tty_3bc_s tty,
    register_3bc_t type, data_3bc_t val)
{
    /** the size of the buffer is according to the memory */
    char output[sizeof(data_3bc_t) * 8 + 1];

    /** print negative symbol **/
    if (val < 0 && type != STRC) {
        val = abs(val);
        driver_tty_output(app, tty, STRC, '-');
    }

    switch (type) {
    case STRB: {
#if defined(TBC_NOT_LOG2)
#warning "[3BC] UNSUPPORTED: STRB OUTPUT"
        driver_program_error(app, ERROR_UNSUPPORTED);
#else
        /**
         * C It doesn't have printing of numbers with binary base,
         * this is very very sad. makes me want to use java!
         */
        int logarithm = val ? log2(val) : 0;
        int pos = 0;

        do {
            /** concat bitwise to string in reverse order **/
            output[logarithm - pos] = '0' + ((val >> pos) & 1);
        } while (pos++ < logarithm);

        /** end of output **/
        output[pos] = '\0';
        break;
#endif
    }

    case STRC:
        snprintf(output, sizeof(output), "%c", val);
        break;

    case STRX:
        snprintf(output, sizeof(output), "%x", val);
        break;

    case STRI:
        snprintf(output, sizeof(output), "%d", val);
        break;

    case STRO:
        snprintf(output, sizeof(output), "%o", val);
        break;
    }

    driver_tty_output_raw(app, tty, output);
}

void driver_tty_output_raw(
    struct app_3bc_s* const app, struct tty_3bc_s tty, const char* string)
{
#if defined(_3BC_NUTTX) && !defined(TBC_NOT_FILES)
    /** fix stream flush on nuttx when repl|output **/
    if (tty.type == STREAM_TYPE_COMPUTER_STD) {
        fputs(string, tty.io.stream);
        fflush(tty.io.stream);
        return;
    }
#endif
#if defined(TBC_P_COMPUTER) && !defined(TBC_NOT_FILES)
    /** stream standard c output **/
    if (tty.type == STREAM_TYPE_COMPUTER_STD) {
        fputs(string, tty.io.stream);
        return;
    }
#endif
    if (tty.type == STREAM_TYPE_CLONE_TTY) {
        driver_tty_output_raw(app, *tty.io.tty, string);
    } else if (tty.type == STREAM_TYPE_FUNCTION_CALL) {
        tty.io.lambda((char*)string);
        return;
    } else if (tty.type == STREAM_TYPE_NONE) {
        driver_program_error(app, ERROR_NONE_TTY);
    }
}
