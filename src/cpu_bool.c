#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_bool_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(!GET_ANY_PARAM);
}

void cpu_bool_and(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(AUX && GET_ANY_PARAM);
}

void cpu_bool_or(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(AUX || GET_ANY_PARAM);
}

void cpu_bool_xor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set((!!AUX) ^ (!!GET_ANY_PARAM));
}

void cpu_bool_nand(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(!(AUX && GET_ANY_PARAM));
}

void cpu_bool_nor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(!(AUX || GET_ANY_PARAM));
}

void cpu_bool_xnor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(!((!!AUX) ^ (!!GET_ANY_PARAM)));
}

void cpu_bool_and_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(AUX && !GET_ANY_PARAM);
}

void cpu_bool_or_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(AUX || !GET_ANY_PARAM);
}
