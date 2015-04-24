#include <TinyWireS.h>


#define SLAVE_ADDRESS 0x04
//#define LED1_PIN         4              // ATtiny Pin 3
#define LED2_PIN         1              // ATtiny Pin 6


void setup(){
  //pinMode(LED1_PIN,OUTPUT);             // for general DEBUG use
  pinMode(LED2_PIN,OUTPUT);             // for verification
  Blink(LED2_PIN,2);                    // show it's alive
  TinyWireS.begin(SLAVE_ADDRESS);
}

void loop(){
  byte byteRcvd = 0;
  if(TinyWireS.available()){
    byteRcvd = TinyWireS.receive();
    
    TinyWireS.send(byteRcvd);
    Blink(LED2_PIN, byteRcvd);                  // show we transmitted

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
}

void Blink(byte led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (25);
    digitalWrite(led,LOW);
    delay (17);
  }
}

