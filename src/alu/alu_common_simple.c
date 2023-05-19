#include "alu_common_simple.h"
#include "types_errors.h"

/**
 * @brief native cpu math
 * @details all logic and arithmeticthat is possible
 * to solve directly on the CPU or by the compiler itself
 * without implementing an algorithm from scratch.
 * @throw ERROR_NUMBER_ZERO
 * @throw ERROR_UNSUPPORTED
 */
void alu_common_simple(struct app_3bc_s* const self)
{
    switch(self->cache_l1.math - 10)
    {
        /** @b SUM: a + b **/
        case 1:
            self->cpu.ra = 
                self->cache_l2.i16[0] + self->cache_l2.i16[1];
            break;

        /** @b SUB: a - b **/
        case 2:
            self->cpu.ra = 
                self->cache_l2.i16[0] - self->cache_l2.i16[1];
            break;

        /** @b MUL: a * b **/
        case 3:
            self->cpu.ra = 
                self->cache_l2.i16[0] * self->cache_l2.i16[1];
            break;

        /** @b DIV: a * b **/
        case 4:
            if (self->cache_l2.i16[1] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra = 
                self->cache_l2.i16[0] / self->cache_l2.i16[1];
            break;

        /** @b MOD: a % b **/
        case 5:
            if (self->cache_l2.i16[1] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra = 
                self->cache_l2.i16[0] % self->cache_l2.i16[1];
            break;

        /** @b ABS: |a| **/
        case 7:
            self->cpu.ra = self->cache_l2.i16[0] < 0?
                -self->cache_l2.i16[0]: 
                self->cache_l2.i16[0];
            break;

        default:
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
    }
}