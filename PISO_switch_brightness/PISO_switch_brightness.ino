// adjust brightness using dip switch via PISO

#define PIN_PL (13) //pin 13 on arduino goes to pin 1 of 74HC165
#define PIN_CP (12) //pin 12 on arduino goes to pin 2 of 74HC165
#define PIN_Q7 (11) //pin 11 on arduino goes to pin 9 of 74HC165
#define LED1 10

int acc = 0;  
int brightness = 0;
int j;
int value[8];

void setup() {
  pinMode(PIN_PL, OUTPUT);
  pinMode(PIN_CP, OUTPUT);
  pinMode(PIN_Q7, INPUT);

  digitalWrite(PIN_PL, HIGH);
  digitalWrite(PIN_CP, LOW);

  // pins for LEDs are outputs
  pinMode(LED1, OUTPUT);

  // setup serial port
  Serial.begin(9600);
  Serial.println("Serial port open");

  //load logic bits from the DIP switches
  digitalWrite(PIN_PL, LOW);  //LOAD BITS
  //reset "load" line, this freezes the internal buffer on both chips
  digitalWrite(PIN_PL, HIGH);

  for(j = 0 ; j < 8 ; j++)
  {
    value[j] = digitalRead(PIN_Q7);

    //read next "switch"
    digitalWrite(PIN_CP, HIGH);
    digitalWrite(PIN_CP, LOW);

    //print switch's value
    Serial.print(value[j]);
  }

  Serial.print(" = ");

  brightness =value[7]  + value[6]*2 + value[5]*2*2 + value[4]*2*2*2 + value[3]*2*2*2*2 + value[2]*2*2*2*2*2 + value[1]*2*2*2*2*2*2 + value[0]*2*2*2*2*2*2*2;

  Serial.print(brightness);
  Serial.println("");
  Serial.println("--------------");
}

void loop() {
  acc = (acc + brightness) % 256;

  if(acc >= brightness){
    digitalWrite(LED1, LOW);   // turn the LED off by making the voltage LOW
  }
  else{
    digitalWrite(LED1, HIGH);    // turn the LED on (HIGH is the voltage level)
  }
}
