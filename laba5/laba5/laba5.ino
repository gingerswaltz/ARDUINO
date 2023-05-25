#include "LCD_I2C.h" // библиотека для экранчика..

LCD_I2C lcd_v(0x27, 20, 4); // инициализация объекта lcd для напряжений
LCD_I2C lcd_a(0x25, 16, 2); // инициализация объекта lcd для сил тока
char buffer[4]; // для напряжений, форматированный вывод
float pi = 3.1415;
float Uab[2] = {
  380*cos(0),
   380*sin(0)
};
float Ubc[2] = {
   380*cos(2*pi/3),
   380*sin(2*pi/3)
};
float Uca[2] = {
   380*cos(4*pi/3),
   380*sin(4*pi/3)
};
float Zab[2] = {
   15,
   0
};
float Zbc[2] = {
   45,
   0
};
float Zca[2] = {
   15,
   0
};
float Rab, Rbc, Rca;

float one[2] = {
   1,
   0
}; // цифра 1 в комплексном представлении
float half[2] = {
   0.5,
   0
}; // число 0.5 в компл. представлении

// вывод сил тока на экран 2004
void output_a(float v1, float v2, float v3, float v4, float v5, float v6) {
   lcd_v.setCursor(0, 0);
   lcd_v.print("A");
   lcd_v.setCursor(1, 0);
   lcd_v.print("1");
   lcd_v.setCursor(2, 0);
   lcd_v.print(":");
   lcd_v.setCursor(3, 0);
   dtostrf(v1, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");
   
   lcd_v.setCursor(0, 1);
   lcd_v.print("A");
   lcd_v.setCursor(1, 1);
   lcd_v.print("2");
   lcd_v.setCursor(2, 1);
   lcd_v.print(":");
   lcd_v.setCursor(3, 1);
   dtostrf(v2, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");
   
   lcd_v.setCursor(0, 2);
   lcd_v.print("A");
   lcd_v.setCursor(1, 2);
   lcd_v.print("3");
   lcd_v.setCursor(2, 2);
   lcd_v.print(":");
   lcd_v.setCursor(3, 2);
   dtostrf(v3, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");
   
   lcd_v.setCursor(10, 0);
   lcd_v.print("A");
   lcd_v.setCursor(11, 0);
   lcd_v.print("4");
   lcd_v.setCursor(12, 0);
   lcd_v.print(":");
   lcd_v.setCursor(13, 0);
   dtostrf(v4, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");
   
   lcd_v.setCursor(10, 1);
   lcd_v.print("A");
   lcd_v.setCursor(11, 1);
   lcd_v.print("5");
   lcd_v.setCursor(12, 1);
   lcd_v.print(":");
   lcd_v.setCursor(13, 1);
   dtostrf(v5, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");
   
   lcd_v.setCursor(10, 2);
   lcd_v.print("A");
   lcd_v.setCursor(11, 2);
   lcd_v.print("6");
   lcd_v.setCursor(12, 2);
   lcd_v.print(":");
   lcd_v.setCursor(13, 2);
   dtostrf(v6, 3, 1, buffer);
   lcd_v.print(buffer);
   lcd_v.print("  ");

}

// вывод триг формы напряжений на экран 1602
void output_v(int a1, int a2, int a3) 
{
   lcd_a.setCursor(0, 0);
   lcd_a.print("V");
   lcd_a.setCursor(1, 0);
   lcd_a.print("1");
   lcd_a.setCursor(2, 0);
   lcd_a.print(":");
   lcd_a.print(a1);
   lcd_a.print(" ");

   lcd_a.setCursor(0, 1);
   lcd_a.print("V");
   lcd_a.setCursor(1, 1);
   lcd_a.print("2");
   lcd_a.setCursor(2, 1);
   lcd_a.print(":");
   lcd_a.print(a2);
   lcd_a.print(" ");

   lcd_a.setCursor(8, 0);
   lcd_a.print("V");
   lcd_a.setCursor(9, 0);
   lcd_a.print("3");
   lcd_a.setCursor(10, 0);
   lcd_a.print(":");
   lcd_a.print(a3);
   lcd_a.print(" ");
}

void sum_complex(  float * a,   float * b,   float * c) {
   c[0] = a[0] + b[0];
   c[1] = a[1] + b[1];
}

// разность компл чисел
void sub_complex(  float * a,   float * b,   float * c) {
   c[0] = a[0] - b[0];
   c[1] = a[1] - b[1];
}

// произведение компл чисел
void mul_complex(  float * a,   float * b,   float * c) {
   c[0] = a[0] * b[0] - a[1] * b[1];
   c[1] = a[0] * b[1] + a[1] * b[0];
}

// частное компл чисел
void div_complex(  float * a,   float * b,   float * c) {
 
   c[0] = ((a[0] * b[0]) + (a[1] * b[1])) / ((b[0] * b[0]) + (b[1] * b[1]));
   c[1] = (a[1] * b[0] - b[1] * a[0]) / (b[0] * b[0] + b[1] * b[1]);
   
}

// тригонометрическая форма для вывода на экран
float trigform(float * a) {
   return sqrt(a[0] * a[0] + a[1] * a[1]);
}

void setup() {
    
   lcd_v.begin();
   lcd_a.begin();
   lcd_v.backlight();
   lcd_a.backlight();
   pinMode(PA0, INPUT);
   pinMode(PA1, INPUT);
   pinMode(PA2, INPUT);
   pinMode(PB1, INPUT);
   pinMode(PB11, INPUT);
}

void loop() {
  float a1, a2, a3, a4, a5, a6;
  float v1, v2, v3;
   float I1 [2];
float I2 [2];
float I3 [2];
float I4 [2];
float I5 [2];
float I6 [2];
   /// переключатели
   int s1 = digitalRead(PB1); 
   int s2 = digitalRead(PB11);

  
   Rab = map(analogRead(PA0), 20, 4095, 1, 101); //Ra  - PA0
   Rab = constrain(Rab, 1, 100);

   Zab[0] = Rab;
   Rbc = map(analogRead(PA1), 20, 4095, 1, 101); //Rb - PA1
   Rbc = constrain(Rbc, 1, 100);

   Zbc[0] = Rbc;
   Rca = map(analogRead(PA2), 20, 4095, 1, 101); //Rc - PA2
   Rca = constrain(Rca, 1, 100);
   Zca[0] = Rca;
      delay(250);



   if (s1 == 1 and s2 == 1) 
   {
     div_complex(Uab, Zab, I4);
     a4 = trigform(I4);
     
     div_complex(Ubc, Zbc, I5);
     a5 = trigform(I5);
     
     div_complex(Uca, Zca, I6);
     a6 = trigform(I6);
     
     sub_complex(I4, I6, I1);
     a1 = trigform(I1);
     
     sub_complex(I5, I4, I2);
     a2 = trigform(I2);
     
     sub_complex(I6, I5, I3);
     a3 = trigform(I3);
     
     v1 = trigform(Uab);
     v2 = trigform(Ubc);
     v3 = trigform(Uca);
    output_a(a1, a2, a3, a4, a5, a6);
     output_v(v1, v2, v3);
   }
//   } else
//   if (s1 == 1 and s2 == 0 and s3 == 0) {
//      float res1[2];
//      float res2[2];
//
//      float Un[2];
//
//      sum_complex(Za, Zb, res1);
//      sum_complex(res1, one, res2);
//      float Ia[2];
//      div_complex(Uab, res2, Ia); // A1
//      mul_complex(Ia, Za, res1);
//      sub_complex(Ua, res1, Un);
//      sub_complex(Ub, Un, res1); // v2
//      v2 = trigform(res1);
//      sub_complex(Ua, Un, res1);
//      v3 = trigform(res1);
//      mul_complex(Ia, Za, res1);
//      v4 = trigform(res1);
//      mul_complex(Ia, Zb, res1);
//      v5 = trigform(res1);
//      v6 = 0;
//      v7 = trigform(Un);
//      v1 = trigform(Uab);
//      a1 = round(trigform(Ia));
//      a2 = a1;
//      a3 = 0;
//      a4 = 0;
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
//   } else
//   if (s1 == 0 and s2 == 1 and s3 == 0) {
//      float res1[2];
//      float res2[2];
//      sum_complex(Zb, Zc, res1);
//      sum_complex(res1, one, res2);
//      float Ib[2];
//      div_complex(Ubc, res2, Ib); // A2
//      a2 = round(trigform(Ib));
//      a3 = a2;
//      a4 = 0;
//      a1 = 0;
//
//      v1 = trigform(Uab);
//      v2 = trigform(Ubc);
//      v3 = trigform(Uca);
//      v4 = 0;
//      mul_complex(Ib, Zb, res1);
//      v5 = trigform(res1);
//      mul_complex(Ib, Zc, res1);
//      v6 = trigform(res1);
//      mul_complex(Ib, Zb, res1);
//      sub_complex(Ub, res1, res2);
//      v7 = trigform(res2);
//
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
//   } else
//   if (s1 == 0 and s2 == 0 and s3 == 1) {
//      float res1[2];
//      a1 = 0;
//      float Ib[2];
//      div_complex(Ub, Zb, Ib);
//      a2 = round(trigform(Ib));
//      a3 = 0;
//      a4 = a2;
//
//      v1 = trigform(Uab);
//      v2 = trigform(Ub);
//      v3 = trigform(Ua);
//      v4 = 0;
//      mul_complex(Ib, Zb, res1);
//      v5 = trigform(res1);
//      v6 = 0;
//      v7 = 0;
//
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
//   } else
//   if (s1 == 1 and s2 == 1 and s3 == 1) {
//      float res1[2];
//      float res2[2];
//      float Ia[2];
//      float Ib[2];
//      float Ic[2];
//
//      sum_complex(Za, half, res1);
//      div_complex(Ua, res1, Ia);
//      a1 = round(trigform(Ia));
//      sum_complex(Zb, half, res1);
//      div_complex(Ub, res1, Ib);
//      a2 = round(trigform(Ib));
//      sum_complex(Zc, half, res1);
//      div_complex(Uc, res1, Ic);
//      a3 = round(trigform(Ic));
//      sum_complex(Ia, Ib, res1);
//      sum_complex(Ic, res1, res2);
//      a4 = round(trigform(res2));
//
//      v1 = trigform(Uab);
//      v2 = trigform(Ubc);
//      v3 = trigform(Uca);
//      mul_complex(Ia, Za, res1);
//      v4 = trigform(res1);
//      mul_complex(Ib, Zb, res1);
//      v5 = trigform(res1);
//      mul_complex(Ic, Zc, res1);
//      v6 = trigform(res1);
//      v7 = 0;
//
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
//   } else
//   if (s1 == 0 and s2 == 1 and s3 == 1) {
//      float res1[2];
//      float res2[2];
//      float Ib[2];
//      float Ic[2];
//
//      a1 = 0;
//      sum_complex(Zb, half, res1);
//      div_complex(Ub, res1, Ib);
//      a2 = round(trigform(Ib));
//      sum_complex(Zc, half, res1);
//      div_complex(Uc, res1, Ic);
//      a3 = round(trigform(Ic));
//      sum_complex(Ib, Ic, res1);
//      a4 = round(trigform(res1));
//
//      v1 = trigform(Uab);
//      v2 = trigform(Ubc);
//      v3 = trigform(Uca);
//      v4 = 0;
//      mul_complex(Ib, Zb, res1);
//      v5 = trigform(res1);
//      mul_complex(Ic, Zc, res1);
//      v6 = trigform(res1);
//      v7 = 0;
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
//   } else
//   if (s1 == 1 and s2 == 0 and s3 == 1) {
//      float res1[2];
//      float res2[2];
//      float Ia[2];
//      float Ib[2];
//
//      sum_complex(Za, half, res1);
//      div_complex(Ua, res1, Ia);
//      a1 = round(trigform(Ia));
//      sum_complex(Zb, half, res1);
//      div_complex(Ub, res1, Ib);
//      a2 = round(trigform(Ib));
//      a3 = 0;
//      sum_complex(Ia, Ib, res1);
//      a4 = round(trigform(res1));
//      v1 = trigform(Uab);
//      v2 = trigform(Ub);
//      v3 = trigform(Ua);
//      mul_complex(Ia, Za, res1);
//      v4 = trigform(res1);
//      mul_complex(Ib, Zb, res1);
//      v5 = trigform(res1);
//      v6 = 0;
//      v7 = v6;
//      output_v(v1, v2, v3, v4, v5, v6, v7);
//      output_a(a1, a2, a3, a4);
//
                           
}
   
