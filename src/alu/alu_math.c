#include "3bc_detect.h"
#include "alu_math.h"
#include "types/types_errors.h"

#if !defined(TBC_NOT_MATH)
#include <math.h>
#endif

/**
 * @brief native host cpu math
 *
 * @details all logic and arithmeticthat is possible
 * to solve directly on the CPU or by the compiler itself
 * without implementing an algorithm from scratch.
 *
 * @throw ERROR_NUMBER_ZERO
 * @throw ERROR_UNSUPPORTED
 *
 * @details
 * ID | Math Name          | Math Formula              | Math Code (ANSI C) 
 * -- |------------------- | ------------------------- | ------------------
 * 01 | Mul Add (base 2)   | @f$(a \ll 1) + b@f$       | (a<<1)+b
 * 02 | Mul Add (base 8)   | @f$(a \ll 3) + b@f$       | (a<<3)+b
 * 03 | Mul Add (base 10)  | @f$(a \times 10) + b@f$   | (a*10)+b
 * 04 | Mul Add (base 16)  | @f$(a \ll 4) + b@f$       | (a<<4)+b
 * 11 | Addition           | @f$a + b@f$               | a+b
 * 12 | Subtraction        | @f$a - b@f$               | a-b
 * 13 | Multiplication     | @f$a \times b@f$          | a*b
 * 14 | Division           | @f$\frac{a}{b}@f$         | a/b
 * 15 | Modulo             | @f$a \mod b@f$            | a%b
 * 16 | Exponentiation     | @f$a^b@f$                 | pow(a,b)
 * 17 | Nth Root           | @f$\sqrt[b]{a}@f$         | pow(a,1/b)
 * 18 | Absolute Value     | @f$\|a\|@f$               | abs(a)
 * 19 | Multiplication Add | use 1, 2, 3 or 4          ||
 * 21 | Bitwise NOT        | @f$\sim a@f$              | ~a
 * 22 | Bitwise AND        | @f$a \& b@f$              | a&b
 * 23 | Bitwise OR         | @f$a \mid b@f$            | a\|b
 * 24 | Bitwise XOR        | @f$a \oplus b@f$          | a^b
 * 25 | Bitwise NAND       | @f$\overline{(a \cdot b)}@f$  | ~(a&b)
 * 26 | Bitwise NOR        | @f$\overline{(a + b)}@f$      | ~(a\|b)
 * 27 | Bitwise XNOR       | @f$\overline{(a \oplus b)}@f$ | ~(a^b)
 * 28 | Bitwise Left Shift | @f$a \ll b@f$             | a<<b
 * 29 | Bitwise Right Shift| @f$a \gg b@f$             | a>>b
 * 31 | Boolean NOT        | @f$\neg a@f$              | !a
 * 32 | Boolean AND        | @f$a \wedge b@f$          | a&&b
 * 33 | Boolean OR         | @f$a \vee b@f$            | a\|\|b
 * 34 | Boolean XOR        | @f$a \oplus b@f$          | (!!a)^(!!b)
 * 35 | Boolean NAND       | @f$\overline{(a \wedge b)}@f$ | !(a&&b)
 * 36 | Boolean NOR        | @f$\overline{(a \vee b)}@f$   | !(a\|\|b)
 * 37 | Boolean XNOR       | @f$\overline{(a \oplus b)}@f$ | !((!!a)^(!!b))|
 * 38 | Logarithm Natural  | @f$\log(a)@f$             | log(a)
 * 39 | Logarithm Base N   | @f$\log_{b}(a)@f$         | log(a)/log(b)
 */
void alu_math(struct app_3bc_s* const self)
{
    switch(self->cache_l1.math)
    {
        case 1:
            self->cpu.ra = 
                (self->cache_l2.i16[0]<<1) + self->cache_l2.i16[1];
            break;

        case 2:
            self->cpu.ra = 
                (self->cache_l2.i16[0]<<3) + self->cache_l2.i16[1];
            break;

        case 3:
            self->cpu.ra = 
                (self->cache_l2.i16[0]*10) + self->cache_l2.i16[1];
            break;

        case 4:
            self->cpu.ra = 
                (self->cache_l2.i16[0]<<4) + self->cache_l2.i16[1];
            break;

        case 11:
            self->cpu.ra = 
                self->cache_l2.i16[0] + self->cache_l2.i16[1];
            break;

        case 12:
            self->cpu.ra = 
                self->cache_l2.i16[0] - self->cache_l2.i16[1];
            break;

        case 13:
            self->cpu.ra = 
                self->cache_l2.i16[0] * self->cache_l2.i16[1];
            break;

        case 14:
            if (self->cache_l2.i16[1] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra = 
                self->cache_l2.i16[0] / self->cache_l2.i16[1];
            break;

        case 15:
            if (self->cache_l2.i16[1] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra = 
                self->cache_l2.i16[0] % self->cache_l2.i16[1];
            break;

        case 16:
#if defined(TBC_NOT_MATH)
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: ALU 16")
#else
#warning "[3BC] UNSUPPORTED: ALU 16"
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
#else
            self->cpu.ra =
                (data_aux_3bc_t)trunc(powf((float)self->cache_l2.i16[0],
                    (float)self->cache_l2.i16[1]));
#endif
            break;

            case 17:
#if defined(TBC_NOT_MATH)
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: ALU 17")
#else
#warning "[3BC] UNSUPPORTED: ALU 17"
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
#else
            self->cpu.ra =
                (data_aux_3bc_t)trunc(powf((float)self->cache_l2.i16[0],
                    1.0f/(float)self->cache_l2.i16[1]));
#endif
            break;

        case 18:
            self->cpu.ra = self->cache_l2.i16[0] < 0?
                -self->cache_l2.i16[0]: 
                self->cache_l2.i16[0];
            break;

        case 21:
            self->cpu.ra = ~self->cache_l2.i16[0];
            break;

        case 22:
            self->cpu.ra =
                self->cache_l2.i16[0] & self->cache_l2.i16[1];
            break;

        case 23:
            self->cpu.ra =
                self->cache_l2.i16[0] | self->cache_l2.i16[1];
            break;

        case 24:
            self->cpu.ra =
                self->cache_l2.i16[0] ^ self->cache_l2.i16[1];
            break;

        case 25:
            self->cpu.ra =
                ~(self->cache_l2.i16[0] & self->cache_l2.i16[1]);
            break;

        case 26:
            self->cpu.ra =
                ~(self->cache_l2.i16[0] | self->cache_l2.i16[1]);
            break;

        case 27:
            self->cpu.ra =
                ~(self->cache_l2.i16[0] ^ self->cache_l2.i16[1]);
            break;

        case 28:
            self->cpu.ra =
                self->cache_l2.i16[0] << self->cache_l2.i16[1];

        case 29:
            self->cpu.ra =
                self->cache_l2.i16[0] << self->cache_l2.i16[1];
            break;

        case 31:
            self->cpu.ra = !self->cache_l2.i16[0];
            break;

        case 32:
            self->cpu.ra =
                self->cache_l2.i16[0] && self->cache_l2.i16[1];
            break;

        case 33:
            self->cpu.ra =
                self->cache_l2.i16[0] || self->cache_l2.i16[1];
            break;

        case 34:
            self->cpu.ra =
                (!!self->cache_l2.i16[0]) ^ (!!self->cache_l2.i16[1]);
            break;

        case 35:
            self->cpu.ra =
                !(self->cache_l2.i16[0] && self->cache_l2.i16[1]);
            break;

        case 36:
            self->cpu.ra =
                !(self->cache_l2.i16[0] || self->cache_l2.i16[1]);
            break;

        case 37:
            self->cpu.ra =
                !((!!self->cache_l2.i16[0]) ^ (!!self->cache_l2.i16[1]));
            break;

        case 38:
#if defined(TBC_NOT_MATH) || defined(TBC_NOT_LOG)
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: ALU 38")
#else
#warning "[3BC] UNSUPPORTED: ALU 38"
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
#else
            if (self->cache_l2.i16[0] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra =
                (data_aux_3bc_t)trunc(log((double)self->cache_l2.i16[0]));
            break;
#endif

        case 39:
#if !defined(TBC_NOT_LOG2) && !defined(TBC_NOT_MATH)
            /** @note optmized @b log2 **/
            if(self->cache_l2.i16[1] == 2) {
                self->cpu.ra =
                (data_aux_3bc_t)trunc(log2((double)self->cache_l2.i16[0]));
                break;
            }
#else
            /** @note software supporting @b log2 **/
            if(self->cache_l2.i16[1] == 2) {
                self->cpu.ra = 16;
                while(self->cache_l2.i16[1] &&
                    !(self->cache_l2.i16[0] & self->cache_l2.i16[1])) {
                    self->cache_l2.i16[1] = self->cache_l2.i16[1] >> 1;
                    --self->cpu.ra;
                }
                break;
            }
#endif
#if !defined(TBC_NOT_LOG10) && !defined(TBC_NOT_MATH)
            /** @note optmized @b log10 **/
            if(self->cache_l2.i16[1] == 10) {
                self->cpu.ra =
                (data_aux_3bc_t)trunc(log10((double)self->cache_l2.i16[0]));
                break;
            }
#endif
#if defined(TBC_NOT_MATH) || defined(TBC_NOT_LOG)
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: ALU 39 (PARTIAL)")
#else
#warning "[3BC] UNSUPPORTED: ALU 39 (PARTIAL)"
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
#else
            if (self->cache_l2.i16[0] == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NUMBER_ZERO;
                break;
            }
            self->cpu.ra =
                (data_aux_3bc_t)trunc(log((double)self->cache_l2.i16[0])/
                log((double)self->cache_l2.i16[0]));
            break;
#endif

        default:
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
    }
}
