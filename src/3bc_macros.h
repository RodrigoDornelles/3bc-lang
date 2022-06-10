/**
 * MACROS ENVIRONMENT (DETECT PLATAFORM/ARCHITECTURE)
 */

/** Atmel AVR **/
#if defined(ARDUINO_ARCH_AVR)
#define _3BC_AVR
#elif defined(__AVR_ATmega8__)
#define _3BC_AVR
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny25__)
#define _3BC_AVR
#elif defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny45__)
#define _3BC_AVR
#elif defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny85__)
#define _3BC_AVR
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define _3BC_AVR
#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__)                \
    || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define _3BC_AVR
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1284__)               \
    || defined(__AVR_ATmega1284P__)
#define _3BC_AVR
#elif defined(__AVR_ATmega2560__)
#define _3BC_AVR
#endif

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define _3BC_MOS6502
#endif

#if defined(__nuttx__)
#define _3BC_NUTTX
#endif

/**
 * PLATAFORM: ARDUINO
 *
 * NOTE: _3BC_SCU allows arduino IDE compilation in parts.
 * NOTE: _3BC_COMPACT reduces rom size.
 */
#if defined(ARDUINO)
#define _3BC_SCU
#define _3BC_COMPACT
#define _3BC_ARDUINO
/**
 * PLATAFORM: OLD COMPUTER
 */
#elif defined(_3BC_MOS6502)
#define _3BC_COMPACT
#define _3BC_COMPUTER
#define _3BC_PC_1970
#if !defined(_3BC_ENABLE_INTERPRETER) && !defined(_3BC_DISABLE_INTERPRETER)
#define _3BC_DISABLE_INTERPRETER
#endif
#elif defined(_3BC_NUTTX)
/**
 * PLATAFORM: NUTTX RTOS
 */
#define _3BC_COMPUTER
#if !defined(_3BC_ENABLE_INTERPRETER) && !defined(_3BC_DISABLE_INTERPRETER)
#define _3BC_ENABLE_INTERPRETER
#endif
#define _3BC_PC_UNIX
/**
 * PLATAFORM: MODERN COMPUTER
 */
#else
#define _3BC_COMPUTER
#if !defined(_3BC_ENABLE_INTERPRETER) && !defined(_3BC_DISABLE_INTERPRETER)
#define _3BC_ENABLE_INTERPRETER
#endif
#if defined(_WIN32)
#define _3BC_PC_WINDOWS
#else
#define _3BC_PC_UNIX
#endif
#endif

/**
 * PARTITIONED COMPILATION
 */
#ifndef _3BC_SCU
#define _3BC_SCU_FIX
#endif

/**
 * CONSTS MACROS
 */
#define LLRBT_BLACK (false)
#define LLRBT_RED (true)

#ifndef AUX
#define AUX (driver_accumulator_get(app))
#endif

#ifndef LABEL_HASH_SIZE
#ifdef _3BC_ARDUINO
#define LABEL_HASH_SIZE (8)
#else
#define LABEL_HASH_SIZE (128)
#endif
#endif

#ifndef GET_ANY_PARAM
#define GET_ANY_PARAM (address ? driver_memory_data_get(app, address) : value)
#endif

#define MEM_CONFIG_RESERVED (0b00000001) /** unused **/
#define MEM_CONFIG_FLOW_SAFE                                                   \
    (0b00000010) /** TODO: trust in over/under flow                            \
                  **/
#define MEM_CONFIG_GPIO_SEND (0b00000100) /** digital output **/
#define MEM_CONFIG_GPIO_READ (0b00001000) /** digital input **/
#define MEM_CONFIG_GPIO_PULL (0b00010000) /** pullup input **/
#define MEM_CONFIG_GPIO_ANAL (0b00100000) /** analogic/pwd **/

/**
 * FUNCTIONS MACROS
 */
#define PARSER_UNPACK(c)                                                       \
    (tolower(c[0]) | tolower(c[1]) << 8 | (long)tolower(c[2]) << 16            \
        | (long)tolower(c[3]) << 24)
#define PARSER_PACK(c1, c2, c3, c4, v, r)                                      \
    case (c1 | c2 << 8 | (long)c3 << 16 | (long)c4 << 24):                     \
        *v = r;                                                                \
        return (true)
#define ERROR_LOG_3BC(a, b)                                                    \
    case (a):                                                                  \
        driver_tty_output_raw(app, app->tty_error, (b));                       \
        break;
#define LLRBT_IS_RED(n) (n == NULL ? false : n->color == LLRBT_RED)
#define POINTER(a) (driver_memory_pointer(app, a))
#define BITFIELD_HAS(a, b) ((b) == ((a) & (b)))
/**
 * PARAMTERS MACROS
 */
#define PARAMS_DEFINE                                                          \
    struct app_3bc_s *const app, register_3bc_t reg, address_3bc_t address, data_3bc_t value
#define VALIDATE_NOT_DUALITY                                                   \
    if (address != 0 && value != 0)                                            \
        driver_program_error(app, ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS                                                    \
    if (address != 0)                                                          \
        driver_program_error(app, ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES                                                    \
    if (value != 0)                                                            \
        driver_program_error(app, ERROR_PARAM_BLOCKED_VALUE);
#define VALIDATE_NOT_NEGATIVES                                                 \
    if (value < 0 || driver_memory_data_get(app, address) < 0 || AUX < 0)      \
        driver_program_error(app, ERROR_NUMBER_NEGATIVE);
#define REQUIRED_ADDRESS                                                       \
    if (address == 0)                                                          \
        driver_program_error(app, ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE                                                         \
    if (value == 0)                                                            \
        driver_program_error(app, ERROR_PARAM_REQUIRE_VALUE);
#define REQUIRED_ANY                                                           \
    if (value == 0 && address == 0)                                            \
        driver_program_error(app, ERROR_PARAM_REQUIRE_ANY);

/**
 * INSTRUCTIONS PACK MACROS
 */
#define CPU_PACK_ZEROMODE(mode)                                                \
    case ((mode * 7) + 1):                                                     \
    case ((mode * 7) + 2):                                                     \
    case ((mode * 7) + 3):                                                     \
    case ((mode * 7) + 4):                                                     \
    case ((mode * 7) + 5):                                                     \
    case ((mode * 7) + 6):                                                     \
        cpu_not_mode(app, reg, address, value);                                \
        break;
#define CPU_PACK_RESERVED(mode)                                                \
    case ((mode * 7) + 1):                                                     \
    case ((mode * 7) + 2):                                                     \
    case ((mode * 7) + 3):                                                     \
    case ((mode * 7) + 4):                                                     \
    case ((mode * 7) + 5):                                                     \
    case ((mode * 7) + 6):                                                     \
        cpu_mode_reserved(app, reg, address, value);                           \
        break;
#define CPU_PACK1(mode, a)                                                     \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;
#define CPU_PACK2(mode, a, b)                                                  \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;
#define CPU_PACK3(mode, a, b, c)                                               \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;
#define CPU_PACK4(mode, a, b, c, d)                                            \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;
#define CPU_PACK5(mode, a, b, c, d, e)                                         \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 5):                                                     \
        e(app, reg, address, value);                                           \
        break;
#define CPU_PACK6(mode, a, b, c, d, e, f)                                      \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 5):                                                     \
        e(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 6):                                                     \
        f(app, reg, address, value);                                           \
        break;

/**
 * USER MACROS
 */
#define lang_3bc_update driver_interrupt
#define lang_3bc_init driver_power_init
#define lang_3bc_line ds_program_fifo_line_add
#define lang_3bc_print(a, t, l)                                                \
    ;                                                                          \
    a->t.type = STREAM_TYPE_FUNCTION_CALL;                                     \
    a->t.io.lambda = l;
#define lang_3bc_custom custom_3bc_func_set
