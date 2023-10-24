#include <assert.h>
#include "util/util_dsl.h"

static tbc_keyword_st keywords[] = {
    {"aldo", 2}, {"erdb", 3}, {"rona", 1}, {"socc", 2}
};
static const int kn = sizeof(keywords)/sizeof(tbc_keyword_st);

int main()
{
    {
        char key[] = "aldo";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 0);
        assert(keywords[index].value == 2);
    }
    {
        char key[] = "erdb";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 1);
        assert(keywords[index].value == 3);
    }
    {
        char key[] = "rona";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 2);
        assert(keywords[index].value == 1);
    }
    {
        char key[] = "socc";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 3);
        assert(keywords[index].value == 2);
    }
    {
        char key[] = "ALDO";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 0);
        assert(keywords[index].value == 2);
    }
    {
        char key[] = "ERDB";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 1);
        assert(keywords[index].value == 3);
    }
    {
        char key[] = "RONA";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 2);
        assert(keywords[index].value == 1);
    }
    {
        char key[] = "SOCC";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == 3);
        assert(keywords[index].value == 2);
    }
    return 0;
}