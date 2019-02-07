#include "ISAMobile.h"

void setup(void)
{
  isaInit();
  fuzzyInit();
}

void loop(void)
{
  int16_t x;
  int16_t y;
  int16_t z;

  float prawo, lewo;
  fuzzy_calculate(x, &prawo, &lewo);
  
  prawo = (prawo > 0) ? (prawo - 500) : 0;
  lewo = (lewo > 0) ? (lewo - 500) : 0;
  
  SetPowerLevel(PowerSideEnum::Right, 127 + lewo);
  SetPowerLevel(PowerSideEnum::Left, 127 + prawo);

  char msg[128];
  sprintf(msg, "Y: %d Prawo: %f Lewo: %f", x, prawo, lewo);
  Serial.println(msg);
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

int changeToNumber(int i){
  switch(i){
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
