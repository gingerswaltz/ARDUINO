#include "LiquidCrystal_I2C.h" // библиотека для экранчика..

LiquidCrystal_I2C lcd( 0x27,20, 4); // инициализация объекта lcd
char buffer [6];
byte digitsArr[10] = {
  0b00111111, //0
  0b00000110, //1 
  0b01011011, //2 
  0b01001111, //3 
  0b01100110, //4 
  0b01101101, //5 
  0b01111101, //6 
  0b00000111, //7 
  0b01111111, //8
  0b01101111, //9
};

int pause = 1;

void setup() 
{
  lcd.init();                       // запускаем экран 
  lcd.backlight();                  // Запускаем подсветку экрана
  for (int i=2;i<=13;i++){
      pinMode(i, OUTPUT);
  }
}

void showDigital (byte pos, byte digi){
  digitalWrite(pos+9, LOW);
  
  for (int i=12;i<=13;i++)
  {
      digitalWrite(i, HIGH);
  }
  digitalWrite(pos+9, LOW);
 delay(1);
 digitalWrite(pos+9, HIGH);
  for (int i=2;i<=9;i++)
  {
    digitalWrite(i, bitRead(digitsArr[digi], i-2));
  }   
}

void PotCheck(int digit){  
  int digit_ed=digit%10;
  if (digit>9)
  {
    showDigital (3, digit/10);
    showDigital (4, digit_ed);
  }else
  {
  showDigital (3, 0);
  showDigital (4, digit);
  }

}

void TumblerCheck(int digit){

  if (tumbler_state>0)
  {
      int capacity=(digit)*145;                
    lcd.setCursor(0,1);
    lcd.print("C=");
    lcd.setCursor(1,1);
    lcd.print(":");
    lcd.setCursor(2,1);
    dtostrf(capacity, 4, 1, buffer);             // Формат до 1 знака после запятой
    lcd.print(buffer);
    delay(10);
    lcd.setCursor(8,1);
    lcd.print("mkF");
  }
}

void loop() 
{
    
  int digit=map(analogRead(A0), 0, 1023, 1, 20);

  PotCheck(digit);
  
TumblerCheck(digit);

  
 
}
