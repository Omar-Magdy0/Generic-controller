#include "ControllerCore.h"
#include <string.h>
#include <util/delay.h>
extern uint16_t globalTimeMillis;
int main(){
  setupFunction();
  Serial0.begin(9600);
  clk0CountMillis(START);

  while (1)
  { _delay_ms(10);
    uint16_t time = millis();
    Serial0.print(212);
    Serial0.print('\n');
   }
  return 0;
}