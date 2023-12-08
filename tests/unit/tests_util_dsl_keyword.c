#include <assert.h>
#include "util/util_dsl.h"

static const char keywords[] = "aldo" "erdb" "rona" "socc";
static const int kn = sizeof(keywords)/4;

int main()
{
    {
        char key[] = "aldo";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 0);
    }
    {
        char key[] = "erdb";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 1);
    }
    {
        char key[] = "rona";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 2);
    }
    {
        char key[] = "socc";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 3);
    }
    {
        char key[] = "ALDO";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 0);
    }
    {
        char key[] = "ERDB";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 1);
    }
    {
        char key[] = "RONA";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 2);
    }
    {
        char key[] = "SOCC";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 3);
    }
    return 0;
}