#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)
/**
 * JOKE: rest in peace spaghetti code, I won't miss you.
 */
#if !defined(TBC_INTERPRETER)
/**
 * When interpreter disabled, always returns end of file.
 */
int interpreter_ticket(struct app_3bc_s* const app)
{
    return EOF;
}
#else
/**
 * Default entry point to the interpreter, works asynchronously.
 *
 * RETURN: EOF if there is nothing else to read.
 * RETURN: 1 if the interpretation was successful.
 */
int interpreter_ticket(struct app_3bc_s* const app)
{
    int character = fgetc(app->tty_source.io.stream);

#if defined(_3BC_NUTTX)
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_STD) {
        driver_tty_output(app, app->tty_keylog, STRC, character);
    }
#endif

    /** end of file **/
    if (character == EOF && app->cache_l3.buffer.storage == NULL) {
        return EOF;
    }

    /** end of line **/
    if (character == '\n' || character == '\r' || character == '\0'
        || character == EOF) {
/** REPL nuttx compatibily **/
#if defined(_3BC_NUTTX)
        if (app->tty_source.type == STREAM_TYPE_COMPUTER_STD) {
            driver_tty_output(app, app->tty_keylog, STRC, '\n');
        }
#endif

        /** mark end of string **/
        {
            char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
                sizeof(char) * (++app->cache_l3.buffer.size));
            if (new_buffer == NULL) {
                driver_program_error(app, ERROR_OUT_OF_MEMORY);
            }
            app->cache_l3.buffer.storage = new_buffer;
            app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = '\0';
        }

        /** insert to vm **/
        char* line = app->cache_l3.buffer.storage;
        do {
            app->program.last_line += 1;
            line = interpreter_readln(app, line);
        } while (line != NULL);

        /** reset buffer **/
        {
            free(app->cache_l3.buffer.storage);
            app->cache_l3.buffer.storage = NULL;
            app->cache_l3.buffer.size = 0;
        }

        return 1;
    }

    /** expand the  buffer **/
    {
        char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
            sizeof(char) * (++app->cache_l3.buffer.size));

        if (new_buffer == NULL) {
            driver_program_error(app, ERROR_OUT_OF_MEMORY);
        }

        app->cache_l3.buffer.storage = new_buffer;
        app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = character;
    }

    return 0;
}
#endif
#endif
