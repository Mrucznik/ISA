#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double consKp=1, consKi=0.02, consKd=0.05;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void pidInit() {
  //initialize the variables we're linked to
  Input = 0;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

int pidOutput(double input) {
  Input = input;

  myPID.SetTunings(consKp, consKi, consKd);   
  myPID.Compute();

  return (int)Output;
}
