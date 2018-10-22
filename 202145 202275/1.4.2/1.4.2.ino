#include <ISADefinitions.h>
int jasnosc=0;
int zmiana=1;

int jasnosci[8];

void setup() {
  long seed = 0;
  for (int i = 0; i < 12; i++)
  {
    seed += analogRead(i);
  }
  randomSeed(seed);
  for(int i=0; i<8; i++)
  {
    pinMode(LEDS[i], OUTPUT);
    jasnosci[i] = random(255);
  }
}

void loop() {
  for(int i=0; i<7; i++)
  {
    if(jasnosci[i] > jasnosci[i+1])
    {
      int tmp = jasnosci[i];
      jasnosci[i] = jasnosci[i+1]; 
      jasnosci[i+1] = tmp;

      display();
      delay(1000);
    }
  }
}

void display()
{
  for(int i=0; i<8; i++)
  {
    analogWrite(LEDS[i], jasnosci[i]);
  }
}

