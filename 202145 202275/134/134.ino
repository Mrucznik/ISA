#include <ISADefinitions.h>
#include <ISAButtons.h>
#include <DueTimer.h>
ISAButtons button;

int number;

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
  number = 0;
  button.init();
  Timer4.attachInterrupt(timer);
  Timer4.setFrequency(1);
  Timer4.start(1000000);
  
}



void getNumber() {
  int tmp;
  tmp = number;
  for(int i = 0; i < 8; i++) 
      digitalWrite(LEDS[i], false);
  for(int i = 0; i < 8; i++) {
      if(tmp%2) digitalWrite(LEDS[i], true);
      tmp /= 2;
  }
}

void timer() {
  number++;
}

void loop() {
  if(button.buttonPressed(0)) {
    Timer4.stop();
  }
  if(button.buttonPressed(1)) {
    Timer4.start();
  }
  if(button.buttonPressed(2)) {
    number = 0;
  }
  getNumber();
 }
