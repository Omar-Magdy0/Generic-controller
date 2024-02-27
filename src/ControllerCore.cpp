#include "ControllerCore.h"
#include <string.h>
#include <util/delay.h>



extern uint16_t globalTimeMillis;
int main(){
  setupFunction();
  Serial0.begin(9600);
  clk0CountMillis(START);
  

  while (1)
  { _delay_ms(100);
    Serial0.print("FUCK  YOU");
    Serial0.print('\n');
    
   }
  return 0;
}
