/*******************************************************************//**
 * @file    version.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#ifndef version_h
#define version_h

#define cn_VERSION_MAJOR (0)
#define cn_VERSION_MINOR (3)
#define cn_VERSION_CUT (12)

/**
 * @brief Build definitions() : Provided build date/time information through system date/time.
 */
// Example of __DATE__ string: "Jul 27 2012" after compilation
//                              01234567890
#define cn_BUILD_YEAR_CH0 (__DATE__[ 7])
#define cn_BUILD_YEAR_CH1 (__DATE__[ 8])
#define cn_BUILD_YEAR_CH2 (__DATE__[ 9])
#define cn_BUILD_YEAR_CH3 (__DATE__[10])

// Month build
// Includes extra letters in string creation for
#define cn_BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define cn_BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define cn_BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define cn_BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define cn_BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define cn_BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define cn_BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define cn_BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define cn_BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define cn_BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define cn_BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define cn_BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')

// Creates month (limits letters based on month type)
#define cn_BUILD_MONTH_CH0 \
    ((cn_BUILD_MONTH_IS_OCT || cn_BUILD_MONTH_IS_NOV || cn_BUILD_MONTH_IS_DEC) ? '1' : '0')

#define cn_BUILD_MONTH_CH1 \
    ( \
        (cn_BUILD_MONTH_IS_JAN) ? '1' : \
        (cn_BUILD_MONTH_IS_FEB) ? '2' : \
        (cn_BUILD_MONTH_IS_MAR) ? '3' : \
        (cn_BUILD_MONTH_IS_APR) ? '4' : \
        (cn_BUILD_MONTH_IS_MAY) ? '5' : \
        (cn_BUILD_MONTH_IS_JUN) ? '6' : \
        (cn_BUILD_MONTH_IS_JUL) ? '7' : \
        (cn_BUILD_MONTH_IS_AUG) ? '8' : \
        (cn_BUILD_MONTH_IS_SEP) ? '9' : \
        (cn_BUILD_MONTH_IS_OCT) ? '0' : \
        (cn_BUILD_MONTH_IS_NOV) ? '1' : \
        (cn_BUILD_MONTH_IS_DEC) ? '2' : \
        /* error default */ '?' \
    )

#define cn_BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define cn_BUILD_DAY_CH1 (__DATE__[ 5])

// #define cn_CHAR_TO_INT(alpha) alpha - cn_ASCII_OFFSET

// Example of __TIME__ string: "21:06:19"
//                              01234567
#define cn_BUILD_HOUR_CH0 (__TIME__[0])
#define cn_BUILD_HOUR_CH1 (__TIME__[1])

#define cn_BUILD_MIN_CH0 (__TIME__[3])
#define cn_BUILD_MIN_CH1 (__TIME__[4])

#define cn_BUILD_SEC_CH0 (__TIME__[6])
#define cn_BUILD_SEC_CH1 (__TIME__[7])


// Version major init
#if cn_VERSION_MAJOR > 99
    #define cn_VERSION_MAJOR_INIT \
    ((cn_VERSION_MAJOR / 100) + '0'), \
    (((cn_VERSION_MAJOR % 100) / 10) + '0'), \
    ((cn_VERSION_MAJOR % 10) + '0')
#elif cn_VERSION_MAJOR > 9
    #define cn_VERSION_MAJOR_INIT \
    ((cn_VERSION_MAJOR / 10) + '0'), \
    ((cn_VERSION_MAJOR % 10) + '0')
#else
    #define cn_VERSION_MAJOR_INIT \
    (cn_VERSION_MAJOR + '0')
#endif

// Version minor init
#if cn_VERSION_MINOR > 99
    #define cn_VERSION_MINOR_INIT \
    ((cn_VERSION_MINOR / 100) + '0'), \
    (((cn_VERSION_MINOR % 100) / 10) + '0'), \
    ((cn_VERSION_MINOR % 10) + '0')
#elif cn_VERSION_MINOR > 9
    #define cn_VERSION_MINOR_INIT \
    ((cn_VERSION_MINOR / 10) + '0'), \
    ((cn_VERSION_MINOR % 10) + '0')
#else
    #define cn_VERSION_MINOR_INIT \
    (cn_VERSION_MINOR + '0')
#endif


/// Version Cut macro
/// @note Added cut to example.
#if cn_VERSION_CUT > 99
    #define cn_VERSION_CUT_INIT \
    ((cn_VERSION_CUT / 100) + '0'), \
    (((cn_VERSION_CUT % 100) / 10) + '0'), \
    ((cn_VERSION_CUT % 10) + '0')
#elif cn_VERSION_CUT > 9
    #define cn_VERSION_CUT_INIT \
    ((cn_VERSION_CUT / 10) + '0'), \
    ((cn_VERSION_CUT % 10) + '0')
#else
    #define cn_VERSION_CUT_INIT \
    (cn_VERSION_CUT + '0')
#endif


/**
 * @brief gen_GetVersion() : Exported complete version string constant (inline for header definition).
 * @details Allows direct printing of versions string with build information.
 */
inline const char * gen_GetVersion(void)
{
    static const char sf_completeVersion[] =
    {
        'v',
        cn_VERSION_MAJOR_INIT,
        '.',
        cn_VERSION_MINOR_INIT,
        '.',
        cn_VERSION_CUT_INIT,
        ' ', 'D',
        cn_BUILD_DAY_CH0, cn_BUILD_DAY_CH1,
        '.',
        cn_BUILD_MONTH_CH0, cn_BUILD_MONTH_CH1,
        '.',
        cn_BUILD_YEAR_CH2, cn_BUILD_YEAR_CH3,
        ' ',
        'T',
        cn_BUILD_HOUR_CH0, cn_BUILD_HOUR_CH1,
        ':',
        cn_BUILD_MIN_CH0, cn_BUILD_MIN_CH1,
        ':',
        cn_BUILD_SEC_CH0, cn_BUILD_SEC_CH1,
        '\0'
    };

    // return pointer to complete version string
    return sf_completeVersion;
}

// @note below values are used in the OCM packet construction for INFO replies
// Ascii offset used in calculations for date integers from string renders
#define cn_ASCII_OFFSET_VAL (0x30)
// Subtract ascii offset
#define NEG_AO_Mac(arg) (arg - cn_ASCII_OFFSET_VAL)

// Two character (string values) to integer macro
#define TWO_C2I_Mac(char_one, char_two) static_cast<uint8_t>((NEG_AO_Mac(char_one) * 10) + NEG_AO_Mac(char_two))

// Integer macros
#define cn_FW_COMPILE_YEAR_MSD    TWO_C2I_Mac(cn_BUILD_YEAR_CH0, cn_BUILD_YEAR_CH1)
#define cn_FW_COMPILE_YEAR_LSD    TWO_C2I_Mac(cn_BUILD_YEAR_CH2, cn_BUILD_YEAR_CH3)
#define cn_FW_COMPILE_MONTH       TWO_C2I_Mac(cn_BUILD_MONTH_CH0, cn_BUILD_MONTH_CH1)
#define cn_FW_COMPILE_DAY         TWO_C2I_Mac(cn_BUILD_DAY_CH0, cn_BUILD_DAY_CH1)

#endif // version_h
/********************************* end of file *****************************/

