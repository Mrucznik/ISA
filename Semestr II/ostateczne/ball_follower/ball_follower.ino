#include "ISAMobile.h"

#define STOP_PROXIMITY 0
#define STOP_ON_BALL_PROXIMITY 0

void setup(void)
{
  isaInit();
  fuzzyInit();
}

void loop(void)
{
  //stop on collision
  int sensor = (int)UltraSoundSensor::Front;
  int proximity = measureSoundSpeed(ultrasound_trigger_pin[sensor], ultrasound_echo_pin[sensor]);

  if(proximity < STOP_PROXIMITY) {
    SetPowerLevel(PowerSideEnum::Right, 0);
    SetPowerLevel(PowerSideEnum::Left, 0);
    
    Serial.println("Przeszkoda! ");
    return;
  }

  //read serial
  String s = "";
  while(true)
  {
    while(Serial.available() == 0);
    int ch = Serial.read();
    if (ch == '\n')
      break;
    s += (char)ch;
  }

  //przesunięcie
  if(s.startsWith("y")) {
    s = s.substring(s.lastIndexOf(" ") + 1);
    char *endptr = NULL;
    int yaw = strtol(s.c_str(), &endptr, 10);
    if (*endptr != '\0') {
      Serial.println("Polecnie 'y': bład w zapisie wartości");
      return;
    }

    if(proximity < STOP_ON_BALL_PROXIMITY) {
      SetPowerLevel(PowerSideEnum::Right, 0);
      SetPowerLevel(PowerSideEnum::Left, 0);
      
      Serial.println("Pilka zbyt blisko");
      return;
    }
  
    float prawo, lewo;
    fuzzy_calculate(yaw, &prawo, &lewo);
    
    prawo = (prawo > 0) ? (prawo - 500) : 0;
    lewo = (lewo > 0) ? (lewo - 500) : 0;

    //int speed = map(proximity, 40, 60, 50, 127);
    
    SetPowerLevel(PowerSideEnum::Right, 127 + lewo);
    SetPowerLevel(PowerSideEnum::Left, 127 + prawo);
  
    char msg[128];
    sprintf(msg, "Y: %d Prawo: %f Lewo: %f", yaw, prawo, lewo);
    Serial.println(msg); 
  } else if(s.startsWith("x")) {
    
  }
}

void jedz(int joy_x, int joy_y)
{
  int speed = 125;
  int power = map(joy_y, 100, 300, -speed, speed);
  int turn = map(joy_x, 100, 300, speed, -speed);

  SetPowerLevel(PowerSideEnum::Right, cut(power+turn, -speed, speed));
  SetPowerLevel(PowerSideEnum::Left, cut(power-turn, -speed, speed));
}


int cut(int val, int min, int max)
{
  if(val < min) return min;
  if(val > max) return max;
  return val;
}

int changeToNumber(int i) {
  switch(i) {
    case 48:
    return 0;
    break;
    case 49:
    return 1;
    break;
    case 50:
    return 2;
    break;
    case 51:
    return 3;
    break;
    case 52:
    return 4;
    break;
    case 53:
    return 5;
    break;
    case 54:
    return 6;
    break;
    case 55:
    return 7;
    break;
    case 56:
    return 8;
    break;
    case 57:
    return 9;
    break;
  }
}
