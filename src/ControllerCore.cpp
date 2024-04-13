
#include "ControllerCore.h"
#include <Arduino.h>





//Function definitions for functions that loop
 void idle(){
  getTime();
  HOTAIR_0.loop_func();
}


void setup(){
  setup_init();
  HOTAIR_0.init();
}



void loop(){
  idle();
}
  
