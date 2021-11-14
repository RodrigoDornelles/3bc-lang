#include "3bc.h"

#if !defined(_3BC_DISABLE_INTERPRETER)
/**
 *  Default entry point to the interpreter, works asynchronously.
 *
 * RETURN: EOF if there is nothing else to read.
 * RETURN: 1 if the interpretation was successful.
 */
int interpreter_read(app_3bc_t app)
{  
    char character = fgetc(app->tty_source.io.stream);

    /** end of file **/
    if (character == EOF && app->cache_l3.buffer == NULL) {
        return EOF;
    }

    /** end of line **/
    if(character == '\n' || character == '\0' || character == EOF) {
        /** mark end of string **/
        {
            char* new_buffer = (char*) realloc(app->cache_l3.buffer, sizeof(char) * (++app->cache_l3.size));   
            if (new_buffer == NULL) {
                driver_program_error(ERROR_OUT_OF_MEMORY);
            }
            app->cache_l3.buffer = new_buffer;
            app->cache_l3.buffer[app->cache_l3.size - 1] = '\0';
        }

        /** insert to vm **/
        char* line = app->cache_l3.buffer;
        do {
            app->program.last_line += 1;
            line = interpreter_compiler(app, line);
        }
        while (line != NULL);

        /** reset buffer **/
        {
            free(app->cache_l3.buffer);
            app->cache_l3.buffer = NULL;
            app->cache_l3.size = 0;
        }

        return 1;
    }

    /** expand the  buffer **/
    {
        char* new_buffer = (char*) realloc(app->cache_l3.buffer, sizeof(char) * (++app->cache_l3.size));
            
        if (new_buffer == NULL) {
            driver_program_error(ERROR_OUT_OF_MEMORY);
        }
        
        app->cache_l3.buffer = new_buffer;
        app->cache_l3.buffer[app->cache_l3.size - 1] = character;
    }

    return 0;
}

#else
/**
 * Disable interpreter, returns whenever there is nothing to read.
 */
int interpreter_read(app_3bc_t app)
{
    return EOF;
}
#endif
