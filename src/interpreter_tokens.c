#include "3bc.h"

#if !defined(_3BC_DISABLE_INTERPRETER)

bool interpreter_tokens(char* line, char** reg, char** mem, char** val)
{
    unsigned char columns = 0;
    char* pointer = line;

    /** reset strings **/
    *reg = NULL;
    *mem = NULL;
    *val = NULL;

   do {
        /** search for the beginning of the column **/ 
        for (;strchr("\t. ", *pointer) != NULL && pointer[0] != '\0'; pointer++);

        /** skip comments **/
        if(strchr("#;", *pointer) != NULL){
            for(;pointer[0] != '\n' && pointer[0] != '\0' && pointer[0] != EOF; pointer++);
            break;
        }

        /** end of line **/
        if (pointer[0] == '\0') {
            break;
        }

        /** insert columun **/
        switch (++columns)
        {
            case 1:
                *reg = pointer;
                break;

            case 2:
                *mem = pointer;
                break;

            case 3:
                *val = pointer;
                break;
        }

        /** skip literal char **/
        if (pointer[0] == '\'') {
            do {
                pointer++;
                if (pointer[0] == '\\') {
                    pointer++;
                }
            }
            while(pointer[0] != '\'' && pointer[0] != '\0');
        }

        /** skip other literals **/
        for (;strchr("\t. ", *pointer) == NULL && pointer[0] != '\0'; pointer++);

        /** mark end of column **/
        if (pointer[0] != '\0') {
            pointer[0] = '\0';
            pointer++;
        }
    }
    while (pointer[0] != '\0');

    /** validate number of columns **/
    return columns == 3 || columns == 0;
}

#endif
