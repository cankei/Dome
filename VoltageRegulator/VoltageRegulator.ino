/* 
 Each channel's pins are labeled
 A - connect this to voltage
 W - this is the pot's wiper, which changes when you set it
 B - connect this to ground.
 
 to command it, you send two bytes, 
 one with the channel number (0) and one with the resistance value for the
 channel (0 - 255).  
 
 The circuit:
 * CS - to digital pin 10  (SS pin)
 * SDI - to digital pin 11 (MOSI pin)
 * SDO - to digital pin 12 (MISO pin)
 * CLK - to digital pin 13 (SCK pin)
 
 LM2678
 #7 pin on/off - to digital pin D9
 
 */


// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
const int switchConverter = 9;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  pinMode (switchConverter, OUTPUT);

  //  digitalWrite(switchConverter, HIGH);

  // initialize SPI:
  SPI.begin(); 
}

void loop() {

  // to address 0, value 255 to its maximum resistor
  digitalWrite(switchConverter, HIGH);

  digitalPotWrite(0, 63);

  // change the resistance on this channel from max to min:
  //    for (int level = 0; level < 255; level++) {
  //      digitalPotWrite(channel, 255 - level);
  //      delay(10);
  //    }
}

int digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 
}





