#ifndef SERIAL_H
#define SERIAL_H

#include "ProIO.h"
#include <stdlib.h>





class Serial{
private:

;
public:
  void begin(int32_t baudrate);
  void write(char message);
  unsigned char read();
  void end();
  unsigned char *buffer;
  uint8_t bufferCount;
  uint8_t currentBufferPoint;
;
};
extern Serial Serial0;

#endif