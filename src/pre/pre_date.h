/**
 * @link https://stackoverflow.com/questions/11697820/how-to-use-date-and-time-predefined-macros-in-as-two-integers-then-stri
 */
#ifndef H_PRE_DATE_TBC
#define H_PRE_DATE_TBC

#define TBC_YEAR_CH0 (__DATE__[7])
#define TBC_YEAR_CH1 (__DATE__[8])
#define TBC_YEAR_CH2 (__DATE__[9])
#define TBC_YEAR_CH3 (__DATE__[10])

#define ___TBC_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a')
#define ___TBC_MONTH_IS_FEB (__DATE__[0] == 'F')
#define ___TBC_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define ___TBC_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define ___TBC_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define ___TBC_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define ___TBC_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define ___TBC_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define ___TBC_MONTH_IS_SEP (__DATE__[0] == 'S')
#define ___TBC_MONTH_IS_OCT (__DATE__[0] == 'O')
#define ___TBC_MONTH_IS_NOV (__DATE__[0] == 'N')
#define ___TBC_MONTH_IS_DEC (__DATE__[0] == 'D')

#define TBC_MONTH_CH0 \
    ((___TBC_MONTH_IS_OCT || ___TBC_MONTH_IS_NOV || ___TBC_MONTH_IS_DEC) ? '1' : '0')

#define TBC_MONTH_CH1 \
    ( \
        (___TBC_MONTH_IS_JAN) ? '1' : \
        (___TBC_MONTH_IS_FEB) ? '2' : \
        (___TBC_MONTH_IS_MAR) ? '3' : \
        (___TBC_MONTH_IS_APR) ? '4' : \
        (___TBC_MONTH_IS_MAY) ? '5' : \
        (___TBC_MONTH_IS_JUN) ? '6' : \
        (___TBC_MONTH_IS_JUL) ? '7' : \
        (___TBC_MONTH_IS_AUG) ? '8' : \
        (___TBC_MONTH_IS_SEP) ? '9' : \
        (___TBC_MONTH_IS_OCT) ? '0' : \
        (___TBC_MONTH_IS_NOV) ? '1' : \
        (___TBC_MONTH_IS_DEC) ? '2' : \
        /* error default */    '?' \
    )

#define TBC_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define TBC_DAY_CH1 (__DATE__[5])

#define TBC_HOUR_CH0 (__TIME__[0])
#define TBC_HOUR_CH1 (__TIME__[1])
#define TBC_MINU_CH0 (__TIME__[3])
#define TBC_MINU_CH1 (__TIME__[4])
#define TBC_SECO_CH0 (__TIME__[6])
#define TBC_SECO_CH1 (__TIME__[7])

#endif
