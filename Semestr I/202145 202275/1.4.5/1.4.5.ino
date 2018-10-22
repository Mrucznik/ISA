#include <ISADefinitions.h>
int jasnosc=0;
int skok=0;
int idx=0;
int zmiana=1;

int jasnosci[8];

void setup() {
  long seed = 0;
  for(int i=0; i<8; i++)
  {
    pinMode(LEDS[i], OUTPUT);
    jasnosci[i] = 0;
  }
  jasnosci[0] = 255;
}

void loop() {

  for(int i=0; i<8; i++)
  {
    if(jasnosci[i] != 0)
    {
      jasnosci[i] --;
    }
  }

  if(skok++ == 50)
  {
    jasnosci[idx] = 255;
    if(idx == 7)
    {
      zmiana=-1;
    }
    if(idx == 0)
    {
      zmiana=1;
    }
    idx+=zmiana;
    skok=0;
  }
  
  display();
  delay(1);
}

void display()
{
  for(int i=0; i<8; i++)
  {
    analogWrite(LEDS[i], jasnosci[i]);
  }
}

