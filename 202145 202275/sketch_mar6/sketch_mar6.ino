#include <ISADefinitions.h>
#include <DueTimer.h>

int state = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  Timer4.attachInterrupt(dioda);
  Timer4.start(1000000);
}

void loop() {

}

void dioda(){
  if(state == 2) {
    digitalWrite(LED1, LOW);
  } else {
    digitalWrite(LED1, HIGH);
  }
  state=(state+1)%3;
}

