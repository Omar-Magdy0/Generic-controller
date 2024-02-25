#include "Serial.h"
#include "avr/interrupt.h"

Serial Serial0;


void Serial::begin(int32_t baudrate){
  //ENABLE UART INTERRUPTS and Peripheral
  SREG &= ~(1 << SREG_I);
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  //Async mode / no parity
  UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01) | (1 << UPM01) |
    (1 << UPM00) | (1 << USBS0) | (1<< UCSZ02));
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
  UBRR0 = (F_CPU/(16 * baudrate)) - 1;

//Malloc some bytes for buffer
  tx_buffer = (uint8_t *)malloc(32);
  rx_buffer = (uint8_t *)malloc(32);


  SREG |= (1 << SREG_I);
}

void Serial::end(){
  UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));
  free(tx_buffer);
  free(rx_buffer);
}


size_t Serial::write(uint8_t c){
  tx_buffer_index_t i = (tx_buffer_head + 1) % TX_BUFFER_SIZE;
  tx_buffer[tx_buffer_head] = c;
  SREG &= ~(1 << SREG_I);
  tx_buffer_head = i;
  UCSR0B |= (1 << UDRIE0);
  SREG |= (1 << SREG_I);
  return 0;
}

/*
void Serial::print(const char text[]){
  for(int8_t i = 0;text[i] != '\0'; i++)write(text[i]);
}*/

unsigned char Serial::read(){
  if (rx_buffer_head == rx_buffer_tail){
    return -1;
  } else {
    unsigned char c = rx_buffer[rx_buffer_tail];
    rx_buffer_tail = (rx_buffer_index_t)(rx_buffer_tail + 1) % RX_BUFFER_SIZE;
    return c;
  }
}

void Serial::readUntil(unsigned char* message,unsigned char c){
  uint8_t i = 0;
  while (message[i] != c){
    message[i++] = read();
  }
}

void Serial::tx_complete_func(){

  unsigned char c = tx_buffer[tx_buffer_tail];
  tx_buffer_tail = (tx_buffer_tail + 1) % TX_BUFFER_SIZE;
  UDR0 = c;

  UCSR0A = ((UCSR0A) & ((1 << U2X0) | (1 << MPCM0))) | (1 << TXC0);

  if (tx_buffer_head == tx_buffer_tail) {
    // Buffer empty, so disable interrupts
    UCSR0B &= ~(1 << UDRIE0);
  }
}

void Serial::rx_done_func(){
  unsigned char c = UDR0;
  rx_buffer_index_t i = (unsigned int)(rx_buffer_head + 1) % RX_BUFFER_SIZE;
  if ( i != rx_buffer_tail){
    rx_buffer[rx_buffer_head] = c;
    rx_buffer_head = i;
  }

}


ISR(USART0_UDRE_vect){
  Serial0.tx_complete_func();
}
ISR(USART0_RX_vect){
  Serial0.rx_done_func();
}