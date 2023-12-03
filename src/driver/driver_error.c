/**
 * @file src/driver/driver_error.c
 * @short guest driver error handler **source code**
 * @brief runtime error catch and report excepetions
 */
#define TBC_SOURCE_ENTRY
#include "driver/driver_error.h"
#include "i18n/i18n_0000.h"
#include "util/util_itos.h"

/** @todo */
#if defined(__NES__)
#define DESCRIPTION_FEED "\n"
#else
#define DESCRIPTION_FEED "\t"
#endif

static const char ___msg_err_1[] = "[3BC] CRITICAL ERROR ABORTED THE PROGRAM";
static const char ___msg_err_2[] = "\n> MACHINE ID:\t";
static const char ___msg_err_4[] = "\n> ERROR LINE:\t";
static const char ___msg_err_6[] = "\n> ERROR CODE:\t";
static const char ___msg_err_8[] = "\n> DESCRIPTION:"DESCRIPTION_FEED;
static const tbc_u8_t ___len_err_1 = (tbc_u8_t) (sizeof(___msg_err_1) * (-1));
static const tbc_u8_t ___len_err_2 = (tbc_u8_t) (sizeof(___msg_err_2) * (-1));
static const tbc_u8_t ___len_err_4 = (tbc_u8_t) (sizeof(___msg_err_4) * (-1));
static const tbc_u8_t ___len_err_6 = (tbc_u8_t) (sizeof(___msg_err_6) * (-1));
static const tbc_u8_t ___len_err_8 = (tbc_u8_t) (sizeof(___msg_err_8) * (-1));

/**
 * @startuml
 * (*) --> "Throw error"
 * --> "Print error (part 1..10)"
 * --> "Garbage Collector"
 * --> (*)
 * @enduml
 */
void driver_error(struct app_3bc_s* const self)
{
    do {
        if (TBC_RET_PRINT_ERROR_1 <= self->rc &&
            self->rc <= TBC_RET_PRINT_ERROR_F) {
            self->cache.l2.tty = &(self->cout.tty_output);
            self->rc = (tbc_return_et) (*((tbc_u8_t*) &self->rc) + 1);
        }

        if (self->rc == TBC_RET_CATCH_ERROR) {
            self->rc = TBC_RET_PRINT_ERROR_1;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_1) {
            self->cache.l3.buffer.storage = (char*) ___msg_err_1;
            self->cache.l3.buffer.size = ___len_err_1;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_2) {
            self->cache.l3.buffer.storage = (char*) ___msg_err_2;
            self->cache.l3.buffer.size = ___len_err_2;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_3) {
            self->cache.l3.fixbuf.size = 
                util_itos10(
                    self->cache.l3.fixbuf.storage,
                    &self->id,
                    sizeof(self->cache.l3.fixbuf.storage),
                    sizeof(self->id) * 8
                );
            break;
        }
        
        if (self->rc == TBC_RET_PRINT_ERROR_4) {
            self->cache.l3.buffer.storage = (char*) ___msg_err_4;
            self->cache.l3.buffer.size = ___len_err_4;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_5) {
            self->cache.l3.fixbuf.size = 
                util_itos10(
                    self->cache.l3.fixbuf.storage,
                    &self->stack.cfgmin.prog->index,
                    sizeof(self->cache.l3.fixbuf.storage),
                    sizeof(self->stack.cfgmin.prog->index) * 8
                );
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_6) {
            self->cache.l3.buffer.storage = (char*) ___msg_err_6;
            self->cache.l3.buffer.size = ___len_err_6;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_7) {
            self->cache.l3.fixbuf.size = 
                util_itos10(
                    self->cache.l3.fixbuf.storage,
                    &self->cache.l1.error,
                    sizeof(self->cache.l3.fixbuf.storage),
                    sizeof(self->cache.l1.error) * 8
                );
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_8) {
            self->cache.l3.buffer.storage = (char*) ___msg_err_8;
            self->cache.l3.buffer.size = ___len_err_8;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_9) {
            if (self->cache.l1.error >= tbc_i18n_error_len) {
                self->cache.l1.error = ERROR_UNKNOWN;
            }
            self->cache.l3.buffer.size =
                -tbc_i18n_error_arr[self->cache.l1.error].len;
            self->cache.l3.buffer.storage = (char*)
                tbc_i18n_error_arr[self->cache.l1.error].ptr;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_A) {
            self->cache.l3.fixbuf.size = 1;
            self->cache.l3.fixbuf.storage[0] = '\n';
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_B) {
            self->rc = TBC_RET_GC_LV3;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}
