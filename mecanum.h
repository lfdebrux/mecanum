#ifndef mecanum_h
#define mecanum_h

#include <Servo.h>

#define debug false

const unsigned long timeout = 30000;

const int DEADZONE = 100;

const int Forward = 11; //Inputs from RC receiver
const int Strafe = 12;  
const int Rotate = 13;  

// outputs to motor controllers
const int Fl = 9;
const int Fr = 6;
const int Rl = 5;
const int Rr = 3;

typedef signed int rc_pulse_t;
typedef signed int servo_pulse_t;

const servo_pulse_t MIN_WIDTH = 1000;
const servo_pulse_t NORM_WIDTH = 1500;
const servo_pulse_t MAX_WIDTH = 1500;

rc_pulse_t ForwardDuration; //To store the duration of the pulses
rc_pulse_t StrafeDuration;    //coming from the receiver
rc_pulse_t RotateDuration;

Servo FLS; //front left servo
Servo FRS; //front right servo...
Servo RLS;
Servo RRS;

servo_pulse_t FL; //Front Left Value
servo_pulse_t FR; //Front Right Value...
servo_pulse_t RL;
servo_pulse_t RR;

#endif
