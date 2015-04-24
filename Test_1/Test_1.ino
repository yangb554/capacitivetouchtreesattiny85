#include <CapacitiveSensor.h>
#include <TinyWireS.h>

#define SLAVE_ADDRESS 0x04

int state = 0;
CapacitiveSensor  cs_3_4 = CapacitiveSensor(3,4);

void setup(){
  pinMode(2, OUTPUT);
  cs_3_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  TinyWireS.begin(SLAVE_ADDRESS);
}

void loop(){
  byte byteRcvd = 0;
  analogWrite(2, HIGH);
  if(TinyWireS.available()){
    byteRcvd = TinyWireS.receive();
    if (byteRcvd == 1){
      byteRcvd = byteRcvd+10;
      TinyWireS.send(byteRcvd);
    }
    if (byteRcvd == 2){
       long start = millis();
       long total = cs_3_4.capacitiveSensor(30);
       byteRcvd = total;
       TinyWireS.send(byteRcvd);
    }
  }


