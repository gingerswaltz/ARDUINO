#include "LCD_I2C.h" // библиотека для экранчика..

LCD_I2C lcd_v(0x27, 20, 4); // инициализация объекта lcd для напряжений
LCD_I2C lcd_a(0x25, 16, 2); // инициализация объекта lcd для сил тока
char buffer[4]; // для напряжений, форматированный вывод

float Ua[2] = {
   230.0,
   0.0
};
float Ub[2] = {
   -115.0,
   199.186
};
float Uc[2] = {
   -115.0,
   -199.186
};
float Uab[2] = {
   Ua[0] - Ub[0],
   Ua[1] - Ub[1]
};
float Ubc[2] = {
   Ub[0] - Uc[0],
   Ub[1] - Uc[1]
};
float Uca[2] = {
   Uc[0] - Ua[0],
   Uc[1] - Ua[1]
};
float Za[2] = {
   15,
   0
};
float Zb[2] = {
   45,
   0
};
float Zc[2] = {
   15,
   0
};
float Ra, Rb, Rc;

float one[2] = {
   1,
   0
}; // цифра 1 в комплексном представлении
float half[2] = {
   0.5,
   0
}; // число 0.5 в компл. представлении

// вывод напряжений на экран 2004
void output_v(int v1, int v2, int v3, int v4, int v5, int v6, int v7) {
   lcd_v.setCursor(0, 0);
   lcd_v.print("V");
   lcd_v.setCursor(1, 0);
   lcd_v.print("1");
   lcd_v.setCursor(2, 0);
   lcd_v.print(":");
   lcd_v.setCursor(3, 0);

   lcd_v.print(v1);
   lcd_v.print("  ");
   lcd_v.setCursor(0, 1);
   lcd_v.print("V");
   lcd_v.setCursor(1, 1);
   lcd_v.print("2");
   lcd_v.setCursor(2, 1);
   lcd_v.print(":");
   lcd_v.setCursor(3, 1);
   lcd_v.print(v2);
   lcd_v.print("  ");
   lcd_v.setCursor(0, 2);
   lcd_v.print("V");
   lcd_v.setCursor(1, 2);
   lcd_v.print("3");
   lcd_v.setCursor(2, 2);
   lcd_v.print(":");
   lcd_v.setCursor(3, 2);
   lcd_v.print(v3);
   lcd_v.print("  ");
   lcd_v.setCursor(10, 0);
   lcd_v.print("V");
   lcd_v.setCursor(11, 0);
   lcd_v.print("4");
   lcd_v.setCursor(12, 0);
   lcd_v.print(":");
   lcd_v.setCursor(13, 0);
   lcd_v.print(v4);
   lcd_v.print("  ");
   lcd_v.setCursor(10, 1);
   lcd_v.print("V");
   lcd_v.setCursor(11, 1);
   lcd_v.print("5");
   lcd_v.setCursor(12, 1);
   lcd_v.print(":");
   lcd_v.setCursor(13, 1);
   lcd_v.print(v5);
   lcd_v.print("  ");
   lcd_v.setCursor(10, 2);
   lcd_v.print("V");
   lcd_v.setCursor(11, 2);
   lcd_v.print("6");
   lcd_v.setCursor(12, 2);
   lcd_v.print(":");
   lcd_v.setCursor(13, 2);
   lcd_v.print(v6);
   lcd_v.print("  ");
   lcd_v.setCursor(10, 3);
   lcd_v.print("V");
   lcd_v.setCursor(11, 3);
   lcd_v.print("7");
   lcd_v.setCursor(12, 3);
   lcd_v.print(":");
   lcd_v.setCursor(13, 3);
   lcd_v.print(v7);
   lcd_v.print("  ");

}

// вывод триг формы сил тока на экран 1602
void output_a(float a1, float a2, float a3, float a4) {
   lcd_a.setCursor(0, 0);
   lcd_a.print("A");
   lcd_a.setCursor(1, 0);
   lcd_a.print("1");
   lcd_a.setCursor(2, 0);
   lcd_a.print(":");
   dtostrf(a1, 3, 1, buffer);
   lcd_a.print(buffer);

   lcd_a.setCursor(0, 1);
   lcd_a.print("A");
   lcd_a.setCursor(1, 1);
   lcd_a.print("2");
   lcd_a.setCursor(2, 1);
   lcd_a.print(":");
   dtostrf(a2, 3, 1, buffer);
   lcd_a.print(buffer);

   lcd_a.setCursor(8, 0);
   lcd_a.print("A");
   lcd_a.setCursor(9, 0);
   lcd_a.print("3");
   lcd_a.setCursor(10, 0);
   lcd_a.print(":");
   dtostrf(a3, 3, 1, buffer);
   lcd_a.print(buffer);

   lcd_a.setCursor(8, 1);
   lcd_a.print("A");
   lcd_a.setCursor(9, 1);
   lcd_a.print("4");
   lcd_a.setCursor(10, 1);
   lcd_a.print(":");
   dtostrf(a4, 3, 1, buffer);
   lcd_a.print(buffer);

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
   pinMode(PA10, INPUT);
   pinMode(PA1, INPUT);
   pinMode(PA11, INPUT);
   pinMode(PB12, INPUT);
}

void loop() {
   float v1, v2, v3, v4, v5, v6, v7;
   float a1, a2, a3, a4;
   
   /// переключатели
   int s1 = digitalRead(PB1); 
   int s2 = digitalRead(PB10);
   int s3 = digitalRead(PB11);
   int s4 = digitalRead(PB12);
   float Za[2] = {
      0,
      0
   };
   float Zb[2] = {
      0,
      0
   };
   float Zc[2] = {
      0,
      0
   };
   float Ra, Rb, Rc;

   Ra = map(analogRead(PA0), 20, 4095, 1, 101); //Ra  - PA0
   Ra = constrain(Ra, 1, 100);

   Za[0] = Ra;
   Rb = map(analogRead(PA1), 20, 4095, 1, 101); //Rb - PA1
   Rb = constrain(Rb, 1, 100);

   Zb[0] = Rb;
   Rc = map(analogRead(PA2), 20, 4095, 1, 101); //Rc - PA2
   Rc = constrain(Rc, 1, 100);
   Zc[0] = Rc;
      delay(250);

   // проверка свича s4  порт PB12
   if (s4 == 1) {
      Zb[1] = -Rb;
      Zb[0] = 0;
   } else {
      Zb[0] = Rb;
      Zb[1] = 0;
   }
  /// Основная суть программы - проверяем состояние свитчей s1..s3 и на основе этого делаем расчёты и выводим на экран 
   if (s1 == 0 and s2 == 0 and s3 == 0) {
      output_a(0, 0, 0, 0);
      v1 = trigform(Uab);
      v7 = trigform(Ub);
      output_v(v1, 0, 0, 0, 0, 0, v7);

   } else
   if (s1 == 1 and s2 == 1 and s3 == 0) {
      float res1[2];
      float res2[2];
      float res3[2];
      float res4[2];
      float res5[2];
      float res6[2];
      float res7[2];
      float res8[2];
      float res9[2];
      float res10[2];
      float Unn[2];

      div_complex(Ua, Za, res1);

      div_complex(Ub, Zb, res2);

      div_complex(Uc, Zc, res3);
      div_complex(one, Za, res4);
      div_complex(one, Zb, res5);
      div_complex(one, Zc, res6);
      sum_complex(res1, res2, res7);
      sum_complex(res7, res3, res8);
      sum_complex(res4, res5, res9);

      sum_complex(res9, res6, res10);

      div_complex(res8, res10, Unn); // unn

      sub_complex(Ua, Unn, res1);
      sum_complex(Za, half, res2);
      float Ia[2];
      div_complex(res1, res2, Ia);

      sub_complex(Ub, Unn, res1);
      sum_complex(Zb, half, res2);
      float Ib[2];
      div_complex(res1, res2, Ib);

      sub_complex(Uc, Unn, res1);
      sum_complex(Zc, half, res2);
      float Ic[2];
      div_complex(res1, res2, Ic);

      mul_complex(Ia, Za, res1);
      v4 = trigform(res1);
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      mul_complex(Ic, Zc, res1);
      v6 = trigform(res1);

      a1 = round(trigform(Ia));
      a2 = round(trigform(Ib));
      a3 = round(trigform(Ic));

      v1 = trigform(Uab);
      v2 = trigform(Ubc);
      v3 = trigform(Uca);
      v7 = trigform(Unn);
      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, 0);

   } else
   if (s1 == 1 and s2 == 0 and s3 == 0) {
      float res1[2];
      float res2[2];

      float Un[2];

      sum_complex(Za, Zb, res1);
      sum_complex(res1, one, res2);
      float Ia[2];
      div_complex(Uab, res2, Ia); // A1
      mul_complex(Ia, Za, res1);
      sub_complex(Ua, res1, Un);
      sub_complex(Ub, Un, res1); // v2
      v2 = trigform(res1);
      sub_complex(Ua, Un, res1);
      v3 = trigform(res1);
      mul_complex(Ia, Za, res1);
      v4 = trigform(res1);
      mul_complex(Ia, Zb, res1);
      v5 = trigform(res1);
      v6 = 0;
      v7 = trigform(Un);
      v1 = trigform(Uab);
      a1 = round(trigform(Ia));
      a2 = a1;
      a3 = 0;
      a4 = 0;
      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   } else
   if (s1 == 0 and s2 == 1 and s3 == 0) {
      float res1[2];
      float res2[2];
      sum_complex(Zb, Zc, res1);
      sum_complex(res1, one, res2);
      float Ib[2];
      div_complex(Ubc, res2, Ib); // A2
      a2 = round(trigform(Ib));
      a3 = a2;
      a4 = 0;
      a1 = 0;

      v1 = trigform(Uab);
      v2 = trigform(Ubc);
      v3 = trigform(Uca);
      v4 = 0;
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      mul_complex(Ib, Zc, res1);
      v6 = trigform(res1);
      mul_complex(Ib, Zb, res1);
      sub_complex(Ub, res1, res2);
      v7 = trigform(res2);

      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   } else
   if (s1 == 0 and s2 == 0 and s3 == 1) {
      float res1[2];
      a1 = 0;
      float Ib[2];
      div_complex(Ub, Zb, Ib);
      a2 = round(trigform(Ib));
      a3 = 0;
      a4 = a2;

      v1 = trigform(Uab);
      v2 = trigform(Ub);
      v3 = trigform(Ua);
      v4 = 0;
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      v6 = 0;
      v7 = 0;

      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   } else
   if (s1 == 1 and s2 == 1 and s3 == 1) {
      float res1[2];
      float res2[2];
      float Ia[2];
      float Ib[2];
      float Ic[2];

      sum_complex(Za, half, res1);
      div_complex(Ua, res1, Ia);
      a1 = round(trigform(Ia));
      sum_complex(Zb, half, res1);
      div_complex(Ub, res1, Ib);
      a2 = round(trigform(Ib));
      sum_complex(Zc, half, res1);
      div_complex(Uc, res1, Ic);
      a3 = round(trigform(Ic));
      sum_complex(Ia, Ib, res1);
      sum_complex(Ic, res1, res2);
      a4 = round(trigform(res2));

      v1 = trigform(Uab);
      v2 = trigform(Ubc);
      v3 = trigform(Uca);
      mul_complex(Ia, Za, res1);
      v4 = trigform(res1);
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      mul_complex(Ic, Zc, res1);
      v6 = trigform(res1);
      v7 = 0;

      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   } else
   if (s1 == 0 and s2 == 1 and s3 == 1) {
      float res1[2];
      float res2[2];
      float Ib[2];
      float Ic[2];

      a1 = 0;
      sum_complex(Zb, half, res1);
      div_complex(Ub, res1, Ib);
      a2 = round(trigform(Ib));
      sum_complex(Zc, half, res1);
      div_complex(Uc, res1, Ic);
      a3 = round(trigform(Ic));
      sum_complex(Ib, Ic, res1);
      a4 = round(trigform(res1));

      v1 = trigform(Uab);
      v2 = trigform(Ubc);
      v3 = trigform(Uca);
      v4 = 0;
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      mul_complex(Ic, Zc, res1);
      v6 = trigform(res1);
      v7 = 0;
      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   } else
   if (s1 == 1 and s2 == 0 and s3 == 1) {
      float res1[2];
      float res2[2];
      float Ia[2];
      float Ib[2];

      sum_complex(Za, half, res1);
      div_complex(Ua, res1, Ia);
      a1 = round(trigform(Ia));
      sum_complex(Zb, half, res1);
      div_complex(Ub, res1, Ib);
      a2 = round(trigform(Ib));
      a3 = 0;
      sum_complex(Ia, Ib, res1);
      a4 = round(trigform(res1));
      v1 = trigform(Uab);
      v2 = trigform(Ub);
      v3 = trigform(Ua);
      mul_complex(Ia, Za, res1);
      v4 = trigform(res1);
      mul_complex(Ib, Zb, res1);
      v5 = trigform(res1);
      v6 = 0;
      v7 = v6;
      output_v(v1, v2, v3, v4, v5, v6, v7);
      output_a(a1, a2, a3, a4);

   }
}
