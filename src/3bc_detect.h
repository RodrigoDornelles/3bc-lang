/**
 * ______ _       ___ _____ ___  ______ ______________  ___
 * | ___ \ |     / _ \_   _/ _ \ |  ___|  _  | ___ \  \/  |
 * | |_/ / |    / /_\ \| |/ /_\ \| |_  | | | | |_/ / .  . |
 * |  __/| |    |  _  || ||  _  ||  _| | | | |    /| |\/| |
 * | |   | |____| | | || || | | || |   \ \_/ / |\ \| |  | |
 * \_|   \_____/\_| |_/\_/\_| |_/\_|    \___/\_| \_\_|  |_/
 *
 * BRIEF: host platform detection, and resource adjustments.
 *
 * DEFINES:
 * TBC_ARCH_BITS_16     -> 16 bits cpu
 * TBC_ARCH_BITS_32     -> 32 bits cpu
 * TBC_ARCH_BITS_64     -> 64 bits cpu
 * TBC_ARCH_BITS_8      -> 8 bits cpu
 *
 * TBC_ARCH_CPU_6502    -> MOS Technology architeture
 * TBC_ARCH_CPU_ARM     -> Acorn RISC Machine architeture
 * TBC_ARCH_CPU_AVR     -> Microchip Technology architeture
 * TBC_ARCH_CPU_INTEL   -> Intel x86 or amd64 architeture
 * TBC_ARCH_CPU_RISCV   -> University of California, Berkeley architeture
 *
 * TBC_KERNEL_DARWIN    -> Apple kernel
 * TBC_KERNEL_HURD      -> Free Software kernel
 * TBC_KERNEL_LINUX     -> Linus Tovards kernel
 * TBC_KERNEL_NT        -> Microsoft kernel
 * TBC_KERNEL_UNIX      -> Bell Labs kernel
 *
 * TBC_NOT_LOG          -> doesn't support logarithm
 * TBC_NOT_MATH         -> doesn't support math library
 * TBC_NOT_LOG2         -> doesn't support base 2 logarithm
 * TBC_NOT_LOG10        -> doesn't support base 10 logarithm
 *
 * TBC_OPT_COMPACT      -> optimize storage occupied
 *
 * TBC_P_COMPUTER       -> microcomputer platform
 * TBC_P_EMBEDDED       -> embedded device plataform
 * TBC_P_WEBASSEMBLY    -> browser or nodejs platform
 * TBC_P_COMPUTER_OLD   -> 70's or 80's microcomputer platform
 *
 * TBC_USE_ARDUINO      -> compatible with arduino framework
 * TBC_USE_CONIO        -> compatible with dos systems
 * TBC_USE_ESPIDF       -> compatible with espressif framework
 * TBC_USE_POSIX        -> compatible with unix systems
 */

/**
 * PLATAFORM: OLD CLASSIC COMPUTERS
 */
#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define TBC_ARCH_BITS_8
#define TBC_ARCH_CPU_6502
#define TBC_NOT_LOG
#define TBC_NOT_MATH
#define TBC_NOT_LOG2
#define TBC_NOT_LOG10
#define TBC_OPT_COMPACT
#define TBC_P_COMPUTER
#endif

/**
 * PLATAFORM: EMBEDDED SYSTEMS
 */
#if defined(ARDUINO_ARCH_AVR)
#define TBC_ARCH_BITS_8
#define TBC_ARCH_CPU_AVR
#define TBC_SCU_FORCE
#define TBC_NOT_LOG2
#define TBC_OPT_COMPACT
#define TBC_P_EMBEDDED
#define TBC_USE_ARDUINO
#endif

#if defined(ESP_PLATFORM)
#define TBC_ARCH_BITS_32
#define TBC_ARCH_CPU_RISCV
#define TBC_SCU_FORCE
#define TBC_OPT_COMPACT
#define TBC_P_EMBEDDED
#define TBC_USE_ARDUINO
#endif

/**
 * PLATAFORM: KERNEL NUTTX
 *
 * TODO: replace '__nuttx__' by another compiler constant
 * that is from the compiler.
 */
#if defined(__nuttx__)
#define TBC_KERNEL_NUTTX
#define TBC_PREFER_INTERPRETER
#define TBC_P_EMBEDDED
#define TBC_USE_POSIX
#endif

/**
 * PLATAFORM: KERNEL LINUX
 */
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define TBC_KERNEL_LINUX
#define TBC_PREFER_INTERPRETER
#define TBC_P_COMPUTER
#define TBC_USE_POSIX
#endif

/**
 * PLATAFORM: KERNEL NT
 */
#if defined(_WIN32)
#define TBC_KERNEL_NT
#define TBC_PREFER_INTERPRETER
#define TBC_P_COMPUTER
#define TBC_USE_CONIO
#endif

/**
 * PLATAFORM: KERNEL DARWIN
 */
#if defined(__APPLE__)
#define TBC_USE_POSIX
#define TBC_KERNEL_DARWIN
#define TBC_PREFER_INTERPRETER
#define TBC_P_COMPUTER
#endif

/**
 * ______ _____  ___ _____ _   _______ _____ _____ 
 * |  ___|  ___|/ _ \_   _| | | | ___ \  ___/  ___|
 * | |_  | |__ / /_\ \| | | | | | |_/ / |__ \ `--. 
 * |  _| |  __||  _  || | | | | |    /|  __| `--. \
 * | |   | |___| | | || | | |_| | |\ \| |___/\__/ /
 * \_|   \____/\_| |_/\_/  \___/\_| \_\____/\____/ 
 */

/**
 * FEATURE: INTERPRETER
 *
 * BRIEF: language mnemonic analyzer, including
 * lexer, tokenizer, and compiler.
 */
#if defined(TBC_SCU_FORCE) && !defined(TBC_SOURCE_ENTRY)
#if defined(_3BC_ENABLE_INTERPRETER)
#define TBC_INTERPRETER
#elif !defined(_3BC_DISABLE_INTERPRETER)
#if defined(TBC_PREFER_INTERPRETER)
#define TBC_INTERPRETER
#else 
#error \
    define '_3BC_ENABLE_INTERPRETER' \
    or '_3BC_DISABLE_INTERPRETER' \
    after include header '3bc.h'
#endif
#endif
#endif

/**
 * FEATURE: SEPARATE SOURCE COMPILATION
 *
 * BRIEF: that allows you to compile the software into pieces
 * and then link them together.
 *
 * JOKE: Arduino makes things always problematic for library creators,
 * don't blame me for "strange" solutions.
 *
 * DEFINES:
 * TBC_SCU_FORCE            -> Compiler forces user to use SCU
 * TBC_SCU_OPTIONAL_FIX     -> Fixture optional feats when SCU is forced
 * TBC_SOURCE_REGISTERS     -> Include opcode registration in source code
 */
#if defined(_3BC_SCU) || defined(TBC_SCU_FORCE)
/** enable **/
#define TBC_SCU
/** fix problem with arduino cli compiler **/
#if defined(TBC_USE_ARDUINO) && defined(TBC_SOURCE_ENTRY)
#define TBC_SCU_OPTIONAL_FIX
#endif
/** NOT SCU **/
#else
/** disable **/
#define TBC_SOURCE_REGISTERS
#endif


/**
 * FEATURE: CUSTOM REGISTERS
 *
 * BRIEF: that allows you to add customizable instructions.
 */
#if defined(_3BC_ENABLE_CUSTOM)
#define TBC_CUSTOM
#endif
