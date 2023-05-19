#include "alu_common_simple.h"
#include "types_errors.h"

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
 * 11 | Addition           | @f$a + b@f$               | a+b
 * 12 | Subtraction        | @f$a - b@f$               | a-b
 * 13 | Multiplication     | @f$a \times b@f$          | a*b
 * 14 | Division           | @f$\frac{a}{b}@f$         | a/b
 * 15 | Modulo             | @f$a \mod b@f$            | a%b
 * 16 | Exponentiation     | @f$a^b@f$                 | pow(a,b)
 * 17 | Nth Root           | @f$\sqrt[b]{a}@f$         | pow(a,1/b)
 * 18 | Absolute Value     | @f$\|a\|@f$               | abs(a)
 * 19 | Multiplication Add | @f$(a \times base) + b@f$ | (a*base)+b
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
void alu_common_simple(struct app_3bc_s* const self)
{
    switch(self->cache_l1.math)
    {
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

        case 17:
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

        default:
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_UNSUPPORTED;
            break;
    }
}

/*
void cpu_bool_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, !AUX);
}

void cpu_bool_and(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX && GET_ANY_PARAM);
}

void cpu_bool_or(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX || GET_ANY_PARAM);
}

void cpu_bool_xor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, (!!AUX) ^ (!!GET_ANY_PARAM));
}

void cpu_bool_nand(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !(AUX && GET_ANY_PARAM));
}

void cpu_bool_nor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !(AUX || GET_ANY_PARAM));
}

void cpu_bool_xnor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !((!!AUX) ^ (!!GET_ANY_PARAM)));
}

*/