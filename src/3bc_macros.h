/**
 * MACROS ENVIRONMENT (PLATAFORM DETECT)
 */
#if defined(ARDUINO)
#define _3BC_COMPACT
#define _3BC_ARDUINO
#else
/**
 * @todo detect is separeted compiling for computer
 */
#define _3BC_REQUIRE_INSTRUCTIONS
#define _3BC_COMPUTER
#ifdef _WIN32
#define _3BC_PC_WINDOWS
#else 
#define _3BC_PC_NOT_WINDOWS
#endif
#endif

/**
 * CONSTS MACROS
 */
#define LLRBT_BLACK                 (false)
#define LLRBT_RED                   (true)

#ifndef APP_3BC
#define APP_3BC                     (driver_bootstrap())
#endif

#ifndef AUX
#define AUX                         (tape_aux_get())
#endif

#ifndef LABEL_HASH_SIZE
#ifdef _3BC_ARDUINO
#define LABEL_HASH_SIZE             (8) 
#else
#define LABEL_HASH_SIZE             (128)
#endif
#endif

#ifndef GET_ANY_PARAM
#define GET_ANY_PARAM               (address?tape_memory_data_get(address):value)
#endif 

#define MEM_CONFIG_MAX_VALUE        (0b0010)
#define MEM_CONFIG_MIN_VALUE        (0b0100)
#define MEM_CONFIG_NORMALIZE        (0b1000)

/**
 * FUNCTIONS MACROS
 */
#define PARSER_UNPACK(c)                (tolower(c[0])+tolower(c[1])+tolower(c[2])+tolower(c[3]))
#define PARSER_PACK(c1,c2,c3,c4,v,r,...)  case(c1+c2+c3+c4):*v=r;return(true)
#define LLRBT_IS_RED(n)                 (n==NULL?false:n->color==LLRBT_RED)

/**
 * LEGACY COMPATIBILITY MACROS
 */
#define lang_line                tape_program_line_add
#define lang_driver_init         driver_power_init
#define lang_driver_exit         driver_power_exit
#define lang_driver_run          driver_program_run

/**
 * C/C++ COMPATIBILITY MACROS
 */
#ifdef inline
#define optional_inline          inline
#else 
#define optional_inline
#endif

/**
 * PARAMTERS MACROS
 */
#define PARAMS_DEFINE                   int reg, int address, int value
#define VALIDATE_NOT_DUALITY            if(address!=0&&value!=0)lang_driver_error(ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS             if(address!=0)lang_driver_error(ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES             if(value!=0)lang_driver_error(ERROR_PARAM_BLOCKED_VALUE);
#define REQUIRED_ADDRESS                if(address==0)lang_driver_error(ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE                  if(value==0)lang_driver_error(ERROR_PARAM_REQUIRE_VALUE);
#define AUX_USE_ANY_PARAM               tape_aux_set(GET_ANY_PARAM);

/**
 * INSTRUCTIONS PACK MACROS
 */
#ifdef _3BC_COMPACT
#define CPU_PACK_ZEROMODE(mode)     case(mode):switch(reg){default:return(&cpu_not_mode);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_RESERVED(mode)     case(mode):switch(reg){default:return(&cpu_mode_reserved);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_PROTECTED(mode)    case(mode):switch(reg){default:return(&cpu_mode_protected);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK1(mode,a)           case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);}
#define CPU_PACK2(mode,a,b)         case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);}
#define CPU_PACK3(mode,a,b,c)       case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);}
#define CPU_PACK4(mode,a,b,c,d)     case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);}
#define CPU_PACK5(mode,a,b,c,d,e)   case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);}
#define CPU_PACK6(mode,a,b,c,d,e,f) case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);case(0b110):return(&f);}
#else 
#define CPU_PACK_ZEROMODE(mode)     {&cpu_null,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_not_mode,&cpu_mode},
#define CPU_PACK_RESERVED(mode)     {&cpu_null,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode_reserved,&cpu_mode},
#define CPU_PACK_PROTECTED(mode)    {&cpu_null,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode_protected,&cpu_mode},
#define CPU_PACK1(mode,a)           {&cpu_null,&a,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode},
#define CPU_PACK2(mode,a,b)         {&cpu_null,&a,&b,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode},
#define CPU_PACK3(mode,a,b,c)       {&cpu_null,&a,&b,&c,&cpu_not_exist,&cpu_not_exist,&cpu_not_exist,&cpu_mode},
#define CPU_PACK4(mode,a,b,c,d)     {&cpu_null,&a,&b,&c,&d,&cpu_not_exist,&cpu_not_exist,&cpu_mode},
#define CPU_PACK5(mode,a,b,c,d,e)   {&cpu_null,&a,&b,&c,&d,&e,&cpu_not_exist,&cpu_mode},
#define CPU_PACK6(mode,a,b,c,d,e,f) {&cpu_null,&a,&b,&c,&d,&e,&cpu_mode},
#endif