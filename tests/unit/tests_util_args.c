#include <assert.h>
#include <string.h>
#include "util_args.h"

int main()
{
    /** Test case 0: without args */
    {
        assert(util_args_has(0, NULL, 'a') == NULL);
        assert(util_args_has(0, NULL, 'b') == NULL);
        assert(util_args_has(0, NULL, 'c') == NULL);
        assert(util_args_has(0, NULL, 'd') == NULL);
        assert(util_args_param(0, NULL, NULL, 0) == NULL);
    }
    /** Test case 1: empty args */
    {
        char* argv[] = {"program_name"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        char ignore_keys[] = "x";
        assert(util_args_has(argc, argv, 'x') == NULL);
        assert(util_args_get(argc, argv, 'x') == NULL);
        assert(util_args_param(argc, argv, NULL, 0) == NULL);
        assert(util_args_param(argc, argv, ignore_keys, 0) == NULL);
    }
    /** Test case 3: util_args_has */
    {
        char* argv[] = {"program_name", "-a", "-b", "-c"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        assert(util_args_has(argc, argv, 'a') != NULL);
        assert(util_args_has(argc, argv, 'b') != NULL);
        assert(util_args_has(argc, argv, 'c') != NULL);
        assert(util_args_has(argc, argv, 'd') == NULL);
    }
    /** Test case 4: util_args_get */
    {
        char* argv[] = {"program_name", "-a", "value_a", "-b", "-c", "value_c", "-d"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        assert(strcmp(util_args_get(argc, argv, 'a'), "value_a") == 0);
        assert(util_args_get(argc, argv, 'b') == NULL);
        assert(strcmp(util_args_get(argc, argv, 'c'), "value_c") == 0);
        assert(util_args_get(argc, argv, 'd') == NULL);
        assert(util_args_get(argc, argv, 'e') == NULL);
    }
    /** Test case 6: Null ignore_keys in util_args_param */
    {
        char* argv[] = {"program_name", "param1", "param2"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        assert(strcmp(util_args_param(argc, argv, NULL, 0), "param1") == 0);
        assert(strcmp(util_args_param(argc, argv, NULL, 1), "param2") == 0);
        assert(util_args_param(argc, argv, NULL, 2) == NULL);
    }
    /** Test case 6: Empty ignore_keys in util_args_param */
    {
        char* argv[] = {"program_name", "param1", "param2"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        char ignore_keys[] = "";
        assert(strcmp(util_args_param(argc, argv, ignore_keys, 0), "param1") == 0);
        assert(strcmp(util_args_param(argc, argv, ignore_keys, 1), "param2") == 0);
        assert(util_args_param(argc, argv, ignore_keys, 2) == NULL);
    }
    /** Test case 7: Ignoring multiple keys in util_args_param */
    {
        char* argv[] = {"program_name", "-a", "value_a", "-b", "value_b", "param1", "param2"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        char ignore_keys[] = "ab";
        assert(strcmp(util_args_param(argc, argv, ignore_keys, 0), "param1") == 0);
        assert(strcmp(util_args_param(argc, argv, ignore_keys, 1), "param2") == 0);
        assert(util_args_param(argc, argv, ignore_keys, 2) == NULL);
    }
    return 0;
}
