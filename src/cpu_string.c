#include "3bc.h"

RETURN_DEFINE cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    lang_driver_output_1(STRI, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    lang_driver_output_1(STRC, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    lang_driver_output_1(STRO, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    lang_driver_output_1(STRX, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_string_stru(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    lang_driver_output_1(STRU, AUX);
    return RETURN_OK;
}