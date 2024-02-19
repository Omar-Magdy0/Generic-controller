#include "Serial.h"
#include "avr/interrupt.h"

Serial Serial0;

void Serial::begin(int32_t baudrate){
  //ENABLE UART INTERRUPTS and Peripheral
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
  //Async mode / no parity
  UCSR0B &= ~(1 << UDRIE0); 
  UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01) | (1 << UPM01) |
    (1 << UPM00) | (1 << USBS0) | (1<< UCSZ02));
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
  UBRR0 = baudrate;

//Malloc some bytes for buffer
  buffer = (uint8_t *)malloc(32);
}

void Serial::end(){
  UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));
  free(buffer);
}


  

void Serial::write(char message){
  buffer[bufferCount] = message;
  bufferCount++;
  UCSR0B |= (1 << UDRIE0);

}
#include <Arduino.h>
ISR(USART0_UDRE_vect){
    if((Serial0.bufferCount > 0) && (UCSR0A & (1 << TXC0))){
        UDR0 = Serial0.buffer[Serial0.currentBufferPoint];
        Serial0.currentBufferPoint++;
        Serial0.bufferCount--;
    }
   
}
    