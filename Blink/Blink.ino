// the setup function runs once when you press reset or power the board
//const int POTENTIOMETER_PIN = PA7;
//const int SEGMENT_A_PIN = PB9;
//const int SEGMENT_B_PIN = PB5;
//const int SEGMENT_C_PIN = PB4;
//const int SEGMENT_D_PIN = PB6;
//const int SEGMENT_E_PIN = PB7;
//const int SEGMENT_F_PIN = PB8;
//const int SEGMENT_G_PIN = PB3;


//todo: dot pin , second display pins??
int segPins[] = {PB9, PB5, PB4, PB6, PB7, PB8, PB3, ???};   // Пины сегментов первого индикатора (в порядке a,b,c,d,e,f,g,dp)
int segPins2[] = {???}; // Пины сегментов второго индикатора
int digit1, digit2;              // Переменные для хранения первой и второй цифр



//
//
//
void setup() {
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


int digits[10][8] = {            // Массив, хранящий информацию о том, какие сегменты должны быть включены для каждой цифры
  {1,1,1,1,1,1,0,0},            // 0
  {0,1,1,0,0,0,0,0},            // 1
  {1,1,0,1,1,0,1,0},            // 2
  {1,1,1,1,0,0,1,0},            // 3
  {0,1,1,0,0,1,1,0},            // 4
  {1,0,1,1,0,1,1,0},            // 5
  {1,0,1,1,1,1,1,0},            // 6
  {1,1,1,0,0,0,0,0},            // 7
  {1,1,1,1,1,1,1,0},            // 8
  {1,1,1,1,0,1,1,0}             // 9
};


// the loop function runs over and over again forever
void loop() {

int potValue = analogRead(potPin);    // Считываем значение с потенциометра
  digit1 = map(potValue, 0, 4095, 0, 10);    // Преобразуем первую цифру в диапазон от 0 до 9
  digit2 = digit1 + 1;                    // Вычисляем вторую цифру как следующую после первой
  
  // Ограничиваем вторую цифру диапазоном от 0 до 9
  if (digit2 > 9) {
    digit2 = 0;
  }
  
  // Отображаем первую цифру на левом индикаторе
  for (int i = 0; i < 8; i++) {
    digitalWrite(segPins[i], digits[digit1][i]);
  }
  digitalWrite(segPins[7], HIGH);   // Включаем десятичную точку у левого индикатора
  
  // Отображаем вторую цифру на правом индикаторе
  for (int i = 0; i < 8; i++) {
    digitalWrite(segPins[i + 8], digits[digit2][i]);
  }
  digitalWrite(segPins[15], HIGH);  // Включаем десятичную точку у правого индикатора

  delay(100);   // Задержка для стабилизации отображения на индикаторе
}
