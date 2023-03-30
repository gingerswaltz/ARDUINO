// the setup function runs once when you press reset or power the board
const int POTENTIOMETER_PIN = PA7;
const int SEGMENT_A_PIN = PB9;
const int SEGMENT_B_PIN = PB5;
const int SEGMENT_C_PIN = PB4;
const int SEGMENT_D_PIN = PB6;
const int SEGMENT_E_PIN = PB7;
const int SEGMENT_F_PIN = PB8;
const int SEGMENT_G_PIN = PB3;
//
//
//
void setup() {
  // initialize digital pin PB1 as an output.
  Serial.begin(9600);
  pinMode(PA7, INPUT);
  pinMode(PB3, OUTPUT); // g
  pinMode(PB4, OUTPUT); // c
  pinMode(PB5, OUTPUT); // b
  pinMode(PB6, OUTPUT); // d
  pinMode(PB7, OUTPUT); // e
  pinMode(PB8, OUTPUT); // f
  pinMode(PB9, OUTPUT); // a
}


int digit=0;

// the loop function runs over and over again forever
void loop() {

int potValue=analogRead(POTENTIOMETER_PIN);

int mappedValue=map(potValue, 0, 4095, 0, 10);
if (mappedValue!=digit) digit=mappedValue;

switch (digit){
  case 0:
   digitalWrite(PB9, HIGH);
        digitalWrite(PB8, HIGH);
        digitalWrite(PB7, HIGH);
        digitalWrite(PB6, HIGH);
        digitalWrite(PB5, HIGH);
        digitalWrite(PB4, HIGH);
        digitalWrite(PB3, LOW);
        break;

    case 1: 
        digitalWrite(SEGMENT_A_PIN, LOW);
        digitalWrite(SEGMENT_B_PIN, HIGH);
        digitalWrite(SEGMENT_C_PIN, HIGH);
        digitalWrite(SEGMENT_D_PIN, LOW);
        digitalWrite(SEGMENT_E_PIN, LOW);
        digitalWrite(SEGMENT_F_PIN, LOW);
        digitalWrite(SEGMENT_G_PIN, LOW);
        break;
}

}
