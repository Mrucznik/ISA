#include <ISADefinitions.h>

class EfektSwietlny
{
private:
  int led1;
  int led2;
  int opoznienie;
  int wypelnienie;
  int aktualneOpoznienie = 0;
  int aktualneWypelnienie = 0;
  bool swieci = false;

public:
  EfektSwietlny(int led1, int led2)
  {
    this->led1 = led1;
    this->led2 = led2;
    opoznienie = 5+random(20);
    wypelnienie = 5+opoznienie/random(20);
  }

  void update()
  {
    aktualneOpoznienie++;

    if(swieci)
      aktualneWypelnienie++;

    if(aktualneOpoznienie >= opoznienie)
    {
      aktualneOpoznienie = 0;
      swieci = true;
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      return;
    }

    if(aktualneWypelnienie >= wypelnienie)
    {
      swieci = false;
      aktualneWypelnienie = 0;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      return;
    }
  }
};


EfektSwietlny* efektySwietlne[4];


void setup() {
  for(int i = 0; i<8; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  
  randomSeed(34234621);

  efektySwietlne[0] = new EfektSwietlny(LED1, LED2);
  efektySwietlne[1] = new EfektSwietlny(LED3, LED4);
  efektySwietlne[2] = new EfektSwietlny(LED5, LED6);
  efektySwietlne[3] = new EfektSwietlny(LED7, LED8);
}

void loop() {
  delay(100);
  for(int i=0; i<4; i++)
  {
    efektySwietlne[i]->update();
  }
}

