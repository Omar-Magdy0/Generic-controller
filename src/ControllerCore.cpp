
#include "ControllerCore.h"
#include <Arduino.h>





//Function definitions for functions that loop
 void idle(){
  getTime();
}


void setup(){
  setup_init();
  Triac0.init();
  Triac0.set_power(250);

}



void loop(){
  // All thermistor temperature is in degrade.


  idle();
}
  
