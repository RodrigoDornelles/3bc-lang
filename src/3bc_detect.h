/**
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * DESCRIPTION:
 * Header refers detection of all platform, compilers and features.
 *
 * BRIEF:
 * Low-level language, tiny virtual machine, intermediate representation,
 * embeddable, easy for beginners. (Friendly Punched cards)
 *
 * AUTHOR:
 * Copyright (C) 2020 Rodrigo Dornelles.
 *
 * LICENSE:
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef H_DETECT_TBC
#define H_DETECT_TBC

/**
 *  _____                       _ _
 * /  __ \                     (_) |
 * | /  \/ ___  _ __ ___  _ __  _| | ___ _ __
 * | |    / _ \| '_ ` _ \| '_ \| | |/ _ \ '__|
 * | \__/\ (_) | | | | | | |_) | | |  __/ |
 *  \____/\___/|_| |_| |_| .__/|_|_|\___|_|
 *                       | |
 *                       |_|
 *
 * BRIEF: builder detection, for compatibility
 * and resource optimization purposes.
 */

#if defined(__STDC_VERSION__)
#if (__STDC_VERSION__ >= 201710L)
#define TBC_CC_STD_17
#define TBC_CC_STD_11
#define TBC_CC_STD_99
#elif (__STDC_VERSION__ >= 201112L)
#define TBC_CC_STD_11
#define TBC_CC_STD_99
#elif (__STDC_VERSION__ >= 199901L)
#define TBC_CC_STD_99
#else
#warning "__STDC_VERSION__ not recognized."
#define TBC_CC_STD_89
#endif
#else
#define TBC_CC_STD_89
#endif

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
 * TBC_KERNEL_DARWIN    -> Apple kernel
 * TBC_KERNEL_HURD      -> Free Software kernel
 * TBC_KERNEL_LINUX     -> Linus Tovards kernel
 * TBC_KERNEL_NT        -> Microsoft kernel
 * TBC_KERNEL_UNIX      -> Bell Labs kernel
 * TBC_KERNEL_NUTTX     -> Apache foundation kernel
 *
 * TBC_NOT_LOG          -> doesn't support logarithm
 * TBC_NOT_MATH         -> doesn't support math library
 * TBC_NOT_LOG2         -> doesn't support base 2 logarithm
 * TBC_NOT_LOG10        -> doesn't support base 10 logarithm
 * TBC_NOT_ARGCV        -> doesn't support argc and argv on main entry
 * TBC_NOT_FILES        -> doesn't support files.
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
#define TBC_NOT_LOG
#ifndef TBC_NOT_MATH
#define TBC_NOT_MATH
#endif
#define TBC_NOT_LOG2
#define TBC_NOT_LOG10
#define TBC_OPT_COMPACT
#define TBC_P_COMPUTER
#define TBC_P_COMPUTER_OLD
#define TBC_USE_CONIO
#endif

#if defined(__NES__)
#define TBC_NOT_ARGCV
#define TBC_NOT_FILES
#define TBC_NOT_CLOCK
#define TBC_CONSOLE_NES
#define TBC_OPT_ULTRA_COMPACT
#undef TBC_P_COMPUTER
/** TODO: remove **/ 
#define _3BC_DISABLE_INTERPRETER
#endif

/**
 * PLATAFORM: EMBEDDED SYSTEMS
 */
#if defined(ARDUINO_ARCH_AVR)
#define TBC_SCU_FORCE
#define TBC_NOT_LOG2
#define TBC_NOT_ARGCV
#define TBC_OPT_COMPACT
#define TBC_P_EMBEDDED
#define TBC_USE_ARDUINO
#endif

#if defined(ESP_PLATFORM)
#define TBC_SCU_FORCE
#define TBC_NOT_ARGCV
#define TBC_OPT_COMPACT
#define TBC_P_EMBEDDED
#define TBC_USE_ARDUINO
#endif

#if defined(ARDUINO_ARCH_ESP8266)
#define TBC_SCU_FORCE
#define TBC_NOT_ARGCV
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
 * PLATAFORM: KERNEL UNIX
 */
#if defined(__unix__) || defined(BSD)
#define TBC_USE_POSIX
#define TBC_KERNEL_UNIX
#define TBC_PREFER_INTERPRETER
#define TBC_P_COMPUTER
#endif

/**
 * PLATAFORM: Browser/NodeJS
 */
#if defined(EMSCRIPTEN)
#define TBC_USE_POSIX
#define TBC_PREFER_INTERPRETER
#define TBC_P_WEBASSEMBLY
#endif

/**
 *  _____ ______ _   _                  _
 * /  __ \| ___ \ | | |                | |
 * | /  \/| |_/ / | | |   __ _ _ __ ___| |__
 * | |    |  __/| | | |  / _` | '__/ __| '_ \
 * | \__/\| |   | |_| | | (_| | | | (__| | | |
 *  \____/\_|    \___/   \__,_|_|  \___|_| |_|
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
 * TBC_ARCH_CPU_POWER   -> Apple, IBM and Motorola alliance architeture
 * TBC_ARCH_CPU_RISCV   -> University of California, Berkeley architeture
 * TBC_ARCH_CPU_WASM    -> Web Assembly vitual machine architeture
 */

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define TBC_ARCH_BITS_8
#define TBC_ARCH_CPU_6502
#endif

#if defined(__arm__)
#define TBC_ARCH_BITS_32
#define TBC_ARCH_CPU_ARM
#endif

#if defined(__aarch64__)
#define TBC_ARCH_BITS_64
#define TBC_ARCH_CPU_ARM
#endif

#if defined(ARDUINO_ARCH_AVR)
#define TBC_ARCH_BITS_8
#define TBC_ARCH_CPU_AVR
#endif

#if defined(__x86_64__)
#define TBC_ARCH_BITS_64
#define TBC_ARCH_CPU_INTEL
#endif

#if defined(__ppc64__)
#define TBC_ARCH_BITS_64
#define TBC_ARCH_CPU_POWER
#endif

#if defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_ESP8266)
#define TBC_ARCH_BITS_32
#define TBC_ARCH_CPU_RISCV
#endif

#if defined(EMSCRIPTEN)
#define TBC_ARCH_BITS_32
#define TBC_ARCH_CPU_WASM
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
 * FEATURE: INTERPRETER
 *
 * BRIEF: language mnemonic analyzer, including
 * lexer, tokenizer, and compiler.
 */
#if !defined(TBC_SCU_OPTIONAL_FIX)
#if defined(_3BC_ENABLE_INTERPRETER)
#define TBC_INTERPRETER
#elif !defined(_3BC_DISABLE_INTERPRETER)
#if defined(TBC_PREFER_INTERPRETER)
#define TBC_INTERPRETER
#else
#error define '_3BC_ENABLE_INTERPRETER' \
    or '_3BC_DISABLE_INTERPRETER' \
    after include header '3bc.h'
#endif
#endif
#endif

/**
 * FEATURE: CUSTOM REGISTERS
 *
 * BRIEF: that allows you to add customizable instructions.
 */
#if defined(_3BC_ENABLE_CUSTOM)
#define TBC_CUSTOM
#endif

/**
 *  _____           _       _   _____                     _
 * /  ___|         (_)     | | /  ___|                   | |
 * \ `--.  ___ _ __ _  __ _| | \ `--. _ __   ___  ___  __| |
 *  `--. \/ _ \ '__| |/ _` | |  `--. \ '_ \ / _ \/ _ \/ _` |
 * /\__/ /  __/ |  | | (_| | | /\__/ / |_) |  __/  __/ (_| |
 * \____/ \___|_|  |_|\__,_|_| \____/| .__/ \___|\___|\__,_|
 *                                   | |
 *                                   |_|
 * BRIEF: helper to find serial speed according to hardware.
 * TODO: improving this list is constant work.
 */
#if defined(__AVR_ATmega8__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny25__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny45__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny85__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega1280__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#define TBC_SERIAL_SPEED 9600
#elif defined(__AVR_ATmega2560__)
#define TBC_SERIAL_SPEED 115200
#elif defined(ESP8266)
#define TBC_SERIAL_SPEED 9600
#elif defined(ESP32)
#define TBC_SERIAL_SPEED 115200
#endif

#endif
