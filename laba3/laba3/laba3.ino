#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 20, 4); // Default address of most PCF8574 modules, change according

#include <TM1637.h>
TM1637 tm1637(2, 3); // объект 7 сегментного 4 разрядного индикатора 
char buffer[6]; // для форматного вывода

float a1;
float a2;
float a3;
float w;
float I1[2];
float I2[2];
float I3[2];
float Xc;
int c;
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


void output(float a1, float a2, float a3, float w){
  
   lcd.setCursor(0, 0);
   lcd.print("W");
   lcd.setCursor(1, 0);
   lcd.print(":");
   lcd.setCursor(2, 0);
   dtostrf(w, 2, 3, buffer); // Формат до 2 знака после запятой
   lcd.print(buffer);
   lcd.print("  ");
   
   lcd.setCursor(10, 0);
   lcd.print("A");
   lcd.setCursor(11, 0);
   lcd.print("1");
   lcd.setCursor(12, 0);
   lcd.print(":");
   lcd.setCursor(13, 0);
   dtostrf(a1, 2, 3, buffer); // Формат до 2 знака после запятой
   lcd.print(buffer);
   lcd.print("  ");

   lcd.setCursor(10, 1);
   lcd.print("A");
   lcd.setCursor(11, 1);
   lcd.print("2");
   lcd.setCursor(12, 1);
   lcd.print(":");
   lcd.setCursor(13, 1);
   dtostrf(a2, 2, 3, buffer); // Формат до 2 знака после запятой
   lcd.print(buffer);
   lcd.print("  ");

lcd.setCursor(10, 2);
   lcd.print("A");
   lcd.setCursor(11, 2);
   lcd.print("3");
   lcd.setCursor(12, 2);
   lcd.print(":");
   lcd.setCursor(13, 2);
   dtostrf(a3, 2, 3, buffer); // Формат до 2 знака после запятой
   lcd.print(buffer);
   lcd.print("  ");

}

// сумма компл чисел
void sum_complex(  float * a,   float * b,   float * c) {
   c[0] = a[0] + b[0];
   c[1] = a[1] + b[1];
}




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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
randomSeed(analogRead(9)); // задаем зерно рандомной генерации  
   r = r_mas[random(0, 4)]; // рандомное напряжение
   XL = XL_mas[random(0, 5)]; // рандомное XL
   pinMode(A6, INPUT);
   tm1637.init();
   tm1637.set(7); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();

}

void loop() {
c = map(analogRead(A6), 0, 1023, 0, 21); // считываем числ
c = constrain(c, 0, 20); // диапазон 1..20
Serial.println(analogRead(A6));
PotCheck(c);
delay(150);
Xc=(1000000)/(314*c);

if (c==0){
  I3[0]=0;
  I3[1]=0;
  
  a3=0;
  a2=50/sqrt((r*r)+(XL*XL));
  a1=a2;
  w=(a2*a2)*r;
  
  output(a1,a2,a3,w);

}else
{
  I3[0]=0;
  I3[1]=50/Xc;
  
  I2[0]=(50*r)/((r*r)+(XL*XL));
  I2[1]=((XL*50)/((r*r)+(XL*XL)))*-1;
  sum_complex(I2, I3, I1);

a1=sqrt((I1[0]*I1[0])+(I1[1]*I1[1]));
a2=sqrt((I2[0]*I2[0])+(I2[1]*I2[1]));
a3=sqrt((I3[0]*I3[0])+(I3[1]*I3[1]));
w=(a2*a2)*r;

output(a1,a2,a3,w);
}



}
