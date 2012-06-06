/*
  Control the brightness of LEDs which parallel connected. Using on and off frequency with the same of Arduino board,  range from 0~255. 
  Time control: to use the function micros(), which always return the current time. The return value is always multiple of four. When the difference of current time and previous time is larger than the interval we set, the brightness will increase by 1. Brightness will cycle from 0 to 255.
 @author M Chen
 @author Q Chen
 */

// Pin 13 and 12 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 13;
int led2 = 12;
// accumulator
int acc = 0;  
int brightness = 0;

unsigned long prevTime = 0;
// set time interval 100 microseconds
unsigned long timePass = 400;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);
  Serial.begin(115200);
  prevTime = micros();
}

void updateBrightness(){
  if(brightness > 255)
    brightness = 0;
  else
    brightness++;

  //  Serial.print(" Brightness is:");
  //  Serial.println(brightness);
}

// the loop routine runs over and over again forever:
void loop() {
  // to set the LEDs on and off according with the input birhgtness
  acc = (acc + brightness) % 256;

  if(acc >= brightness){
    digitalWrite(led1, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(led2, LOW);   // turn the LED off by making the voltage LOW
  }
  else{
    digitalWrite(led1, HIGH);    // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, HIGH);    // turn the LED on (HIGH is the voltage level)
  }

  unsigned long currentTime = micros();

  if(currentTime - prevTime >= timePass){
    noInterrupts();
    updateBrightness();
    interrupts();
    // save as previous time
    prevTime = currentTime;
    Serial.println(prevTime);
  }
}






















