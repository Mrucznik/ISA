#include <ISADefinitions.h>
#include <DueTimer.h>

int i = 0;
int zmiana = 1;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  Timer1.attachInterrupt(dioda);
  Timer1.start(250000);
}

void loop() {

}

void dioda(){

  for(int j=0; j<8; j++)
  {
    digitalWrite(LEDS[j], LOW);
  }
  digitalWrite(LEDS[i], HIGH);
  i = i + zmiana;
  if (i == 7 || i == 0) {
    zmiana = zmiana*(-1);
  }
}

