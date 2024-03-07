#include "ControllerCore.h"
#include <string.h>
#include <util/delay.h>
#include <stdint.h>


extern uint16_t globalTimeMillis;


/*
DUMMY struct + OBJECT FOR C/C++ test USING AVR-GCC COMPILER
*/



int main(){
 
  setupFunction();
  Serial0.begin(9600);
  clk0CountMillis(START);
  _delay_ms(50);


  
  while (1)
  { _delay_ms(500);
   }
  return 0;
}
