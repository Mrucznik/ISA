#include <ISADefinitions.h>
#include <ISA7SegmentDisplay.h>
#include <DueTimer.h>
ISA7SegmentDisplay sseg;

volatile long czas = 0;

enum ESystem {
  dziesietny,
  osemkowy,
  szesnastkowy
};

ESystem kebabCase = dziesietny;

void setup() {
  pinMode(KEY_LEFT, INPUT);
  pinMode(KEY_DOWN, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  
  Timer4.attachInterrupt(timer);
  Timer4.setFrequency(10);
  Timer4.start();

  sseg.init();
}

void loop() {
  if(!digitalRead(KEY_LEFT))
  {
    kebabCase = dziesietny;
  }
  if(!digitalRead(KEY_DOWN))
  {
    kebabCase = szesnastkowy;
  }
  if(!digitalRead(KEY_RIGHT))
  {
    kebabCase = osemkowy;
  }
  
  switch(kebabCase)
  {
    case dziesietny:
      sseg.displayDigit(czas%10, 0);
      sseg.displayDigit((czas/10)%10, 1);
      sseg.displayDigit((czas/100)%10, 2);
      sseg.displayDigit((czas/1000)%10, 3);
      
      break;
    case osemkowy:
      displayHex(czas%8, 0);
      displayHex((czas/(8))%8, 1);
      displayHex((czas/(8*8))%8, 2);
      displayHex((czas/(8*8*8))%8, 3);
    
      break;
    case szesnastkowy:
      displayHex(czas%16, 0);
      displayHex((czas/(16))%16, 1);
      displayHex((czas/(16*16))%16, 2);
      displayHex((czas/(16*16*16))%16, 3);
    
      break;
  }
}

void displayHex(int liczba, int pos)
{
  if(liczba < 10)
  {
    sseg.displayDigit(liczba, pos);
  } else if(liczba == 10)
  {
    sseg.setLed(bit(0) | bit(4) | bit(2) | bit(3) | bit(5) | bit(6), pos);
  } else if(liczba == 11)
  {
    sseg.setLed(bit(4) | bit(7) | bit(3) | bit(5) | bit(6), pos);
  } else if(liczba == 12)
  {
    sseg.setLed(bit(7) | bit(2) | bit(5) | bit(6), pos);
  } else if(liczba == 13)
  {
    sseg.setLed(bit(4) | bit(7) | bit(3) | bit(5) | bit(0), pos);
  } else if(liczba == 14)
  {
    sseg.setLed(bit(7) | bit(2) | bit(5) | bit(6) | bit(4), pos);
  } else if(liczba == 15)
  {
    sseg.setLed(bit(2) | bit(5) | bit(6) | bit(4), pos);
  }
}

void timer()
{
  czas++;
}

