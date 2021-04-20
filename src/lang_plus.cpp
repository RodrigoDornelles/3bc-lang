#include "3bc.h"
#ifdef _3BC_ARDUINO
#include "Arduino.h"
#endif

/**
 * functions call's adaptations for C++ code
 * to be recognized by C code.
 * 
 * (required for avr compiler in arduino ide)
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _3BC_ARDUINO
void arduino_serial_begin()
{
    Serial.begin(9600);
}

void arduino_serial_print(unsigned char serial, const char* string)
{
    Serial.print(string);
}
#endif

#ifdef __cplusplus
}
#endif