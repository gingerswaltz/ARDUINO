
// the setup function runs once when you press reset or power the board

void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(PA7, INPUT);
  pinMode(PB3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  pinMode(PB8, OUTPUT);
  pinMode(PB9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
//  digitalWrite(PB3,HIGH); // 5 noga G
//  digitalWrite(PB4,HIGH); // 7 noga B
//  digitalWrite(PB5,HIGH); // 4 noga C
//  digitalWrite(PB6,HIGH); // 
//  digitalWrite(PB7,HIGH);
//  digitalWrite(PB8,HIGH);
//  digitalWrite(PB9,HIGH);
int val=analogRead(PA7);
if (val>273) 
{ 
  digitalWrite(PB5,HIGH); 
 digitalWrite(PB4,HIGH); // 7 noga B
}else
{
  digitalWrite(PB5,LOW); // 4 noga C
  digitalWrite(PB4,LOW); // 7 noga B
}

  
}
