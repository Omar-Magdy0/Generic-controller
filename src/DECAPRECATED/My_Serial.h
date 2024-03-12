#ifndef MY_SERIAL_H
#define MY_SERIAL_H
//#include "hal_settings.h"
#ifdef _customSerial

#include "../shared/Marduino.h"



#define TX_BUFFER_SIZE 32
#define RX_BUFFER_SIZE 32
typedef int8_t tx_buffer_index;
typedef int8_t rx_buffer_index;




class uart0 : public Print{
public:
  void begin(int32_t baudrate);
  size_t write(uint8_t);
  using Print::write;
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
  uart0(){};
;
};


extern uart0 Serial0;

#endif

#endif