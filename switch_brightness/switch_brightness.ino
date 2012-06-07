// dip switch brightness 

// Arduino pins used for the LEDs
#define LED1 13
#define LED2 12
#define LED3 11

// Arduino pins used for the switches
#define S1 9
#define S2 8
#define S3 7
#define S4 6
#define S5 5
#define S6 4
#define S7 3
#define S8 2

// State of each switch (0 or 1)
int s1state;
int s2state;
int s3state;
int s4state;
int s5state;
int s6state;
int s7state;
int s8state;

int acc = 0;  
int brightness = 0;

void setup() {
  // pins for LEDs are outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  // pins for switches are inputs
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);
  // setup serial port
  Serial.begin(115200);
  Serial.println("Serial port open");
}

void loop() {
  s1state = digitalRead(S1);
  s2state = digitalRead(S2);
  s3state = digitalRead(S3);
  s4state = digitalRead(S4);
  s5state = digitalRead(S5);
  s6state = digitalRead(S6);
  s7state = digitalRead(S7);
  s8state = digitalRead(S8);

  brightness = s8state + s7state*2 + s6state*2*2 + s5state*2*2*2 + s4state*2*2*2*2 + s3state*2*2*2*2*2 + s2state*2*2*2*2*2*2 + s1state*2*2*2*2*2*2*2;

//  Serial.print(s1state);
//  Serial.print(s2state);
//  Serial.print(s3state);
//  Serial.print(s4state);
//  Serial.print(s5state);
//  Serial.print(s6state);
//  Serial.print(s7state);
//  Serial.print(s8state);
//  Serial.print(" = ");
//  Serial.print(brightness);
//  Serial.println();

  acc = (acc + brightness) % 256;

  if(acc >= brightness){
    digitalWrite(LED1, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED2, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED3, LOW);   // turn the LED off by making the voltage LOW
  }
  else{
    digitalWrite(LED1, HIGH);    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED2, HIGH);    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED3, HIGH);    // turn the LED on (HIGH is the voltage level)
  }
}

