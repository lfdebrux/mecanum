#include "mecanum.h"

// default to no movement if no pulse is detected
// or the signal is very close to centre
rc_pulse_t sanitise(rc_pulse_t in) {
  if (in != 0) {
    in -= NORM_WIDTH;
    if (abs(in) < DEADZONE) {
      in = 0;
    }
  }
  return in;
}

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
  ForwardDuration = pulseIn(Forward, HIGH, timeout);
  StrafeDuration = pulseIn(Strafe, HIGH, timeout);
  RotateDuration = pulseIn(Rotate, HIGH, timeout);

  ForwardDuration = sanitise(ForwardDuration);
  StrafeDuration = sanitise(StrafeDuration);
  RotateDuration = sanitise(RotateDuration);

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
    Serial.print(StrafeDuration);
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
