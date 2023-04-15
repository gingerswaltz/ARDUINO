#include "LiquidCrystal_I2C.h" // библиотека для экранчика..
#include <Wire.h>             
#include <ctime>
LiquidCrystal_I2C lcd( 0x27,16, 2); // инициализация объекта lcd
word r_eg_mas[3] {100,500,1000};    // массив случайных значений Rэг
word e_eg_mas[3] {100,150,250};     // массив случайных значений Eэг
float r_eg;                         // Rэг
float e_eg;                         // Eэг
float rn;                           // Переменное сопротивление Rn
float I;                            // Сила тока
float U;                            // Напряжение
char buffer[6];                     // temp-переменная для форматного вывода





void tumblerCheck(){
  int tumbler_state=digitalRead(PB10);   // Считываем положение тумблера..

  if(tumbler_state==1)                   // Если включено, то у нас режим "КЗ"
  {
    rn=analogRead(PA0)*((10*r_eg)/4096);  // Считываем значение Rн с потенциометра
    delay(100);                           // Задержка для корректного вывода
      I=(e_eg)/(r_eg+rn);                 // Расчёт по формулам электротехники
      U=rn*I;
    
    lcd.setCursor(10,0);                  
    lcd.print("I");
    lcd.setCursor(11,0);  
    lcd.print(":");
    lcd.setCursor(12,0);
    lcd.print(I*1000);                    // вывод в мA
    

    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(1,1);
    lcd.print(":");
    lcd.setCursor(2,1);
    dtostrf(U, 4, 1, buffer);             // Формат до 1 знака после запятой
    lcd.print(buffer);
  }else                                   // Иначе у нас режим "ХХ"    
  {
    I=0;                                  // зададим константы I и U
    U=e_eg;
    lcd.setCursor(10,0);
    lcd.print("I");
    lcd.setCursor(11,0);
    lcd.print(":");
    lcd.setCursor(12,0);
    lcd.print(I);
    

    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(1,1);
    lcd.print(":");
    lcd.setCursor(2,1);
    dtostrf(U, 4, 1, buffer);
    lcd.print(buffer);
  }
}





void setup(){ 
  pinMode(PA0,INPUT);               // пин потенциометра
  pinMode(PB10,INPUT);              // пин переключателя режима "КЗ-ХХ"
 
 randomSeed(analogRead(PB10));      // задаем зерно рандомной генерации  
             
  lcd.init();                       // запускаем экран 
  lcd.backlight();                  // Запускаем подсветку экрана
  r_eg=r_eg_mas[random(0,3)];       // рандомно выбираем значение Rэг
   e_eg=e_eg_mas[random(0,3)];      // рандомно выбираем значение Eэг
  
}

void loop() {
  
  tumbler_check();
}
