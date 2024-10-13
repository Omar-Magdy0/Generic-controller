#include "core.h"

#define TEST(n,b) (!!((n)&_BV(b)))

void _SerialValidateMessage(){
    Serial.print(F("OK"));
    Serial.write('\n');
}

void _SerialErrorMessage(){
    Serial.print(F("ERR"));
    Serial.write('\n');
}





dataVals _SerialGetValue(unsigned char c){
    char _Serial[10];
    dataVals data;
    while(Serial.available() > 0){
        data.c = Serial.read();
        if(data.c){
            Serial.readBytesUntil(c,_Serial,10);
            data.value = atof(_Serial);
            return data;
        }
    }
    data.c = -1;
    return data;
}

void _SerialReturnValue(char c,float val){
    Serial.write(c);
    Serial.print(val,3);
    Serial.print('\n');
}