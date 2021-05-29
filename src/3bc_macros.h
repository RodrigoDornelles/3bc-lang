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
#define APP_3BC                     (lang_bootstrap())
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

#define MEM_CONFIG_MAX_VALUE        (0b0010)
#define MEM_CONFIG_MIN_VALUE        (0b0100)
#define MEM_CONFIG_NORMALIZE        (0b1000)

/**
 * FUNCTIONS MACROS
 */
#define lang_line(a,b,c)                tape_program_line_add(a,b,c)
#define PARSER_UNPACK(c)                (tolower(c[0])+tolower(c[1])+tolower(c[2])+tolower(c[3]))
#define PARSER_PACK(c1,c2,c3,c4,v,r,...)  case(c1+c2+c3+c4):*v=r;return(true)
#define LLRBT_IS_RED(n)                 (n==NULL?false:n->color==LLRBT_RED)


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