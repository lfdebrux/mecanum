#ifndef mecanum_h
#define mecanum_h

#include <Servo.h>

#define DEBUG false

const unsigned long MIN_WIDTH = 1000;
const unsigned long NORM_WIDTH = 1500;
const unsigned long MAX_WIDTH = 1500;

const unsigned long timeout = 30000;

const int DEADZONE = 100;

const int Forward = 7; //Inputs from RC receiver
const int Strafe = 2;  
const int Rotate = 3;  

const int Fl = 10;
const int Fr = 9;
const int Rl = 6;
const int Rr = 5;

typedef signed long rc_pulse_t;
typedef unsigned long servo_pulse_t; 

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
