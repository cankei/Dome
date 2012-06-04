/*
  Control the brightness of LEDs which parallel connected. Using on and off frequency with the same of Arduino board,  range from 0~255. Need to set up interrupt later.
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

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Input a number ranging from 0~255 ");
}

// the loop routine runs over and over again forever:
void loop() { 
  if(Serial.available()){
    int inputBright = Serial.parseInt();
    if(inputBright < 0 || inputBright > 255)
      Serial.println("Invalid input");
    else
      brightness = inputBright;
  }
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
}








