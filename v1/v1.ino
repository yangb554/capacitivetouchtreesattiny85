/* ATtiny85 as an I2C Slave            BroHogan                           1/12/11
 * Example of ATtiny I2C slave receiving and sending data to an Arduino master.
 * Gets data from master, adds 10 to it and sends it back.
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = I2C SDA on DS1621  & GPIO        ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = I2C SCK on DS1621  & GPIO        ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * Current Rx & Tx buffers set at 32 bytes - see usiTwiSlave.h
 * Credit and thanks to Don Blake for his usiTwiSlave code. 
 * More on TinyWireS usage - see TinyWireS.h
 */


#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <CapacitiveSensor.h>
#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38)
#define LED1_PIN         0 // ATtiny Pin 3

CapacitiveSensor cs_3_4 = CapacitiveSensor(3,4);

void setup(){
  pinMode(LED1_PIN,OUTPUT);             // for general DEBUG use
  cs_3_4.set_CS_AutocaL_Millis(0xFFFFFFFF);            
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}


void loop(){
  byte byteRcvd = 0;
  if (TinyWireS.available()){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    Touch();           
    byteRcvd += 10;                     // add 10 to what's received
    TinyWireS.send(byteRcvd);           // send it back to master
  }
}


void Touch(){
  long start = millis();
  long total = cs_3_4.capacitiveSensor(30);
  if (total > 25){
    TinyWireS.send(1);
  }
  if (total < 25){
    TinyWireS.send(0);
  }
}



