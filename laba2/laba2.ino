#include "LiquidCrystal_I2C.h" // библиотека для экранчика..

#include <TM1637.h>

const double pi = 3.14;
LiquidCrystal_I2C lcd(0x27, 20, 4); // инициализация объекта lcd
TM1637 tm1637(PB8, PB9); // объект 7 сегментного 4 разрядного индикатора 

char buffer[6]; // для форматного вывода

int r_mas[4] = {
   50,
   75,
   100,
   150
};
int XL_mas[5] = {
   200,
   250,
   300,
   350,
   400
};
double r, XL;
double u = 50;
double _xx = 0;

void setup() {

   randomSeed(analogRead(PB1)); // задаем зерно рандомной генерации  
   r = r_mas[random(0, 4)]; // рандомное напряжение
   XL = XL_mas[random(0, 5)]; // рандомное XL
   tm1637.init();
   tm1637.set(7); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
   lcd.init(); // запускаем экран 
   lcd.backlight(); // Запускаем подсветку экрана
   pinMode(PA0, INPUT); // потенциометр
   pinMode(PB15, INPUT); // ключ (замыкаем-размыкаем)

}

// функция вывода на семисегментный дисп. чисел согласно потенциометра
void PotCheck(int digit) {
   int digit_ed = digit % 10;
   if (digit > 9) {
      tm1637.display(1, digit / 10);
      tm1637.display(2, digit_ed);
   } else {
      tm1637.display(1, 0);
      tm1637.display(2, digit);
   }

}

void loop() {

   int xc;

   int digit; // число - ёмкость
   double Ur;
   double UL;
   int U1;
   int U2;
   double Z;
   double I;

   // считываем состояние ключа
   int tumbler_state = digitalRead(PB15);
   if (tumbler_state > 0) {
      tm1637.clearDisplay(); // очищаем дисплей
      tm1637.set(0); // выключаем его
      xc = 0;
      U2 = 0;

   } else {
      digit = map(analogRead(PA0), 20, 4095, 1, 21); // считываем число
      digit = constrain(digit, 1, 20); // диапазон 1..20
      xc = (1000000) / (2 * pi * 50 * digit);
      tm1637.set(7); // ставим макс яркость

      PotCheck(digit); // и закидываем число на семисегментный
   }

   /// на случай если вдруг откажет или пропадёт семисегментный, можно выводить на lcd  

   //lcd.setCursor(7,1);
   //    lcd.print("C");
   //    lcd.setCursor(8,1);
   //    lcd.print(":");
   //    lcd.setCursor(9,1);
   //    lcd.print(digit/10);
   //    lcd.setCursor(10,1);
   //    lcd.print(digit%10);
   //    lcd.setCursor(11,1);
   //    lcd.print("mF");    

   _xx = XL - xc;
   Z = sqrt(r * r + _xx * _xx);
   I = (u / Z);
   lcd.setCursor(0, 3);
   lcd.print("A1");
   lcd.setCursor(1, 3);
   lcd.print(":");
   lcd.setCursor(2, 3);
   dtostrf(I, 1, 3, buffer); // Формат до 3 знака после запятой
   lcd.print(buffer);
   lcd.print(" ");

   double P = (I * I) * r;
   lcd.setCursor(0, 0);
   lcd.print("W");
   lcd.setCursor(1, 0);
   lcd.print(":");
   lcd.setCursor(2, 0);
   dtostrf(P, 2, 2, buffer); // Формат до 2 знака после запятой
   lcd.print(buffer);
   lcd.print(" ");

   UL = I * XL;
   Ur = I * r;
   U1 = sqrt((Ur * Ur) + (UL * UL));
   U2 = I * xc;

   lcd.setCursor(14, 0);
   lcd.print("V");
   lcd.setCursor(15, 0);
   lcd.print("1");
   lcd.setCursor(16, 0);
   lcd.print(":");
   lcd.setCursor(17, 0);
   lcd.print(U1 / 100);
   lcd.setCursor(18, 0);
   lcd.print((U1 / 10) % 10);
   lcd.setCursor(19, 0);
   lcd.print((U1 % 100) % 10);

   lcd.setCursor(14, 3);
   lcd.print("V");
   lcd.setCursor(15, 3);
   lcd.print("2");
   lcd.setCursor(16, 3);
   lcd.print(":");
   lcd.setCursor(17, 3);
   lcd.print(U2 / 100);
   lcd.setCursor(18, 3);
   lcd.print((U2 / 10) % 10);
   lcd.setCursor(19, 3);
   lcd.print((U2 % 100) % 10);
}
