#pragma once

#include "avr/eeprom.h"

void EEPROM_READ(int pos,const char *data,uint8_t size);
void EEPROM_WRITE(int pos, const char *data, uint8_t size);