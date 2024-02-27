#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include "avr/interrupt.h"
#include <stdlib.h>
#include <Print.h>

#define TX_BUFFER_SIZE 32
#define RX_BUFFER_SIZE 32
typedef int8_t tx_buffer_index_t;
typedef int8_t rx_buffer_index_t;




class Serial : public Print{
public:
  void begin(int32_t baudrate);
  size_t write(uint8_t);
  void end();
  unsigned char read();
  void readUntil(unsigned char* message,unsigned char c);
  unsigned char *tx_buffer;
  unsigned char *rx_buffer;
  uint8_t rx_buffer_head = 0;
  uint8_t rx_buffer_tail = 0;
  uint8_t tx_buffer_head = 0;
  uint8_t tx_buffer_tail = 0;
  void tx_complete_func();
  void rx_done_func();
  Serial(){};
;
};


extern Serial Serial0;

#endif