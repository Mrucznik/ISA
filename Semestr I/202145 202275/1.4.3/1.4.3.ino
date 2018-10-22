#include <ISADefinitions.h>
#include <ISAButtons.h>

ISAButtons buttons;
int jasnosc=0;
int zmiana=1;

void setup() {
  buttons.init();
  pinMode(LED1, OUTPUT);
  pinMode(KEY_UP, INPUT);
  pinMode(KEY_DOWN, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  pinMode(KEY_LEFT, INPUT);
}

void loop() {
  if(buttons.buttonPressed(12)) { //+
    jasnosc++;
    display();
    delay(100);
  }
  if(buttons.buttonPressed(11)) { //-
    jasnosc--;
    display();
    delay(100);
  }
  if(!digitalRead(KEY_UP)) {
    jasnosc+=10;
    display();
    delay(100);
  }
  if(!digitalRead(KEY_DOWN)) {
    jasnosc-=10;
    display();
    delay(100);
  }
  if(!digitalRead(KEY_RIGHT)) {
    jasnosc+=50;
    display();
    delay(100);
  }
  if(!digitalRead(KEY_LEFT)) {
    jasnosc-=50;
    display();
    delay(100);
  }
}

void display()
{

  if(jasnosc < 0) {
    jasnosc=0;
  }
  if(jasnosc > 255) {
    jasnosc = 255;
  }
  
  analogWrite(LED1, jasnosc);
}

