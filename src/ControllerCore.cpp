#include "HAL/HAL.h"

int main(){
   // setupFunction();
  SREG |= (1<<7);
  Serial0.begin(9600);
  char sad[] = "sadrage\n";

  for(int i = 0;sad[i] != '\0';i++)
  Serial0.write(sad[i]);




  while(1){
  }
  return 0;
}