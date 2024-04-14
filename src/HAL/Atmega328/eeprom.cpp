#include "eeprom.h"
 

#if defined CUSTOM_EEPROM
eeprom EEPROM;

void eeprom::read(int pos, char *c, uint8_t size){

}
float eeprom::readFloat(int pos){return 0;}
int eeprom::readInt(int pos){return 0;}
char eeprom::readChar(int pos){return 0;}
void eeprom::write(int pos, char *c, uint8_t size){
}
void eeprom::writeFloat(int pos,float f){}
void eeprom::writeInt(int pos, int val){}
void eeprom::writeChar(int pos, int val){}
#endif