#include "ISAMobile.h"

#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

Fuzzy* fuzzy = new Fuzzy();

#define POLNOC 127

QMC5883 qmc;


void setup(void)
{
	// Czujniki ultradźwiekowe
	for (int i = (int)UltraSoundSensor::__first; i <= (int)UltraSoundSensor::__last; i++)
	{
		pinMode(ultrasound_trigger_pin[i], OUTPUT);
		pinMode(ultrasound_echo_pin[i], INPUT);
		
		digitalWrite(ultrasound_trigger_pin[i], 0);
	}
	
	// Silniki
	pinMode(A_PHASE, OUTPUT);
	pinMode(A_ENABLE, OUTPUT);
	pinMode(B_PHASE, OUTPUT);
	pinMode(B_ENABLE, OUTPUT);
	pinMode(MODE, OUTPUT);

	digitalWrite(MODE, true);
	SetPowerLevel(PowerSideEnum::Left, 0);
	SetPowerLevel(PowerSideEnum::Right, 0);

	Serial.begin(9600);
	Serial.print("Test... ");
	
	Wire.begin();
	qmc.init();
	
	Serial1.begin(9600); // HC06

  //polnoc
  //initialize the variables we're linked to
  
  //Fuzzy logic
  FuzzyInput* odchylenie = new FuzzyInput(1);
  FuzzyOutput* prawo = new FuzzyOutput(1);
  FuzzyOutput* lewo = new FuzzyOutput(2);

  //fuzy input sets
  FuzzySet* odchylony_w_lewo = new FuzzySet(0, 0, 0, 127);
  odchylenie->addFuzzySet(odchylony_w_lewo);
  FuzzySet* odchylony_w_prawo = new FuzzySet(127, 255, 255, 255);
  odchylenie->addFuzzySet(odchylony_w_prawo);

  //fuzzy output sets
  FuzzySet* jedz_w_prawo = new FuzzySet(1000, 1000, 1000, 0);
  prawo->addFuzzySet(jedz_w_prawo);
  FuzzySet* jedz_w_lewo = new FuzzySet(1000, 1000, 1000, 0);
  lewo->addFuzzySet(jedz_w_lewo);

  //dodawanie do fuzy
  fuzzy->addFuzzyInput(odchylenie);
  fuzzy->addFuzzyOutput(prawo);
  fuzzy->addFuzzyOutput(lewo);

  //reguły if
  FuzzyRuleAntecedent* ifOdchylonyWLewo = new FuzzyRuleAntecedent();
  ifOdchylonyWLewo->joinSingle(odchylony_w_lewo);
  FuzzyRuleAntecedent* ifOdchylonyWPrawo = new FuzzyRuleAntecedent();
  ifOdchylonyWPrawo->joinSingle(odchylony_w_prawo);

  //reguly then
  FuzzyRuleConsequent* thenJedzWLewo = new FuzzyRuleConsequent();
  thenJedzWLewo->addOutput(jedz_w_lewo);
  FuzzyRuleConsequent* thenJedzWPrawo = new FuzzyRuleConsequent();
  thenJedzWPrawo->addOutput(jedz_w_prawo);

  //zasady
  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifOdchylonyWLewo, thenJedzWPrawo);
  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifOdchylonyWPrawo, thenJedzWLewo);

  fuzzy->addFuzzyRule(fuzzyRule1);
  fuzzy->addFuzzyRule(fuzzyRule2);
  
}

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

void SetPowerLevel(PowerSideEnum side, int level)
{
  level = constrain(level, -255, 255);
  
  if (side == PowerSideEnum::Right) {
    if (level > 0) {
      // do przodu
      digitalWrite(A_PHASE, 1);
      analogWrite(A_ENABLE, level);
    } else if (level < 0) {
      // do tyłu
      digitalWrite(A_PHASE, 0);
      analogWrite(A_ENABLE, -level);
    } else {
      // stop
      digitalWrite(A_PHASE, 0);
      analogWrite(A_ENABLE, 0);
    }
  }
  
  if (side == PowerSideEnum::Left) {
    if (level > 0) {
      // do przodu
      digitalWrite(B_PHASE, 1);
      analogWrite(B_ENABLE, level);
    } else if (level < 0) {
      // do tyłu
      digitalWrite(B_PHASE, 0);
      analogWrite(B_ENABLE, -level);
    } else {
      // stop
      digitalWrite(B_PHASE, 0);
      analogWrite(B_ENABLE, 0);
    }
  } 
}

int measureSoundSpeed(int trigger_pin, int echo_pin)
{
	digitalWrite(trigger_pin, false);
	delayMicroseconds(2);

	digitalWrite(trigger_pin, true);
	delayMicroseconds(10);
	digitalWrite(trigger_pin, false);

	// zmierz czas przelotu fali dźwiękowej
	int duration = pulseIn(echo_pin, true, 50 * 1000);
	

	// przelicz czas na odległość (1/2 Vsound(t=20st.C))
	int distance = (int)((float)duration * 0.03438f * 0.5f);
	return distance;
}

#if 0
void loop(void)
{
	delay(1000);


	SetPowerLevel(Side_Left, 100);
	delay(2000);

	SetPowerLevel(Side_Left, 200);
	delay(2000);

	SetPowerLevel(Side_Left, 255);
	delay(2000);


	SetPowerLevel(Side_Left, 0);
	SetPowerLevel(Side_Right, 0);

	SetPowerLevel(Side_Left, -100);
	delay(2000);

	SetPowerLevel(Side_Left, -200);
	delay(2000);

	SetPowerLevel(Side_Left, -255);
	delay(2000);

	SetPowerLevel(Side_Left, 0);
	SetPowerLevel(Side_Right, 0);
	delay(4000);
	
	
		
	
	delay(1000);

	SetPowerLevel(Side_Right, 100);
	delay(2000);

	SetPowerLevel(Side_Right, 200);
	delay(2000);

	SetPowerLevel(Side_Right, 255);
	delay(2000);


	SetPowerLevel(Side_Right, 0);
	SetPowerLevel(Side_Right, 0);

	SetPowerLevel(Side_Right, -100);
	delay(2000);

	SetPowerLevel(Side_Right, -200);
	delay(2000);

	SetPowerLevel(Side_Right, -255);
	delay(2000);

	SetPowerLevel(Side_Right, 0);
	SetPowerLevel(Side_Right, 0);
	delay(4000);
}


void xloop() {
	
	qmc.measure();
	int16_t x = qmc.getX();
	int16_t y = qmc.getY();
	int16_t z = qmc.getZ();

	char buf[100];
	sprintf(buf, "\n %5d %5d %5d", x, y, z);
	Serial.print(buf);
	delay(100);
}



#endif


void cmd_proximity(const char* msg, UltraSoundSensor sensor)
{
	char buffer[64];
	int d[5] = {};
	int sum = 0;
	int id = 0;
	
	while (Serial.available() == 0)
	{
		int dist = measureSoundSpeed(
			ultrasound_trigger_pin[(int)sensor],
			ultrasound_echo_pin[(int)sensor]);

		// średnia krocząca
		sum -= d[id];
		sum += d[id] = dist;
		id = (id + 1) % 5;
		dist = sum / 5;

		sprintf(buffer, "\n%s: %0dcm", msg, dist);
		Serial.print(buffer);
	}
	
	while (Serial.available())
		Serial.read();	
}


void cmd_qmc(void)
{
	char buffer[64];
  
	qmc.reset();
	while (Serial.available() == 0)
	{
		qmc.measure();
		int16_t x = qmc.getX();
		int16_t y = qmc.getY();
		int16_t z = qmc.getZ();

		sprintf(buffer, "\n X=%5d Y=%5d Z=%5d", x, y, z);
		Serial.print(buffer);
	}
	
	while (Serial.available())
		Serial.read();	
}


void cmd_bluetooth(void)
{
	Serial.println("### HC06: Tryb komunikacji z modułem HC06. Aby wyjść, wpisz \"++++++\"...");
	Serial.println("### Uwaga! Moduł analizuje czas otrzymywania danych; polecenie musi");
	Serial.println("###        kończyć się krótką przerwą (ok. 500ms) BEZ znaku nowej linii");
	Serial.print("\n> ");
	
	int plus_counter = 0;
  int number_counter = 0;
  int number[6];
  int joy_x,joy_y;
	while (true) {
		int b = 0;
		if (Serial.available()) {
			
			b = Serial.read();
		
			if (b == '+') {
				plus_counter++;
				if (plus_counter >= 6)
					break; // wyjdź na 6 plusów
			}
		
			Serial1.write(b);	// wyślij do hc06
			Serial.write(b);	// echo lokalne
  
		}
			
		if (Serial1.available()) {
			int b = Serial1.read();
      if(!(b>0 && b<10))
        {
          //Serial.write(b);
          number[number_counter] = changeToNumber(b);
          number_counter++;
          
        }
       if(number_counter == 6)
       {

        joy_x = ( number[0] * 100 + number[1] * 10 + number[2]);
        joy_y = ( number[3] * 100 + number[4] * 10 + number[5]);
        
        Serial.print(joy_x);
        Serial.print(joy_y);
        Serial.println();
        number_counter = 0;

        jedz(joy_x, joy_y);
       }
			  
		}
		
	}
	
	Serial.println("HC06: Koniec.");
}

void jedz(int joy_x, int joy_y)
{
  int speed = 125;
  int power = map(joy_y, 100, 300, -speed, speed);
  int turn = map(joy_x, 100, 300, speed, -speed);

  SetPowerLevel(PowerSideEnum::Right, cut(power+turn, -speed, speed));
  SetPowerLevel(PowerSideEnum::Left, cut(power-turn, -speed, speed));
}

void cmd_polnoc500()
{
  qmc.reset();
  while(1)
  {
    
    qmc.measure();
    int16_t x = qmc.getX();
    int16_t y = qmc.getY();
    int16_t z = qmc.getZ();
    
    fuzzy->setInput(1, cut(x, 0, 255));
    fuzzy->fuzzify();

    char msg[128];
    float prawo = fuzzy->defuzzify(1);
    float lewo = fuzzy->defuzzify(2);
    prawo = (prawo > 0) ? (prawo - 500) : 0;
    lewo = (lewo > 0) ? (lewo - 500) : 0;
    
    SetPowerLevel(PowerSideEnum::Right, 127 + lewo);
    SetPowerLevel(PowerSideEnum::Left, 127 + prawo);
    
    sprintf(msg, "Y: %d Prawo: %f Lewo: %f", x, prawo, lewo);
    Serial.println(msg);
  }
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

void loop(void)
{
  cmd_polnoc500();
  return;
  
	delay(1000);
	for (int i = 0; i < 10; i++)
	{
		Serial.print((char)(43+2*(i&1)));
		delay(200);
	}
	Serial.println();
	Serial.println("=======================================================");
	Serial.println("# Programowanie Systemow Autonomicznych               #");
	Serial.println("# Tester autek v1.0 Tomasz Jaworski, 2018             #");
	Serial.println("=======================================================");
	Serial.println("Polecenia powinny konczyc sie wylacznie znakiem '\\n'.");
	Serial.println("ARDUINO IDE: Zmień 'No line ending' na 'Newline' w dolnej części okna konsoli...\n");
	
	while(1)
	{
		Serial.print("> ");

		String s = "";
		while(true)
		{
			while(Serial.available() == 0);
			int ch = Serial.read();
			if (ch == '\n')
				break;
			s += (char)ch;
		}
		
		s.trim();
		s.toLowerCase();
		Serial.println(s);
		
		//
		
		if (s == "help")
		{
			Serial.println("Pomoc:");
			Serial.println("   proxf - odczytuj czujnik odleglosc (PRZEDNI)");
			Serial.println("   proxb - odczytuj czujnik odleglosc (TYLNY)");
			Serial.println("   proxl - odczytuj czujnik odleglosc (LEWY)");
			Serial.println("   proxr - odczytuj czujnik odleglosc (PRAWY)");
			
			Serial.println("   mSD p - ustaw wysterowanie silnika napędowego");
			Serial.println("   		S (strona): 'L'-lewa, 'R'-prawa, 'B'-obie");
			Serial.println("   		D (kierunek): 'F'-do przodu, 'B'-do tyłu, 'S'-stop");
			Serial.println("   		n (wysterowanie): poziom sterowania 0-255");
			Serial.println("   reset - reset");
			Serial.println("   qmc   - odczytuj pomiary pola magnetycznego w trzech osiach");
			Serial.println("   bt    - komunikacja z modułem HC06 (Bluetooth)");
			continue;
		}
		
		if (s == "reset") {
			Serial.println("Ok.");
			delay(1000);
			RSTC->RSTC_MR = 0xA5000F01;
			RSTC->RSTC_CR = 0xA500000D;
			while(1);
		}
		
		if (s == "bt") {
			cmd_bluetooth();
			continue;
		}
		
		if (s == "proxf") {
			cmd_proximity("PRZOD", UltraSoundSensor::Front);
			continue;
		}
		
		if (s == "proxb") {
			cmd_proximity("TYL", UltraSoundSensor::Back);
			continue;
		}
		
		if (s == "proxl") {
			cmd_proximity("LEWY", UltraSoundSensor::Left);
			continue;
		}
		
		if (s == "proxr") {
			cmd_proximity("PRAWY", UltraSoundSensor::Right);
			continue;
		}

		if (s == "qmc") {
			cmd_qmc();
			continue;
		}
   
   if (s == "polnoc500") {
      cmd_polnoc500();
      continue;
    }

		if (s.startsWith("m")) {
			if (s.length() < 3) {
				Serial.println("Polecenie 'm': bład w poleceniu");
				continue;
			}
			
			int side = tolower(s[1]);
			int direction = tolower(s[2]);
			int power = -1;
			if (s.indexOf(" ") != -1) {
				s = s.substring(s.lastIndexOf(" ") + 1);
				char *endptr = NULL;
				power = strtol(s.c_str(), &endptr, 10);
				if (*endptr != '\0') {
					Serial.println("Polecnie 'm': bład w zapisie wartości wystarowania");
					continue;
				}
			}
			
			if (strchr("lrb", side) == NULL) {
				Serial.println("Polecnie 'm': bład w formacie strony");
				continue;
			}
				
			if (strchr("fbs", direction) == NULL) {
				Serial.println("Polecnie 'm': bład w formacie kierunku");
				continue;
			}
			
			if (direction != 's' && power == -1) {
				Serial.println("Polecnie 'm': brak podanej wartości wysterowania");
				continue;
			}
				
			// przekształcenia
			bool left = side == 'l' || side == 'b';
			bool right = side == 'r' || side == 'b';
			power = direction == 's' ? 0 : power;
			power = direction == 'b' ? -power : power;

			char msg[128];
			sprintf(msg, "Ustawienia: L=%d, R=%d, power=%d\n", left, right, power);
			Serial.print(msg);
			if (left)
				SetPowerLevel(PowerSideEnum::Left, power);
			if (right)
				SetPowerLevel(PowerSideEnum::Right, power);
			
			continue;
		}

		Serial.print(" Polecenie '");
		Serial.print(s);
		Serial.print("' jest nieznane; Może 'help'?\n");
	}
}
