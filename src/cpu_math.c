#define _3BC_SCU_FIX_2
#include "3bc.h"


void cpu_math_sum(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(AUX + GET_ANY_PARAM);
}

void cpu_math_sub(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(AUX - GET_ANY_PARAM);
}

void cpu_math_mul(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(AUX * GET_ANY_PARAM);
}

void cpu_math_div(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        register data_3bc_t divisor = GET_ANY_PARAM;
        if (divisor == 0) {
            driver_program_error(ERROR_DIVISION_BY_ZERO);
        }
        else {
            driver_accumulator_set(AUX/divisor);
        }
    }    
}

void cpu_math_mod(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(AUX % GET_ANY_PARAM);
}

void cpu_math_power(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    #if defined(_3BC_MOS6502)
    driver_program_error(ERROR_UNSUPPORTED);
    #else 
    driver_accumulator_set((data_aux_3bc_t) pow((double) (AUX), (double) (GET_ANY_PARAM)));
    #endif
}

void cpu_math_root(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    #if defined(_3BC_MOS6502)
    driver_program_error(ERROR_UNSUPPORTED);
    #else 
    driver_accumulator_set((data_aux_3bc_t) pow((double) (AUX), (1 / (double) (GET_ANY_PARAM))));
    #endif
}

void cpu_math_abs(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set((data_aux_3bc_t) labs((long int) AUX));
}

void cpu_math_negative(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set((data_aux_3bc_t) labs((long int) AUX) * (-1));
}