#include <ISADefinitions.h>
#include <ISAButtons.h>
#include <DueTimer.h>
#include <ISA7SegmentDisplay.h>
ISAButtons button;
ISA7SegmentDisplay sseg;

int cyfry[3];
int number=-1;
volatile long czas=0;
int idx = 0;

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(LEDS[i], OUTPUT);
  }
  button.init();
  pinMode(BUZZER, OUTPUT);
  Timer4.attachInterrupt(timer);
  Timer4.setFrequency(1);
  Timer4.start(1000000);
  
  sseg.init();
  
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
    } 
    else if(idx == 2)
    {
      number = cyfry[0]*10 + cyfry[1];
    }
    else if(idx == 3)
    {
      number = cyfry[0]*100 + cyfry[1]*10 + cyfry[2];
    }
    idx = 0;
    czas = 0;
    delay(300);
    Timer4.start();
  }
  if(button.buttonPressed(11)){ //- zawies program
    while(true){}
  }

  if(button.buttonPressed(15)) { //Cancle - stop timer
    Timer4.stop();
    delay(300);
  }
  if(button.buttonPressed(13)) { //separator dziesiętny - start timer
    Timer4.start();
    delay(300);
  }
  if(czas == number)
  {
    Timer4.stop();
    buzujimigaj();
    number = -1;
    czas = 0;
  }
  else
  {
    displayByte(czas);
  }
}

void buzujimigaj()
{
  digitalWrite(BUZZER, HIGH);
  for(int i=0; i<8; i++)
  {
    digitalWrite(LEDS[i], HIGH);
  }
  delay(500);
  digitalWrite(BUZZER, LOW);
  for(int i=0; i<8; i++)
  {
    digitalWrite(LEDS[i], LOW);
  }
  delay(500);
}

void timer() {
  czas++;
}

void displayByte(long bajt) {
      sseg.displayDigit(bajt%10, 0);
      sseg.displayDigit((bajt/10)%10, 1);
      sseg.displayDigit((bajt/100)%10, 2);
      sseg.displayDigit((bajt/1000)%10, 3);
}
