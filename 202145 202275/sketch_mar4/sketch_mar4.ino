#include <ISADefinitions.h>

int counter = 0;

void setup() {

  
  Timer4.attachInterrupt(timer);
  Timer4.start(1000000);
}

void loop() {
  delay(1000);
  counter++;
  displayByte(counter);
}

void displayByte(unsigned char bajt) {
  for(int i = 0; i<8; i++) {
    if(bajt & (1<<i)) {
      digitalWrite(LEDS[i], HIGH);
    } else {
      digitalWrite(LEDS[i], LOW);
    }
  }
}

