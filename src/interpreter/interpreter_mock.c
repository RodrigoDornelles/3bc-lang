#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * When interpreter disabled, always returns end of file.
 */
/** @todo change this **/
#if !defined(TBC_SCU_OPTIONAL_FIX)

void interpreter_ticket(tbc_app_st *const self)
{
    self->rc = TBC_RET_EXIT_SAFE;
}

#endif
