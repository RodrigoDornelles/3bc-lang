#include <assert.h>
#include "types/types_null.h"
#include "util/util_dsl.h"

static const char keywords[] = "aldo" "erdb" "rona" "socc";
static const int kn = sizeof(keywords);

int main()
{
    {
        int index = util_dsl_keyword(NULL, keywords, kn);
        assert(index == -2);
    }
    {
        char key[] = "aldo";
        int index = util_dsl_keyword(key, NULL, kn);
        assert(index == -2);
    }
    {
        char key[] = "rona";
        int index = util_dsl_keyword(key, keywords, 0);
        assert(index == -2);
    }
    {
        char key[] = "ball";
        int index = util_dsl_keyword(key, keywords, kn);
        assert(index == -1);
    }
    return 0;
}