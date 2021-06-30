#include "3bc.h"

bool interpreter_tokens(struct tty_3bc_s tty, char** reg, char** mem, char** val)
{
    unsigned int columns = 0;
    char c;

    /** reset strings **/
    *reg = NULL;
    *mem = NULL;
    *val = NULL;

    /** read line **/
    do {
        /** scan character **/
        c = fgetc(tty.io.stream);

        /** skip comment **/
        if(c=='#'){
            for(;c!= '\n' && c != '\0'&& c !=- 1; c=fgetc(tty.io.stream));
        }

        /** skip spacing | end of file **/
        if (strchr("\t#;, ", c) != NULL || feof(tty.io.stream) || c == '\n') {
            continue;
        }

        /** create column **/
        {
            bool is_hash = false;
            bool is_char = false;
            bool is_scape = false;
            unsigned char lenght = 1;
            char* string = (char*) malloc(lenght * sizeof(char) + 1);
            string[0] = c;
            columns += 1;

            /** init char or hash **/
            is_char |= c == '\'' && !is_hash;
            is_hash |= c == '"' && !is_char;

            /** scan column string **/
            while ((c = fgetc(tty.io.stream)) != '\0'
                && c != '\n' && !feof(tty.io.stream)
                && (strchr("\t#; ,", c) == NULL || is_hash || is_char))
            {
                /** detect is scape **/
                is_scape = (is_hash || is_char) && c == '\\';

                /** expand string **/
                char* new_buffer = (char*) realloc(string, ++lenght * sizeof(char) + 1);
                
                /** insufficient memory to read a large line **/
                if (new_buffer == NULL) {
                    driver_program_error(ERROR_LONG_LINE);
                }

                /** add character **/
                string = new_buffer;
                string[lenght - 1] = c;
                string[lenght] = '\0';

                /** end of char or hash **/
                is_char = is_char && !is_scape && c != '\'';
                is_hash = is_hash && !is_scape && c != '"';
                is_scape = false;
            }

            /** write string in the column pointer reference **/
            switch (columns) 
            {
                case 1:
                    *reg = string;
                    break;

                case 2:
                    *mem = string;
                    break;

                case 3:
                    *val = string;
                    break;
            }
        } 
    }
    while (!feof(tty.io.stream) && c != '\0' && c != '\n' && strchr("#;", c) == NULL);

    /** validate number of columns **/
    return columns == 3 || columns == 0;
}