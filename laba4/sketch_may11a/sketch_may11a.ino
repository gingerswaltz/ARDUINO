#include "LCD_I2C.h" // библиотека для экранчика..
LCD_I2C lcd_v( 0x27,20, 4); // инициализация объекта lcd
LCD_I2C lcd_a( 0x26,16, 2); // инициализация объекта lcd
char buffer[4]; // for a

double Ua[2]={230.0, 0.0};
double Ub[2]={-115.0, 199.186};
double Uc[2]={-115.0, -199.186};
double Uab[2]={Ua[0]-Ub[0], Ua[1]-Ub[1]};
double Ubc[2]={Ub[0]-Uc[0], Ub[1]-Uc[1]};
double Uca[2]={Uc[0]-Ua[0], Uc[1]-Ua[1]};
double Za[2]={15,0};
double Zb[2]={45,0};
double Zc[2]={15,0};
double v1,v2,v3,v4,v5,v6,v7;
double a1,a2,a3,a4;
int s1,s2,s3=0;
double Rb[2]={45,0};
double Rc[2]={15,0};
double Ra[2]={15,0};
double  one[2]={1,0};
double  half[2]={0.5,0};
 
void output_v(int v1,int v2,int v3,int v4,int v5,int v6,int v7)
{
    lcd_v.setCursor(0,0);
    lcd_v.print("V");
    lcd_v.setCursor(1,0);
    lcd_v.print("1");
    lcd_v.setCursor(2,0);
    lcd_v.print(":");
    lcd_v.setCursor(3,0);
   
    lcd_v.print(v1);

    lcd_v.setCursor(0,1);
    lcd_v.print("V");
    lcd_v.setCursor(1,1);
    lcd_v.print("2");
    lcd_v.setCursor(2,1);
    lcd_v.print(":");
    lcd_v.setCursor(3,1);
    lcd_v.print(v2);

    lcd_v.setCursor(0,2);
    lcd_v.print("V");
    lcd_v.setCursor(1,2);
    lcd_v.print("3");
    lcd_v.setCursor(2,2);
    lcd_v.print(":");
    lcd_v.setCursor(3,2);
    lcd_v.print(v3);

    lcd_v.setCursor(10,0);
    lcd_v.print("V");
    lcd_v.setCursor(11,0);
    lcd_v.print("4");
    lcd_v.setCursor(12,0);
    lcd_v.print(":");
    lcd_v.setCursor(13,0);
    lcd_v.print(v4);

    lcd_v.setCursor(10,1);
    lcd_v.print("V");
    lcd_v.setCursor(11,1);
    lcd_v.print("5");
    lcd_v.setCursor(12,1);
    lcd_v.print(":");
    lcd_v.setCursor(13,1);
    lcd_v.print(v5);

     lcd_v.setCursor(10,2);
    lcd_v.print("V");
    lcd_v.setCursor(11,2);
    lcd_v.print("6");
    lcd_v.setCursor(12, 2);
    lcd_v.print(":");
   lcd_v.setCursor(13,2);
    lcd_v.print(v6);

     lcd_v.setCursor(10,3);
    lcd_v.print("V");
    lcd_v.setCursor(11,3);
    lcd_v.print("7");
    lcd_v.setCursor(12,3);
    lcd_v.print(":");
    lcd_v.setCursor(13,3);
    lcd_v.print(v7);
    
    
}

void output_a(double a1, double a2, double a3, double a4)
{
lcd_a.setCursor(0,0);
lcd_a.print("A");
lcd_a.setCursor(1,0);
lcd_a.print("1");
lcd_a.setCursor(2,0);
lcd_a.print(":");
dtostrf(a1, 3, 1, buffer); 
lcd_a.print(buffer);

lcd_a.setCursor(0,1);
lcd_a.print("A");
lcd_a.setCursor(1,1);
lcd_a.print("2");
lcd_a.setCursor(2,1);
lcd_a.print(":");
dtostrf(a2, 3, 1, buffer); 
lcd_a.print(buffer);

lcd_a.setCursor(8,0);
lcd_a.print("A");
lcd_a.setCursor(9,0);
lcd_a.print("3");
lcd_a.setCursor(10,0);
lcd_a.print(":");
dtostrf(a3, 3, 1, buffer); 
lcd_a.print(buffer);

lcd_a.setCursor(8,1);
lcd_a.print("A");
lcd_a.setCursor(9,1);
lcd_a.print("4");
lcd_a.setCursor(10,1);
lcd_a.print(":");
dtostrf(a4, 3, 1, buffer); 
lcd_a.print(buffer);

  
}



void sum_complex(double* a, double* b,  double* &c)
{
  c = new double[2];
  c[0] = a[0]+b[0];
  c[1] = a[1]+b[1];
}
void sub_complex(double* a, double* b, double* &c)
{
    c = new double[2];
c[0] = a[0]-b[0];
  c[1] = a[1]-b[1];
}
void mul_complex(double* a, double* b, double* &c)
{
      c = new double[2];
c[0] = a[0]*b[0]-a[1]*b[1];
  c[1] = a[1]*b[0]-a[0]*b[1]; 
}

void div_complex(double* a, double* b, double* &c)
{
    c = new double[2];
    c[0] = (a[0]*b[0]+b[1]*b[1])/(b[0]*b[0]+b[1]*b[1]);
    c[1] = (a[1]*b[0]-b[1]*a[0])/(b[0]*b[0]+b[1]*b[1]);
}



double trigform(double* a){
  return sqrt(a[0]*a[0]+a[1]*a[1]);
}
void setup(){
   
   lcd_v.begin();
   lcd_a.begin();
   lcd_v.backlight();
   lcd_a.backlight();
 

      Serial.begin(9600);

    
    
} 


void loop(){
//double* res=sum_complex(Ua, Ub);

s1=1;
s2=0;
s3=1;
if (s1==0 and s2==0 and s3==0){
  output_a(0,0,0,0);
  v1=trigform(Uab);
  v7=trigform(Ub);
  output_v(v1,0,0,0,0,0,v7);
  
}else
if (s1==1 and s2==1 and s3==0){

double* res1 = new double[2];
 double* res2 = new double[2];
double* res3 = new double[2];
double* res4 = new double[2];
double* res5 = new double[2];
double* res6 = new double[2];
double* res7 = new double[2];
double* res8 = new double[2];
double* res9 = new double[2];
double* res10 = new double[2];
double* Unn=new double[2];
 
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
  

 sub_complex(Ua, Unn,res1);
 sum_complex(Za, half, res2);
 double* Ia=new double[2];
 div_complex(res1, res2, Ia);


   sub_complex(Ub, Unn, res1);
  sum_complex(Zb, half,res2);
double* Ib=new double[2];
div_complex(res1, res2, Ib);

  sub_complex(Uc, Unn, res1);
 sum_complex(Zc, half, res2);
double* Ic=new double [2];
div_complex(res1, res2, Ic);


mul_complex(Ia, Za, res1);
 v4=trigform(res1);
mul_complex(Ib, Zb, res1);
 v5=trigform(res1);
mul_complex(Ic, Zc, res1);
  v6=trigform(res1);

 a1=trigform(Ia);
 a2=trigform(Ib);
  a3=trigform(Ic);

  v1=trigform(Uab);
  v2=trigform(Ubc);
  v3=trigform(Uca);
  v7=trigform(Unn);
output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,0);
  
delete[] res1;
delete[] res2;
delete[] res3;
delete[] res4;
delete[] res5;
delete[] res6;
delete[] res7;
delete[] res8;
delete[] res9;
delete[] res10;
delete[] Unn;
delete[]Ia;
delete[]Ib;
delete[]Ic;
}else 
if(s1==1 and s2==0 and s3==0){
  double* res1 = new double[2];
 double* res2 = new double[2];

double* Un=new double[2];

sum_complex(Za, Zb, res1);
sum_complex(res1, one, res2);
double* Ia=new double[2];
div_complex(Uab, res2, Ia); // A1
mul_complex(Ia, Za, res1);
sub_complex(Ua, res1, Un);
sub_complex(Ub, Un, res1); // v2
v2=trigform(res1);
sub_complex(Ua, Un, res1);
v3=trigform(res1);
mul_complex(Ia, Za, res1);
v4=trigform(res1);
mul_complex(Ia, Zb, res1);
v5=trigform(res1);
v6=0;
v7=trigform(Un);
v1=trigform(Uab);
a1=trigform(Ia);
a2=a1;
a3=0;
a4=0;
output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);
delete[] res1;
delete[] res2;
delete[] Un;
delete[] Ia;
} else 
if(s1==0 and s2==1 and s3==0){
  
  double* res1 = new double[2];
 double* res2 = new double[2];
sum_complex(Zb, Zc, res1);
sum_complex(res1, one, res2);
double* Ib=new double[2];
div_complex(Ubc, res2, Ib); // A2
a2=trigform(Ib);
a3=a2;
a4=0;
a1=0;

v1=trigform(Uab);
v2=trigform(Ubc);
v3=trigform(Uca);
v4=0;
mul_complex(Ib, Zb, res1);
v5=trigform(res1);
mul_complex(Ib,Zc,res1);
v6=trigform(res1);
mul_complex(Ib, Zb, res1);
sub_complex(Ub, res1,res2);
v7=trigform(res2);

output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);
delete[] res1;
delete[] res2;
delete[] Ib;
}else 
if(s1==0 and s2==0 and s3==1){
 
  double* res1 = new double[2];
  a1=0;
  double* Ib = new double[2];
  div_complex(Ub, Zb, Ib);
  a2=trigform(Ib);
  a3=0;
  a4=a2;

  v1=trigform(Uab);
  v2=trigform(Ub);
  v3=trigform(Ua);
  v4=0;
  mul_complex(Ib,Zb, res1);
  v5=trigform(res1);
  v6=0;
  v7=0;

output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);

  delete[] res1;

delete[] Ib;
}else 
if(s1==1 and s2==1 and s3==1){
  double* res1 = new double[2];
 double* res2 = new double[2];
double* Ia = new double[2];
 double* Ib = new double[2];
 double* Ic = new double[2];

sum_complex(Za, half, res1);
div_complex(Ua, res1, Ia);
a1=trigform(Ia);
sum_complex(Zb, half, res1);
div_complex(Ub, res1, Ib);
a2=trigform(Ib);
sum_complex(Zc, half, res1);
div_complex(Uc, res1, Ic);
a3=trigform(Ic);
sum_complex(Ia, Ib, res1);
sum_complex(Ic, res1, res2);
a4=trigform(res2);

v1=trigform(Uab);
  v2=trigform(Ubc);
  v3=trigform(Uca);
  mul_complex(Ia,Za, res1);
  v4=trigform(res1);
    mul_complex(Ib,Zb, res1);
  v5=trigform(res1);
    mul_complex(Ic,Zc, res1);
  v6=trigform(res1);
  v7=0;

output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);
delete[] res1;
delete[] res2;
delete[] Ia;
delete[] Ib;
delete[] Ic;

}else
if(s1==0 and s2==1 and s3==1){
   double* res1 = new double[2];
 double* res2 = new double[2];
 double* Ib = new double[2];
 double* Ic = new double[2];

a1=0;
sum_complex(Zb, half, res1);
div_complex(Ub, res1, Ib);
a2=trigform(Ib);
sum_complex(Zc, half, res1);
div_complex(Uc, res1, Ic);
a3=trigform(Ic);
sum_complex(Ib, Ic, res1);
a4=trigform(res1);

v1=trigform(Uab);
  v2=trigform(Ubc);
  v3=trigform(Uca);
  v4=0;
 mul_complex(Ib, Zb, res1);
 v5=trigform(res1);
  mul_complex(Ic, Zc, res1);
 v6=trigform(res1);
 v7=0;
 output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);
delete[] res1;
delete[] res2;
delete[] Ib;
delete[] Ic;
}else 
if(s1==1 and s2==0 and s3==1){
  
}
 double* res1 = new double[2];
 double* res2 = new double[2];
 double* Ia = new double[2];
 double* Ib = new double[2];

sum_complex(Za, half, res1);
div_complex(Ua, res1, Ia);
a1=trigform(Ia);
sum_complex(Zb, half, res1);
div_complex(Ub, res1, Ib);
a2=trigform(Ib);
a3=0;
sum_complex(Ia, Ib, res1);
a4=trigform(res1);
v1=trigform(Uab);
v2=trigform(Ub);
v3=trigform(Ua);
mul_complex(Ia, Za, res1);
v4=trigform(res1);
mul_complex(Ib, Zb, res1);
v5=trigform(res1);
v6=0;
v7=v6;
 output_v(v1,v2,v3,v4,v5,v6,v7);
output_a(a1,a2,a3,a4);
delete[] res1;
delete[] res2;
delete[] Ib;
delete[] Ia;

}
