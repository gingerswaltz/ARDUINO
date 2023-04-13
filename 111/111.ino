int numbers[] = {100, 250, 500, 750, 1000}; // объявление массива чисел



void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);

}

void loop() {
  int randomIndex = random(0, 5); // генерация случайного индекса от 0 до 4
  int randomNumber = numbers[randomIndex]; // получение случайного числа из массива по сгенерированному индексу
  Serial.println(randomNumber);
  delay(1000);
  }
