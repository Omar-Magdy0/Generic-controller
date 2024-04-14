#pragma once 

#include <stdint.h>

struct _eeprom{
virtual void read(int pos, char *c, uint8_t size);
virtual float readFloat(int pos);
virtual int readInt(int pos);
virtual char readChar(int pos);

virtual void write(int pos, char *c, uint8_t size);
virtual void writeFloat(int pos,float f);
virtual void writeInt(int pos, int val);
virtual void writeChar(int pos, int val);
};