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

void fuzzyInit(void)
{
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

void fuzzy_calculate(int16_t input, float* right, float* left)
{
    fuzzy->setInput(1, cut(input, 0, 255));
    fuzzy->fuzzify();
    
    *right = fuzzy->defuzzify(1);
    *left = fuzzy->defuzzify(2);
}
