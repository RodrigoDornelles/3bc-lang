#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_math_sum(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX + GET_ANY_PARAM);
}

void cpu_math_sub(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX - GET_ANY_PARAM);
}

void cpu_math_mul(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX * GET_ANY_PARAM);
}

void cpu_math_div(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        register data_3bc_t divisor = GET_ANY_PARAM;
        if (divisor == 0) {
            driver_program_error(app, ERROR_NUMBER_ZERO);
        } else {
            driver_accumulator_set(app, AUX / divisor);
        }
    }
}

void cpu_math_mod(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX % GET_ANY_PARAM);
}

void cpu_math_power(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
#if defined(_3BC_MOS6502)
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    /** TODO: remove this "gambiarra" tecnical debt **/
    driver_accumulator_set(app,
        (data_aux_3bc_t)trunc(pow((double)(AUX), (double)(GET_ANY_PARAM))));
#endif
}

void cpu_math_root(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
#if defined(_3BC_MOS6502)
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    driver_accumulator_set(app,
        (data_aux_3bc_t)trunc(
            pow((double)(AUX), (1 / (double)(GET_ANY_PARAM)))));
#endif
}

void cpu_math_abs(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, labs(AUX));
}

/**
 * logarithm with base
 */
void cpu_math_logb(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    REQUIRED_ANY
#if defined(_3BC_MOS6502)
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    if (AUX == 0) {
        driver_program_error(app, ERROR_NUMBER_ZERO);
    } else {
        register int base = GET_ANY_PARAM;
        switch (base) {
        case 2:
            driver_accumulator_set(
                app, (data_aux_3bc_t)trunc(log2((double)AUX)));
            break;

        case 10:
            driver_accumulator_set(
                app, (data_aux_3bc_t)trunc(log10((double)AUX)));
            break;

        default:
            driver_accumulator_set(app,
                (data_aux_3bc_t)trunc(log((double)AUX) / log((double)base)));
            break;
        }
    }
#endif
}

/**
 * logarithm natural
 */
void cpu_math_logn(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
#if defined(_3BC_MOS6502)
    /** TODO: support logarithm on 6502 **/
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    if (AUX == 0) {
        driver_program_error(app, ERROR_NUMBER_ZERO);
    }

    driver_accumulator_set(app, (data_aux_3bc_t)trunc(log((double)AUX)));
#endif
}

void cpu_math_mul_add(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        char base = 0;

        if (reg == NB02) {
            base = 2;
        } else if (reg == NB08) {
            base = 8;
        } else if (reg == NB10) {
            base = 10;
        } else if (reg == NB16) {
            base = 16;
        }

        driver_accumulator_set(app, (AUX * base) + GET_ANY_PARAM);
    }
}