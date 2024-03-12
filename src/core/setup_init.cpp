#include "setup_init.h"
#include "../Config.h"
#include "../Features/Features.h"

void  setup_init(){
    Serial.begin(9600);
    _delay_ms(50);
    
    #if _display_ > 0
    screen.init();
    #endif


    Serial.print("wakeup");

}

