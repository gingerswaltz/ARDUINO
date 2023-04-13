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

void setup(){ 
  Serial.begin(9600);
  pinMode(PA0,INPUT);
  pinMode(PB10,INPUT);
  srand(time(NULL));
  lcd.init(); 
  r_eg=1000;
  e_eg=100;
  lcd.backlight();
  
}

void loop() {
  int tumbler_state=digitalRead(PB10);
 //map(potValue, 0, 4095, 0, 10)
  if(tumbler_state==1)
  {
    rn=analogRead(PA0)*((10*r_eg)/4096);
    Serial.println(rn);
      I=(e_eg)/(r_eg+rn);
      U=rn*I;
  
    lcd.setCursor(10,0);
    lcd.print("I");
    lcd.setCursor(12,0);
    lcd.print(I);
    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(2,1);
    lcd.print(U);
  }else
  {
    lcd.setCursor(10,0);
    lcd.print("I");
    lcd.setCursor(12,0);
    lcd.print(0);
    lcd.setCursor(0,1);
    lcd.print("U");
    lcd.setCursor(2,1);
    lcd.print(e_eg);
  }
  
 
}

//#include <Wire.h>
// 
//void setup(){
//    Wire.begin();
// 
//    Serial.begin(9600);
//    while (!Serial);
//    Serial.println("\nI2C Scanner");
//} 
//
//void loop(){
//    byte error, address;
//    int nDevices;
// 
//    Serial.println("Scanning...");
// 
//    nDevices = 0;
//    for(address = 8; address < 127; address++ ){
//        Wire.beginTransmission(address);
//        error = Wire.endTransmission();
// 
//        if (error == 0){
//            Serial.print("I2C device found at address 0x");
//            if (address<16)
//                Serial.print("0");
//            Serial.print(address,HEX);
//            Serial.println(" !");
// 
//            nDevices++;
//        }
//        else if (error==4) {
//            Serial.print("Unknow error at address 0x");
//            if (address<16)
//                Serial.print("0");
//            Serial.println(address,HEX);
//        } 
//    }
//    if (nDevices == 0)
//        Serial.println("No I2C devices found\n");
//    else
//        Serial.println("done\n");
// 
//    delay(5000);
//}
