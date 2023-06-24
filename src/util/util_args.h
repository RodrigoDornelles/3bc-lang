#ifndef H_UTIL_ARGS_TBC
#define H_UTIL_ARGS_TBC

char* util_args_has(int argc, char** argv, char key);
char* util_args_get(int argc, char** argv, char key);
char* util_args_param(int argc, char** argv, char* ignore_keys, int param_pos);

#endif
