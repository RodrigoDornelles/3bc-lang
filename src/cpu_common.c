#include "3bc.h"

RETURN_DEFINE cpu_null(PARAMS_DEFINE)
{
    return RETURN_OK;
}

RETURN_DEFINE cpu_mode(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_router_cpu_set(value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_label_invalid(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] LABEL INVALID");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_mode(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] EMPUTY CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_duality(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] DUALITY ADDRES WITH VALUE IN SINGLE REGISTER");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_exist(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] REGISTER NOT EXIST IN CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_addres(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] NOT ALOWED ADDRES");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_value(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] NOT ALOWED VALUE");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_required_addres(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] ADDRES IS REQUIRED");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_required_value(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] VALUE IS REQUIRED");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}

RETURN_DEFINE cpu_mode_protected(PARAMS_DEFINE)
{
    lang_driver_error("[!] [3BC] [CRITICAL ERROR] PROTECTED CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
    return RETURN_OK;
}