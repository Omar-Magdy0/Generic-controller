#include "core.h"

#define TEST(n,b) (!!((n)&_BV(b)))

inline void validateMessage(){
    Serial.print(F("OK"));
}





dataVals _SerialGetValue(){
    char _Serial[10];
    dataVals data;
    while(Serial.available() > 0){
        if(data.c = Serial.read()){
            Serial.setTimeout(100);
            Serial.readBytesUntil('\r',_Serial,10);
            data.value = atoi(_Serial);
            return data;
        }
    }
    data.c = 0;
    return data;
}
