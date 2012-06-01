/*
  Control the brightness of LEDs which parallel connected. Using similar mechanism of PWM, range from 0~255
 @author M Chen
 @author Q Chen
 */

// Pin 13 and 12 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 13;
int led2 = 12;
// the time that the LEDs remain on
float ledOnTime = 0;
// the time that the LEDs remain off, we choose 20 miliseconds because it the time that it can't distinguish the LEDs on or off. So t
// e total delay time is 20 miliseconds. But can be changed later.
float ledOffTime = 20;

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
  // use serial input to control the brightness, input should be 0~255 ratio
  if(Serial.available()){
    float brightRatio = Serial.parseFloat();
    //    int brightRatio = Serial.parseInt();
    if(brightRatio < 0 || brightRatio > 255)
      Serial.println("Invalid input");
    else{
      ledOnTime = 20 * brightRatio / 255;
      ledOffTime = 20 - ledOnTime;
    }
  }

  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(ledOnTime);               // wait for a second

  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
  delay(ledOffTime);          // wait for a second
}




