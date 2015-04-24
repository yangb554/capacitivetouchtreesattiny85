#include <TinyWireS.h>


#define SLAVE_ADDRESS 0x04
//#define LED1_PIN         4              // ATtiny Pin 3
#define LED2_PIN         1              // ATtiny Pin 6

//CapacitiveSensor   cs_3_4 = CapacitiveSensor(3,4);

void setup(){
  //pinMode(LED1_PIN,OUTPUT);             // for general DEBUG use
  pinMode(LED2_PIN,OUTPUT);             // for verification
  pinMode(3, OUTPUT);
  Blink(LED2_PIN,2);                    // show it's alive
//  cs_3_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  TinyWireS.begin(SLAVE_ADDRESS);
}

void loop(){
  byte byteRcvd = 0;
  if(TinyWireS.available()){
    byteRcvd = TinyWireS.receive();
    Blink(LED2_PIN, byteRcvd);                  // show we transmitted
    long start = millis();
    //long touch =  cs_3_4.capacitiveSensor(30);
    analogWrite(3, 100);
    TinyWireS.send(1);
    delay(1);
    /*
    if (byteRcvd == 1){
      byteRcvd = byteRcvd + 15;
      TinyWireS.send(byteRcvd);
    }
    if (byteRcvd == 2){
       long start = millis();
       long total = cs_3_4.capacitiveSensor(30);
       byteRcvd = total;
       TinyWireS.send(byteRcvd);
    }
    */
  }
  analogWrite(3,0);
}

void Blink(byte led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (25);
    digitalWrite(led,LOW);
    delay (17);
  }
}

