#include "3bc.h"

bool interpreter_tokens(file_t* stream, char** reg, char** mem, char** val)
{
    unsigned int columns = 0;
    char c;

    /** read line **/
    do {
        /** scan character **/
        c = fgetc(stream);

        /** skip spacing | end of file **/
        if (strchr("\t#;, ", c) != NULL || feof(stream)) {
            continue;
        }
        
        /** create column **/
        {
            unsigned char lenght = 1;
            char* string = malloc(lenght * sizeof(char) + 1);
            string[0] = c;
            columns += 1;

            /** scan column string **/
            while ((c = fgetc(stream)) != '\0'
                && c != '\n' && !feof(stream)
                && strchr("\t#;, ", c) == NULL)
            {
                string = realloc(string, ++lenght * sizeof(char) + 1);
                string[lenght - 1] = c;
                string[lenght] = '\0';
            }

            /** reference string to column pointer **/
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
    while (!feof(stream) && c != '\0' && c != '\n' && strchr("#;", c) == NULL);

    /** validate number of columns **/
    return columns == 3 || columns == 0;
}