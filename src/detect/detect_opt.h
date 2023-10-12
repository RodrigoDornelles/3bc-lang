#ifndef H_DETECT_OPT_TBC
#define H_DETECT_OPT_TBC

#if defined(ARDUINO_ARCH_AVR)
#ifndef TBC_OPT_COMPACT_1
#define TBC_OPT_COMPACT_1
#endif
#endif

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__) || defined(__MSX__)
#ifndef TBC_OPT_COMPACT_2
#define TBC_OPT_COMPACT_2
#endif
#endif

#endif
