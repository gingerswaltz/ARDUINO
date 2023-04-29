#include "LiquidCrystal_I2C.h" // библиотека для экранчика..
#include <Wire.h>
const double pi=3.14;
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

int r_mas[4]={50, 75, 100, 150};
int XL_mas[5]={200, 250, 300, 350, 400};
int r, XL;
 int u=50;
 double X;

int segPins[14]={0, 0, PB0, PB1, PB3, PB4, PB5, PB8, PB10, PB11, 0, 0, PB12, PB13}; //pb12, pb13 resistors
int pause = 1;
int xc=0;
void setup() 
{
  randomSeed(analogRead(PB9));      // задаем зерно рандомной генерации  
 r=r_mas[random(0,4)];
 XL=XL_mas[random(0,5)];
lcd.print("test");
 lcd.init();                       // запускаем экран 
 lcd.backlight();                  // Запускаем подсветку экрана
 Serial.begin(115200);
pinMode(PA5, INPUT);
pinMode(PA3, INPUT);
  for (int i=2;i<=13;i++){
      pinMode(segPins[i], OUTPUT);
  }
}

void showDigital (byte pos, byte digi){
  digitalWrite(segPins[pos+9], LOW);
  
  for (int i=12;i<=13;i++)
  {
      digitalWrite(segPins[i], HIGH);
  }
  digitalWrite(segPins[pos+9], LOW);
 delay(1);
 digitalWrite(segPins[pos+9], HIGH);
  for (int i=2;i<=9;i++)
  {
    digitalWrite(segPins[i], bitRead(digitsArr[digi], i-2));
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



void loop() 
{

int  digit=map(analogRead(PA5), 20, 4095, 1, 21);
digit=constrain(digit, 1, 20);
Serial.println(digitalRead(PA3));
    PotCheck(digit);

  
int tumbler_state=digitalRead(PA3); 
  if (tumbler_state>0)
  {

xc=0;
     
  } else {
    
  xc=(1000000/2*pi*50*digit);
  }
    
    X=XL-xc;
   
   double Z=sqrt(r*r+_X*_X);
   double I=(u/Z);
   lcd.setCursor(0,0);
    lcd.print("A1");
    lcd.setCursor(1,0);
    lcd.print(":");
    lcd.setCursor(2,0);
    dtostrf(I, 4, 1, buffer);             // Формат до 1 знака после запятой
    
    lcd.print(buffer);
    lcd.setCursor(7,0);
    lcd.print("v");
 
}
