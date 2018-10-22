#include <ISADefinitions.h>
#include <ISAButtons.h>

ISAButtons button;
int number;

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
  number = 0;
  pinMode(BUZZER, OUTPUT);
  button.init();
}

void loop() {

  setNumber();
  if(button.buttonPressed(4)){
    getNumber();
  }
  
  

}

void setNumber(){
  if(button.buttonPressed(14)){
    number = 0;
  }
  if(button.buttonPressed(8)){
    number = 1;
  }
  if(button.buttonPressed(9)){
    number = 2;
  }
  if(button.buttonPressed(10)){
    number = 3;
  }
  if(button.buttonPressed(7)){
    number = 4;
  }
  if(button.buttonPressed(6)){
    number = 5;
  }
  if(button.buttonPressed(5)){
    number = 6;
  }
  if(button.buttonPressed(0)){
    number = 7;
  }
  if(button.buttonPressed(1)){
    number = 8;
  }
  if(button.buttonPressed(2)){
    number = 9;
  }
  if(button.buttonPressed(12)){
    number = 0;
    getNumber();
  }
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
