#include <TimerOne.h>


/**
 * Brightness Control: to control the brightness of multiple LEDs (16) parallel connected, by switching the LEDs on and off frequently. Brightness ranging from 0~255.
 * Time Control, to use the library.
 */

// 8 bit shif register setting
//Pin connected to ST_CP of 74HC4094
const int latchPin = 8;
//Pin connected to SH_CP of 74HC4094
const int clockPin = 12;
//Pin connected to DS of 74HC4094
const int dataPin = 11;

// number of LEDs
const int numLED = 16;
// accumulator
unsigned int accumulator[numLED];

// brightness of 16 LEDs
unsigned int brightness[numLED];

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // initialize accumlator and brightness
  for(int thisLED = 0; thisLED < numLED; thisLED++){
    accumulator[thisLED] = 0;
    brightness[thisLED] = 0;
  }

  // initialize the library function
  Timer1.initialize();
  // for every interval time, generates an interrupt, call external function
  Timer1.attachInterrupt(controlBrightness, 2000);

  Serial.begin(9600);
}

void loop() {
  for (int thisLED = 0; thisLED < numLED; thisLED++){
    if(brightness[thisLED] > 255 ){
      brightness[thisLED] = 0;
    }
    if(brightness[thisLED] < 0){
      brightness[thisLED] = 0;
    }
    //    brightness[thisLED] += thisLED;
    brightness[thisLED] += 5;
  }

}

/**
 * From tutorial: http://arduino.cc/en/Tutorial/ShftOut13
 */
void registerWrite(unsigned int bitsToSend) {
  // the bits you want to send. Use an unsigned int,
  // so you can use all 16 bits:
  //  unsigned int bitsToSend = 0;  

  // turn on the next highest bit in bitsToSend:
  //  bitWrite(bitsToSend, whichPin, whichState);  

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

// for each interval, upgrad each LEDs
void controlBrightness(){  
  unsigned int bitsToSend = 0;

  // to set the LEDs on and off according with the input brightness
  for (int thisLED = 0; thisLED < numLED; thisLED++){
    accumulator[thisLED] = (accumulator[thisLED] + brightness[thisLED]) % 256;
    if(accumulator[thisLED] >= brightness[thisLED]){
      bitWrite(bitsToSend, thisLED, 1); 
    }
    else{
      bitWrite(bitsToSend, thisLED, 0); 
    }
  }

  digitalWrite(latchPin, LOW);

  byte registerOne = highByte(bitsToSend);
  byte registerTwo = lowByte(bitsToSend);

  shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
  shiftOut(dataPin, clockPin, MSBFIRST, registerOne);

  digitalWrite(latchPin, HIGH);
  
  // write to register
  //  registerWrite(bitsToSend); 
}













