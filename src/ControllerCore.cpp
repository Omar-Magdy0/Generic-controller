
#include "ControllerCore.h"




//Function definitions for functions that loop
 void idle(){
  getTime();
  Triac0.frequency_check();
  Serial.println(Triac0.getFrequency());
}


void setup(){
  setup_init();
  Triac0.init();
}

void loop(){
  idle();
  delay(100);
}
  
