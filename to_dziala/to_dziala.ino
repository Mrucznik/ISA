#include <Wire.h>

#define addr 0x1E

//CZUJNIKI ODLEGŁOŚCI
#define US_FRONT_TRIGGER_PIN  8
#define US_FRONT_ECHO_PIN   9

#define US_BACK_TRIGGER_PIN    10
#define US_BACK_ECHO_PIN    11

#define US_LEFT_TRIGGER_PIN    5
#define US_LEFT_ECHO_PIN    4

#define US_RIGHT_TRIGGER_PIN  6
#define US_RIGHT_ECHO_PIN   7

//SILNIKI
#define A_ENABLE 2  //PWM
#define A_PHASE 48  //0 - przod, 1 - tyl DIGITAL
#define B_ENABLE 3  //PWM
#define B_PHASE 46  //0 - przod, 1 - tyl DIGITAL
#define MODE 44     //sterowanie 0 - ciężkie, 1 - uproszczone DIGITAL

//KOMPAS

//INNE
#define SPEED 150

enum Side
{
  Side_Left,
  Side_Right
};


void setup() {
  //CZUJNIKI
  pinMode(US_FRONT_TRIGGER_PIN, OUTPUT);
  pinMode(US_BACK_TRIGGER_PIN, OUTPUT);
  pinMode(US_LEFT_TRIGGER_PIN, OUTPUT);
  pinMode(US_RIGHT_TRIGGER_PIN, OUTPUT);

  pinMode(US_FRONT_ECHO_PIN, INPUT);
  pinMode(US_BACK_ECHO_PIN, INPUT);
  pinMode(US_LEFT_ECHO_PIN, INPUT);
  pinMode(US_RIGHT_ECHO_PIN, INPUT);

  //PWM'y
  pinMode(A_ENABLE, OUTPUT);  //ustawienie pinów do PWM na output
  pinMode(B_ENABLE, OUTPUT);

  pinMode(A_PHASE, OUTPUT);   //ustawienie pinów do kierunku jazdy na output
  pinMode(B_PHASE, OUTPUT);

  pinMode(MODE, OUTPUT);      //ustawienie pinu rozdzaju sterowania na output
  digitalWrite(MODE, HIGH);   //ustawienie uproszczonego sterowania ;P

  digitalWrite(A_PHASE, 0);
  digitalWrite(B_PHASE, 0);

  analogWrite(A_ENABLE, 0);
  analogWrite(B_ENABLE, 0);

  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}

void loop() {
  kompas();
  //ruch();
  //serial_port();
}

void kompas()
{
  int x=0,y=0,z=0; //triple axis data

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 
 //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  while(6<=Wire.available()){
    x = Wire.read()<<8; //MSB  x 
    x |= Wire.read(); //LSB  x
    z = Wire.read()<<8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read()<<8; //MSB y
    y |= Wire.read(); //LSB y
  }
  
  // Show Values
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();
  
  delay(500);
}

void ruch()
{
  int lewo = measure(US_LEFT_TRIGGER_PIN, US_LEFT_ECHO_PIN);
  int prawo = measure(US_RIGHT_TRIGGER_PIN, US_RIGHT_ECHO_PIN);
  int przod = measure(US_FRONT_TRIGGER_PIN, US_FRONT_ECHO_PIN);

  if(przod < 25 || lewo < 15 || prawo < 15)
  {
    if(przod < 15)
    {
      w_lewo();
    }
    else if(lewo > prawo)
    {
      w_prawo();
    }
    else if(prawo > lewo)
    {
      w_lewo();
    }
    else if(przod > 15)
    {
      do_przodu();
    }
    else 
    {
      w_prawo();
    }
    return;
  }
  do_przodu();
}

void serial_port()
{
    char buffer[64];
    Serial.print("> ");
    
    String s = "";
    while(true)
    {
      while(Serial.available() == 0);
      int ch = Serial.read();
      if (ch == '\n')
        break;
      s += (char)ch;
    }

    if(s == "prawo_przod")
    {
      jedz(Side_Right, -255);
    }
    else if(s == "lewo_przod")
    {
      jedz(Side_Left, -255);
    }
    else if(s == "prawo_tyl")
    {
      jedz(Side_Right, 255);
    }
    else if(s == "lewo_tyl")
    {
      jedz(Side_Left, 255);
    }
    else if(s == "tyl")
    {
      jedz(Side_Left, 255);
      jedz(Side_Right, 255);
    }
    else if(s == "prosto")
    {
      jedz(Side_Left, -255);
      jedz(Side_Right, -255);
    }
    else if(s == "stop")
    {
      jedz(Side_Left, 0);
      jedz(Side_Right, 0);
    }
    else if(s == "czujnik_przod")
    {
      int dist = measure(US_FRONT_TRIGGER_PIN, US_FRONT_ECHO_PIN);
      sprintf(buffer, "Czujnik przod: %0dcm", dist);
      Serial.println(buffer);
    }
    else if(s == "czujnik_tyl")
    {
      int dist = measure(US_BACK_TRIGGER_PIN, US_BACK_ECHO_PIN);
      sprintf(buffer, "Czujnik tyl: %0dcm", dist);
      Serial.println(buffer);
    }
    else if(s == "czujnik_lewo")
    {
      int dist = measure(US_LEFT_TRIGGER_PIN, US_LEFT_ECHO_PIN);
      sprintf(buffer, "Czujnik lewo: %0dcm", dist);
      Serial.println(buffer);
    }
    else if(s == "czujnik_prawo")
    {
      int dist = measure(US_RIGHT_TRIGGER_PIN, US_RIGHT_ECHO_PIN);
      sprintf(buffer, "Czujnik prawo: %0dcm", dist);
      Serial.println(buffer);
    }
}

void jedz(Side side, int speed)
{
  
  if(side == Side_Left)
  {
    if(speed < 0)
    {
      digitalWrite(A_PHASE, 0);
      analogWrite(A_ENABLE, speed*(-1));
    }
    else if(speed > 0)
    {
      digitalWrite(A_PHASE, 1);
      analogWrite(A_ENABLE, speed);
    }
    else
    {
      
      digitalWrite(A_PHASE, 0);
      analogWrite(A_ENABLE, 0);
    }
  }
  else if(side == Side_Right)
  {
    if(speed < 0)
    {
      digitalWrite(B_PHASE, 0);
      analogWrite(B_ENABLE, speed*(-1));
    }
    else if(speed > 0)
    {
      digitalWrite(B_PHASE, 1);
      analogWrite(B_ENABLE, speed);
    }
    else
    {
      
      digitalWrite(B_PHASE, 0);
      analogWrite(B_ENABLE, 0);
    }
  }
}

int measure(int trigger, int echo)
{
  digitalWrite(trigger, false);
  delayMicroseconds(2);

  digitalWrite(trigger, true);
  delayMicroseconds(10);
  digitalWrite(trigger, false);

  // zmierz czas przelotu fali dźwiękowej
  int duration = pulseIn(echo, true);

  // przelicz czas na odległość (1/2 Vsound(t=20st.C))
  int distance = (int)((float)duration * 0.03438f * 0.5f);
  return distance;
}

void do_przodu(){
  jedz(Side_Left, -SPEED);
  jedz(Side_Right, -SPEED);
}

void do_tylu(){
  jedz(Side_Left, SPEED);
  jedz(Side_Right, SPEED);
}

void w_lewo(){
  jedz(Side_Left, -SPEED);
  jedz(Side_Right, SPEED);
}

void w_prawo(){
  jedz(Side_Right, -SPEED);
  jedz(Side_Left, SPEED);
}

void stoj(){
      jedz(Side_Left, 0);
      jedz(Side_Right, 0);
}


