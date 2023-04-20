// the setup function runs once when you press reset or power the board
const int POTENTIOMETER_PIN = PA7;
const int SEGMENT_A_PIN = PB9;
const int SEGMENT_B_PIN = PB5;
const int SEGMENT_C_PIN = PB4;
const int SEGMENT_D_PIN = PB11;
const int SEGMENT_E_PIN = PB10;
const int SEGMENT_F_PIN = PB8;
const int SEGMENT_G_PIN = PB3;


//todo: dot pin , second display pins??
int segPins[] = {PB9, PB5, PB4, PB11, PB10, PB8, PB3};   // Пины сегментов первого индикатора (в порядке a,b,c,d,e,f,g,  ??dp)
int segPins2[] = {}; // Пины сегментов второго индикатора
int digit1, digit2;              // Переменные для хранения первой и второй цифр



//
//
//
void setup() {
  Serial.begin(9600);
  pinMode(PB13, OUTPUT);
  pinMode(PB15, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(SEGMENT_G_PIN, OUTPUT); // g
  pinMode(SEGMENT_C_PIN, OUTPUT); // c
  pinMode(SEGMENT_B_PIN, OUTPUT); // b
  pinMode(SEGMENT_D_PIN, OUTPUT); // d
  pinMode(SEGMENT_E_PIN, OUTPUT); // e
  pinMode(SEGMENT_F_PIN, OUTPUT); // f
  pinMode(SEGMENT_A_PIN, OUTPUT); // a
  pinMode(PB1, OUTPUT);
  pinMode(PB0, OUTPUT);
  
}


byte digits[] = { 
 0b11000000, // 0 
 0b11111001, // 1 
 0b10100100, // 2 
 0b10110000, // 3 
 0b10011001, // 4 
 0b10010010, // 5 
 0b10000010, // 6 
 0b11111000, // 7 
 0b10000000, // 8 
 0b10010000 // 9 
};


void displayDigit(byte digit, int digitPin, int segPins[]){
  for (int i=0; i<7; i++){
    if (digit &(1<<i)){
      digitalWrite(segPins[i], HIGH);
    }else {
      digitalWrite(segPins[i], LOW);
    }
  }

  digitalWrite(digitPin, LOW);
  delayMicroseconds(500);
  digitalWrite(digitPin, HIGH);
}

// the loop function runs over and over again forever
void loop() {

int angle =map(analogRead(POTENTIOMETER_PIN), 1, 4095, 0, 20); // Считываем значение с потенциометра
 Serial.println(angle);
  Serial.println(angle%10);
  ////digit1 =     // Преобразуем первую цифру в диапазон от 0 до 9
//  digit2 = digit1 + 1;                    // Вычисляем вторую цифру как следующую после первой
 displayDigit(digits[4], PB14, segPins); 
}
