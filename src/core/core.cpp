#include "core.h"

#define TEST(n,b) (!!((n)&_BV(b)))

inline void validateMessage(){
    Serial.print(F("OK"));
}





dataVals _SerialGetValue(unsigned char c){
    char _Serial[10];
    dataVals data;
    while(Serial.available() > 0){
        if(data.c = Serial.read()){
            Serial.readBytesUntil(c,_Serial,10);
            data.value = atoi(_Serial);
            return data;
        }
    }
    data.c = 0;
    return data;
}
