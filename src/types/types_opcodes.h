#ifndef H_TYPES_OPCODES_TBC
#define H_TYPES_OPCODES_TBC

#include "types_primitive.h"

#define NILL ((tbc_register_t)0) /**< OPCODE: 0 **/
#define MODE ((tbc_register_t)7) /**< OPCODE: 7 **/
#define STRB ((tbc_register_t)1) /**< OPCODE: 1 **/
#define FREE ((tbc_register_t)1) /**< OPCODE: 1 **/
#define MATH ((tbc_register_t)1) /**< OPCODE: 1 **/
#define GOTO ((tbc_register_t)1) /**< OPCODE: 1 **/
#define NB02 ((tbc_register_t)1) /**< OPCODE: 1 **/
#define CALL ((tbc_register_t)1) /**< OPCODE: 1 **/
#define BACK ((tbc_register_t)1) /**< OPCODE: 1 **/
#define FAKE ((tbc_register_t)1) /**< OPCODE: 1 **/
#define STRO ((tbc_register_t)2) /**< OPCODE: 2 **/
#define ALOC ((tbc_register_t)2) /**< OPCODE: 2 **/
#define FGTO ((tbc_register_t)2) /**< OPCODE: 2 **/
#define NB08 ((tbc_register_t)2) /**< OPCODE: 2 **/
#define STOP ((tbc_register_t)2) /**< OPCODE: 2 **/
#define FRET ((tbc_register_t)2) /**< OPCODE: 2 **/
#define FCAL ((tbc_register_t)2) /**< OPCODE: 2 **/
#define REAL ((tbc_register_t)2) /**< OPCODE: 2 **/
#define STRI ((tbc_register_t)3) /**< OPCODE: 3 **/
#define MOFF ((tbc_register_t)3) /**< OPCODE: 3 **/
#define PULL ((tbc_register_t)3) /**< OPCODE: 3 **/
#define ZGTO ((tbc_register_t)3) /**< OPCODE: 3 **/
#define NB10 ((tbc_register_t)3) /**< OPCODE: 3 **/
#define ZRET ((tbc_register_t)3) /**< OPCODE: 3 **/
#define ZCAL ((tbc_register_t)3) /**< OPCODE: 3 **/
#define MICR ((tbc_register_t)3) /**< OPCODE: 3 **/
#define STRX ((tbc_register_t)4) /**< OPCODE: 4 **/
#define PGTO ((tbc_register_t)4) /**< OPCODE: 4 **/
#define MUSE ((tbc_register_t)4) /**< OPCODE: 4 **/
#define SPIN ((tbc_register_t)4) /**< OPCODE: 4 **/
#define NB16 ((tbc_register_t)4) /**< OPCODE: 4 **/
#define PRET ((tbc_register_t)4) /**< OPCODE: 4 **/
#define PCAL ((tbc_register_t)4) /**< OPCODE: 4 **/
#define MILI ((tbc_register_t)4) /**< OPCODE: 4 **/
#define STRC ((tbc_register_t)5) /**< OPCODE: 5 **/
#define NGTO ((tbc_register_t)5) /**< OPCODE: 5 **/
#define PUSH ((tbc_register_t)5) /**< OPCODE: 5 **/
#define NRET ((tbc_register_t)5) /**< OPCODE: 5 **/
#define NCAL ((tbc_register_t)5) /**< OPCODE: 5 **/
#define SECO ((tbc_register_t)5) /**< OPCODE: 5 **/

enum  ___tbc_cpumode_e {
    TBC_MODE_EMPUTY, /**< CPU MODE: 0**/
    TBC_MODE_DEBUG, /**< CPU MODE: 1**/
    TBC_MODE_STRING, /**< CPU MODE: 2**/
    TBC_MODE_INPUT, /**< CPU MODE: 3**/
    TBC_MODE_INPUT_SILENT, /**< CPU MODE: 4**/
    TBC_MODE_INPUT_PASSWORD, /**< CPU MODE: 5**/
    TBC_MODE_MEMORY, /**< CPU MODE: 6**/
    TBC_MODE_MEMORY_PTR, /**< CPU MODE: 7**/
    TBC_MODE_MEMORY_AUX, /**< CPU MODE: 8**/
    TBC_MODE_JUMP, /**< CPU MODE: 9**/
    TBC_MODE_CUSTOM_1, /**< CPU MODE: 10**/
    TBC_MODE_MATH_SUM, /**< CPU MODE: 11**/
    TBC_MODE_MATH_SUB, /**< CPU MODE: 12**/
    TBC_MODE_MATH_MUL, /**< CPU MODE: 13**/
    TBC_MODE_MATH_DIV, /**< CPU MODE: 14**/
    TBC_MODE_MATH_MOD, /**< CPU MODE: 15**/
    TBC_MODE_MATH_POWER, /**< CPU MODE: 16**/
    TBC_MODE_MATH_ROOT, /**< CPU MODE: 17**/
    TBC_MODE_MATH_ABS, /**< CPU MODE: 18**/
    TBC_MODE_MATH_MUL_ADD, /**< CPU MODE: 19**/
    TBC_MODE_CUSTOM_2, /**< CPU MODE: 20**/
    TBC_MODE_BITWISE_NOT, /**< CPU MODE: 21**/
    TBC_MODE_BITWISE_AND, /**< CPU MODE: 22**/
    TBC_MODE_BITWISE_OR, /**< CPU MODE: 23**/
    TBC_MODE_BITWISE_XOR, /**< CPU MODE: 24**/
    TBC_MODE_BITWISE_NAND, /**< CPU MODE: 25**/
    TBC_MODE_BITWISE_NOR, /**< CPU MODE: 26**/
    TBC_MODE_BITWISE_XNOR, /**< CPU MODE: 27**/
    TBC_MODE_BITWISE_LEFT, /**< CPU MODE: 28**/
    TBC_MODE_BITWISE_RIGHT, /**< CPU MODE: 29**/
    TBC_MODE_CUSTOM_3, /**< CPU MODE: 30**/
    TBC_MODE_BOOLEAN_NOT, /**< CPU MODE: 31**/
    TBC_MODE_BOOLEAN_AND, /**< CPU MODE: 32**/
    TBC_MODE_BOOLEAN_OR, /**< CPU MODE: 33**/
    TBC_MODE_BOOLEAN_XOR, /**< CPU MODE: 34**/
    TBC_MODE_BOOLEAN_NAND, /**< CPU MODE: 35**/
    TBC_MODE_BOOLEAN_NOR, /**< CPU MODE: 36**/
    TBC_MODE_BOOLEAN_XNOR, /**< CPU MODE: 37**/
    TBC_MODE_MATH_LOG_BASE, /**< CPU MODE: 38**/
    TBC_MODE_MATH_LOG_NATURAL, /**< CPU MODE: 39**/
    TBC_MODE_CUSTOM_4, /**< CPU MODE: 40**/
    TBC_MODE_PROCEDURE_RET, /**< CPU MODE: 41**/
    TBC_MODE_PROCEDURE, /**< CPU MODE: 42**/
    TBC_MODE_SLEEP, /**< CPU MODE: 43**/
    TBC_MODE_END /**< CPU MODE: 44**/
};

/** fist column of opcode **/
typedef tbc_u8_t tbc_register_t;
/** third column of opcode | cpu context **/
typedef enum  ___tbc_cpumode_e tbc_cpumode_et;

#endif
