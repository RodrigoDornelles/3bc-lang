#include "3bc.h"
#include "lang/lang_3bc_put.h"

int main()
{
    static struct app_3bc_s instance;
    lang_3bc_put(&instance, 'i');
#if defined(TBC_FREEZE_STOPPED)
    while(1);
#endif
    return 0;
}
