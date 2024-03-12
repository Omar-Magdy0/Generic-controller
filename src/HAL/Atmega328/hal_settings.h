#pragma once 

//DEFINE FOR CUSTOM SERIAL API
//#define _customSerial

//#define extra_small_buffers
#ifdef extra_small_buffers
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
#endif