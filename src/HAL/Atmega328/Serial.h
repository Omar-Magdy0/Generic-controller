#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <stdlib.h>


#define TX_BUFFER_SIZE 32
#define RX_BUFFER_SIZE 32
typedef int8_t tx_buffer_index_t;
typedef int8_t rx_buffer_index_t;

struct Serial{
public:
  void begin(int32_t baudrate);
  void write(char c);
 // unsigned char read();
  void end();
  void print(const char text[]);
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




#endif