//Pin connected to ST_CP of 74HC4094
int latchPin = 8;
//Pin connected to SH_CP of 74HC4094
int clockPin = 12;
////Pin connected to DS of 74HC4094
int dataPin = 11;
// Pin connected to OE of 74HC4094
int outputEnablePin = 7;

// accumulator
int acc = 0;  
int brightness = 0;

unsigned long prevTime = 0;
// set time interval 100 microseconds
unsigned long timePass = 4000;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);

  Serial.begin(115200);
  prevTime = micros();
}

void loop() {

  // to set the LEDs on and off according with the input birhgtness
  acc = (acc + brightness) % 256;

  if(acc >= brightness){
    digitalWrite(latchPin, LOW);
    digitalWrite(outputEnablePin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    digitalWrite(outputEnablePin, HIGH);
  }
  else{
    digitalWrite(latchPin, LOW);
    digitalWrite(outputEnablePin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 255);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    digitalWrite(outputEnablePin, HIGH);
  }

  unsigned long currentTime = micros();

  if(currentTime - prevTime >= timePass){
    noInterrupts();
    updateBrightness();
    interrupts();
    // save as previous time
    prevTime = currentTime;
    //    Serial.println(prevTime);
  }
} 

void updateBrightness(){
  if(brightness > 255)
    brightness = 0;
  else
    brightness++;
}






