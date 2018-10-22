#include <ISADefinitions.h>

void setup() {
  for(int i = 0; i<8; i++)
  {
    pinMode(LEDS[i], OUTPUT);
  }
  wyswietl_bajt(120);
}

void loop() {
  
}

void wyswietl_bajt(unsigned char bajt)
{
  for(int i = 0; i<8; i++)
  {
    if(bajt & (1<<i))
      digitalWrite(LEDS[i], HIGH);
  }
}

