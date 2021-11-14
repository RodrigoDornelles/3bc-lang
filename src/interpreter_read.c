#include "3bc.h"

#if defined(_3BC_DISABLE_INTERPRETER)
int interpreter_read(app_3bc_t app)
{
    return EOF;
}
#else
int interpreter_read(app_3bc_t app)
{  
    char character = fgetc(app->tty_source.io.stream);

    /** end of file **/
    if (character == EOF || feof(app->tty_source.io.stream)) {
        return EOF;
    }

    /** end of line **/
    if(strchr("#;,\n", character) != NULL || character == '\0') {
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
        {
            app->program.last_line += 1;
            interpreter_compiler(app, app->cache_l3.buffer);
        }

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
#endif