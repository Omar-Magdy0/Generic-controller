#pragma once

#include "avr/eeprom.h"
#include "../shared/EEPROM.h"
#include "EEPROM.h"
#include <EEPROM.h>

#if defined CUSTOM_EEPROM
struct eeprom :public _eeprom{
    void read(int pos, char *c, uint8_t size);
    float readFloat(int pos);
    int readInt(int pos);
    char readChar(int pos);

    void write(int pos, char *c, uint8_t size);
    void writeFloat(int pos,float f);
    void writeInt(int pos, int val);
    void writeChar(int pos, int val);
} EEPROM;
#endif


