#include <CapacitiveSensor.h>
#define led         1

CapacitiveSensor cs_3_4 = CapacitiveSensor(3,4);
void setup(){
  pinMode(led, OUTPUT);
  cs_3_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
}
void loop(){
  long start = millis();
  long total = cs_3_4.capacitiveSensor(30);
  if (total > 25){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
  
