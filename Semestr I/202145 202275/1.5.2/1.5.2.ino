#include <ISADefinitions.h>
#include <ISAButtons.h>
#include <DueTimer.h>
ISAButtons button;

int cyfry[3];
int number=-1;
int czas=0;
int idx = 0;

int mors[10][5] = {
  {1,0,0,0,0},
  {1,1,0,0,0},
  {1,1,1,0,0},
  {1,1,1,1,0},
  {1,1,1,1,1},
  {0,1,1,1,1},
  {0,0,1,1,1},
  {0,0,0,1,1},
  {0,0,0,0,1},
  {0,0,0,0,0}
};

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
  button.init();
  pinMode(BUZZER, OUTPUT);
  
}

void loop() {
  if(idx < 3)
  {
    if(button.buttonPressed(14)){
      cyfry[idx] = 0;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(8)){
      cyfry[idx] = 1;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(9)){
      cyfry[idx] = 2;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(10)){
      cyfry[idx] = 3;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(7)){
      cyfry[idx] = 4;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(6)){
      cyfry[idx] = 5;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(5)){
      cyfry[idx] = 6;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(0)){
      cyfry[idx] = 7;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(1)){
      cyfry[idx] = 8;
      idx++;
      delay(300);
    }
    if(button.buttonPressed(2)){
      cyfry[idx] = 9;
      idx++;
      delay(300);
    }
  }
  
  if(button.buttonPressed(12)){ //+ ustawia 
    if(idx == 1)
    {
      number = cyfry[0];
      displayByte(number);
      buzujMorsem(cyfry[0]);
    } 
    else if(idx == 2)
    {
      number = cyfry[0]*10 + cyfry[1];
      displayByte(number);
      buzujMorsem(cyfry[0]);
      buzujMorsem(cyfry[1]);
    }
    else if(idx == 3)
    {
      number = cyfry[0]*100 + cyfry[1]*10 + cyfry[2];
      displayByte(number);
      buzujMorsem(cyfry[0]);
      buzujMorsem(cyfry[1]);
      buzujMorsem(cyfry[2]);
    }
    idx = 0;
    czas = 0;
  }
  displayByte(number);
}

void buzujMorsem(int number) {
  int* cyfra = mors[number];
  for(int i = 0; i < 5; i++) {
    if(cyfra[i] == 0){
      buzujKreske();
    }
    if(cyfra[i] == 1){
      buzujKropke();
    }
  }
  delay(50);
}

void buzujKropke() {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);
}

void buzujKreske() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(50);
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

