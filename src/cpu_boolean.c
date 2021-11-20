#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_bitwise_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, ~AUX);
}

void cpu_bitwise_and(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX & GET_ANY_PARAM);
}

void cpu_bitwise_or(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX | GET_ANY_PARAM);
}

void cpu_bitwise_xor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX ^ GET_ANY_PARAM);
}

void cpu_bitwise_nand(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX & GET_ANY_PARAM));
}

void cpu_bitwise_nor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX | GET_ANY_PARAM));
}

void cpu_bitwise_xnor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX ^ GET_ANY_PARAM));
}

void cpu_bitwise_left(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX << GET_ANY_PARAM);
}

void cpu_bitwise_right(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX >> GET_ANY_PARAM);
}

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
