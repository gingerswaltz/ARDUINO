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


int digits[10][7] = {            // Массив, хранящий информацию о том, какие сегменты должны быть включены для каждой цифры
  {1,1,1,1,1,1,0},            // 0
  {0,1,1,0,0,0,0},            // 1
  {1,0,1,1,1,0,1},            // 2
  {1,1,1,1,0,0,1},            // 3
  {0,1,1,0,0,1,1},            // 4
  {1,1,0,1,0,1,1},            // 5
  {1,1,0,1,1,1,1},            // 6
  {1,1,1,0,0,0,0},            // 7
  {1,1,1,1,1,1,1},            // 8
  {1,1,1,1,0,1,1}             // 9
};


// the loop function runs over and over again forever
void loop() {

int potValue = analogRead(POTENTIOMETER_PIN);    // Считываем значение с потенциометра
  digit1 = map(potValue, 0, 4095, 0, 10);    // Преобразуем первую цифру в диапазон от 0 до 9
  digit2 = digit1 + 1;                    // Вычисляем вторую цифру как следующую после первой
  
  // Ограничиваем вторую цифру диапазоном от 0 до 9
  
  if (digit2>9)
  {
      for (int i = 0; i < 9; i++) {
        digitalWrite(segPins[i], digits[digit1][i]);
      } 
      digitalWrite(PB1, HIGH);
      digitalWrite(PB0, LOW);
  }else
  {
      digitalWrite(PB1, LOW);

    }
  
  // Отображаем первую цифру на левом индикаторе
  for (int i = 0; i < 9; i++) {
    digitalWrite(segPins[i], digits[digit1][i]);
  }
  
  // Отображаем вторую цифру на правом индикаторе
  for (int i = 0; i < 6; i++) {
    digitalWrite(segPins[i], digits[digit1][i]);
  }
 delay(100);
}
