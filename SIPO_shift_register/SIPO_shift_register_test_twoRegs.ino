/**
 * Test 8 bit shift register, expecially for two registers connected together.
 */
//Pin connected to ST_CP of 74HC4094
const int latchPin = 8;
//Pin connected to SH_CP of 74HC4094
const int clockPin = 12;
////Pin connected to DS of 74HC4094
const int dataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop() {
  for (int thisLed = 0; thisLed < 16; thisLed++){
    registerWrite(thisLed, 1);
    delay(500);
    registerWrite(thisLed, 0);
  }
} 

/**
 * From tutorial: http://arduino.cc/en/Tutorial/ShftOut13
 */
void registerWrite(int whichPin, int whichState) {
  // the bits you want to send. Use an unsigned int,
  // so you can use all 16 bits:
  unsigned int bitsToSend = 0;  

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);  

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // break the bits into two bytes, one for 
  // the first register and one for the second:
  byte registerOne = highByte(bitsToSend);
  byte registerTwo = lowByte(bitsToSend);

  // shift the bytes out:
  shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
  shiftOut(dataPin, clockPin, MSBFIRST, registerOne);

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
}














