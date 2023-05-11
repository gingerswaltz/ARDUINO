#include "LCD_I2C.h" // библиотека для экранчика..
#include "Complex.h"
//LCD_I2C lcd_v( 0x27,20, 4); // инициализация объекта lcd

//LCD_I2C lcd_a( 0x26,16, 2); // инициализация объекта lcd
double Ua[2]={220.0,0.0};
double Ub[2]={-110.0, 190.53};
double Uc[2]={-110.0, -190.53};
double Uab[2];//={Ua[0]-Ub[0], Ua[1]-Ub[1]};
double Ubc[2]={Ub[0]-Uc[0], Ub[1]-Uc[1]};

void sum_complex(double* a, double* b, double* c)
{
  c[0] = a[0]+b[0];
  c[1] = a[1]+b[1];
}
void sub_complex(double* a, double* b, double* c)
{
  c[0] = a[0]-b[0];
  c[1] = a[1]-b[1];
}
void mul_complex(double* a, double* b, double* c)
{
  c[0] = a[0]*b[0]-a[1]*b[1];
  c[1] = a[1]*b[0]-a[0]*b[1];
}
void div_complex(double* a, double* b, double* c)
{
  c[0] = (a[0]*b[0]+b[1]*b[1])/(b[0]*b[0]+b[1]*b[1]);
  c[1] = (a[1]*b[0]-b[1]*a[0])/(b[0]*b[0]+b[1]*b[1]);
}
void setup(){
   
   //lcd_v.init();
  // lcd_a.init();
  // lcd_v.backlight();
 //  lcd_a.backlight();
  //  lcd_v.print("hello");
  //  lcd_a.print("world"); 

      Serial.begin(9600);

    
    
} 


void loop(){
// sum_complex_r(Ua,Ub);
 // sum_complex_m(Ua,Ub);
sum_complex(Ua, Ub, Uab);
Serial.println(Uab[0]);
Serial.println(Uab[1]);
    delay(1000);

}
