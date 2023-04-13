#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include <ctime>
LiquidCrystal_I2C lcd( 0x27,16, 2);
word r_eg_mas[3] {100,500,1000};
word e_eg_mas[3] {100,150,250};
float r_eg;
float e_eg;
float rn;
float I;
float U;
char buffer[6];




void setup(){ 
 randomSeed(analogRead(PA1));
 
  pinMode(PA0,INPUT);
  pinMode(PB10,INPUT);
  srand(time(NULL));
  lcd.init(); 
  r_eg=r_eg_mas[random(0,3)];
   e_eg=e_eg_mas[random(0,3)];

  lcd.backlight();
  
}

void loop() {
  int tumbler_state=digitalRead(PB10);

  if(tumbler_state==1)
  {
    rn=analogRead(PA0)*((10*r_eg)/4096);
    delay(100);
      I=(e_eg)/(r_eg+rn);
      U=rn*I;
    lcd.setCursor(10,0);
    lcd.print("I");
    lcd.setCursor(12,0);
    lcd.print(I*1000);
    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(2,1);
    dtostrf(U, 4, 1, buffer);
    lcd.print(buffer);
  }else
  {
    I=0;
    U=e_eg;
    lcd.setCursor(10,0);
    lcd.print("I");
    lcd.setCursor(12,0);
    lcd.print(I);
    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(2,1);
    dtostrf(U, 4, 1, buffer);
    lcd.print(buffer);
  }
  
 
}
