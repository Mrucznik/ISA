#include <ISADefinitions.h>
#include <ISAButtons.h>
#include <ISALiquidCrystal.h>
ISALiquidCrystal lcd;
ISAButtons button;

char napis[26];
int idx = 0;

void setup() {
  button.init();
  pinMode(BUZZER, OUTPUT);
  lcd.begin();
}

void loop() {
  if(button.buttonPressed(14)){
    napis[idx++] = '0';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(8)){
    napis[idx++] = '1';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(9)){
    napis[idx++] = '2';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(10)){
    napis[idx++] = '3';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(7)){
    napis[idx++] = '4';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(6)){
    napis[idx++] = '5';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(5)){
    napis[idx++] = '6';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(0)){
    napis[idx++] = '7';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(1)){
    napis[idx++] = '8';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  if(button.buttonPressed(2)){
    napis[idx++] = '9';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  
  if(button.buttonPressed(12))//+
  {
    napis[idx++] = '+';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  
  if(button.buttonPressed(11))//-
  {
    napis[idx++] = '-';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  
  if(button.buttonPressed(4))//*
  {
    napis[idx++] = '*';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }
  
  if(button.buttonPressed(3))///
  {
    napis[idx++] = '/';
    lcd.clear();
    lcd.print(napis);
    delay(300);
  }

  if(button.buttonPressed(15)) { //Cancle
    for(int i=0; i<sizeof(napis); i++)
    {
      napis[i] = '\0';
    }
    idx = 0;
    lcd.clear();
    delay(300);
  }
  
  if(button.buttonPressed(13)) { //separator dziesiętny - enter
    int a=0,b=0,wynik=0;
    char znak=0;
    sscanf(napis, "%d%c%d", &a, &znak, &b);
    switch(znak)
    {
      case '+':
        wynik = a+b;
        break;
      case '-':
        wynik = a-b;
        break;
      case '*':
        wynik = a*b;
        break;
      case '/':
        wynik = a/b;
        break;
    }
    lcd.setCursor(0,1);
    lcd.print("=");
    lcd.print(wynik);
    delay(300);
  }
}
