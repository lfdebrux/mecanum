#include <mecanum.h>

void setup()
{
  if (debug) Serial.begin(9600);
  FLS.attach(Fl);
  FRS.attach(Fr);
  RLS.attach(Rl);
  RRS.attach(Rr);
  pinMode(Forward, INPUT);
  pinMode(Strafe, INPUT);
  pinMode(Rotate, INPUT);
}

void loop()
{
  // read receiver signals
  ForwardDuration = pulseIn(Forward, HIGH, timeout) - NORM_WIDTH;
  StrafeDuration = pulseIn(Strafe, HIGH, timeout) - NORM_WIDTH;
  RotateDuration = pulseIn(Rotate, HIGH, timeout) - NORM_WIDTH;

  // default to no movement if no pulse is detected
  // or the signal is very close to centre
  if (ForwardDuration != 0 && abs(ForwardDuration) < DEADZONE) {
    ForwardDuration = 0;
  }
  if (StrafeDuration != 0 && abs(StrafeDuration) < DEADZONE) {
    StrafeDuration = 0;
  }
  if (RotateDuration != 0 && abs(RotateDuration) < DEADZONE) {
    RotateDuration = 0; 
  }

  // mix the signals
  FL = ForwardDuration + StrafeDuration + RotateDuration + NORM_WIDTH;
  FR = ForwardDuration - StrafeDuration - RotateDuration + NORM_WIDTH;
  RL = ForwardDuration - StrafeDuration + RotateDuration + NORM_WIDTH;
  RR = ForwardDuration + StrafeDuration - RotateDuration + NORM_WIDTH;

  // clamp the outputs
  FL = constrain(FL, MIN_WIDTH, MAX_WIDTH);
  FR = constrain(FR, MIN_WIDTH, MAX_WIDTH);
  RL = constrain(RL, MIN_WIDTH, MAX_WIDTH);
  RR = constrain(RR, MIN_WIDTH, MAX_WIDTH);

  // set servo library outputs
  FLS.writeMicroseconds(FL);
  FRS.writeMicroseconds(FR);
  RLS.writeMicroseconds(RL);
  RRS.writeMicroseconds(RR);

  if (debug) {
    Serial.print(ForwardDuration);
    Serial.print(", ");
    Serial.print(RotateDuration);
    Serial.print(" => ");
    Serial.print(FL);
    Serial.print(", ");
    Serial.print(FR);
    Serial.print(", ");
    Serial.print(RL);
    Serial.print(", ");
    Serial.print(RR);
    Serial.println();
  }
}
