/* Include the library */
#include "HCMotor.h"
 
/* Pins used to drive the motors */
#define DIR_PIN 8 //Connect to drive modules 'direction' input.
#define CLK_PIN 9 //Connect to drive modules 'step' or 'CLK' input.
#define DIR_PIN_NEG 10 // connect to drive module direction in negative input

#define DIR_PIN_M2 6
#define CLK_PIN_M2 7
 
/* Set the analogue pin the potentiometer will be connected to. */
#define POT_PIN A0
#define POT_PIN2 A1
 
/* Set a dead area at the centre of the pot where it crosses from forward to reverse */
#define DEADZONE 20 
 
/* The analogue pin will return values between 0 and 1024 so divide this up between 
   forward and reverse */
#define POT_REV_MIN 0
#define POT_REV_MAX (512 - DEADZONE)
#define POT_FWD_MIN (512 + DEADZONE)
#define POT_FWD_MAX 1024
 
 
/* Create an instance of the library */
HCMotor HCMotor;
 
 
 
void setup() 
{
//  Serial.begin(9600);
  /* Initialise the library */
  HCMotor.Init();
 
  /* Attach motor 0 to digital pins 8 & 9. The first parameter specifies the 
     motor number, the second is the motor type, and the third and forth are the 
     digital pins that will control the motor */
  HCMotor.attach(0, STEPPER, CLK_PIN, DIR_PIN);
  HCMotor.attach(1, STEPPER, CLK_PIN, DIR_PIN_NEG);
  HCMotor.attach(2, STEPPER, CLK_PIN_M2, DIR_PIN_M2);
 
  /* Set the number of steps to continuous so the the motor is always turning whilst 
     not int he dead zone*/
  HCMotor.Steps(0,CONTINUOUS);
  HCMotor.Steps(1,CONTINUOUS);
  HCMotor.Steps(2,CONTINUOUS);
}
 
 
void loop() 
{
  int Speed, Speed2, Pot, Pot2;
 
  /* Read the analogue pin to determine the position of the pot. */
  Pot = analogRead(POT_PIN);
  Pot2 = analogRead(POT_PIN2);
  
/*MOTOREN BASIS*/ 
  /* Is the pot in the reverse position ? */
  if (Pot >= POT_REV_MIN && Pot <= POT_REV_MAX)
  {
    HCMotor.Direction(0, REVERSE);
    Speed = map(Pot, POT_REV_MIN, POT_REV_MAX, 10, 1024);
    HCMotor.Direction(1, FORWARD);
 
  /* Is the pot in the forward position ? */
  }else if (Pot >= POT_FWD_MIN && Pot <= POT_FWD_MAX)
  {
    HCMotor.Direction(0, FORWARD);
    Speed = map(Pot, POT_FWD_MIN, POT_FWD_MAX, 1024, 10);
    HCMotor.Direction(1, REVERSE);
 
  /* Is the pot in the dead zone ? */
  }else
  {
    Speed = 0;
  }
 
/*MOTOR 2e sectie*/  
  if (Pot2 >= POT_REV_MIN && Pot2 <= POT_REV_MAX)
  {
    HCMotor.Direction(2, REVERSE);
    Speed2 = map(Pot2, POT_REV_MIN, POT_REV_MAX, 10, 1024);
  
  /* Is the pot in the forward position ? */
  }else if (Pot2 >= POT_FWD_MIN && Pot2 <= POT_FWD_MAX)
  {
    HCMotor.Direction(2, FORWARD);
    Speed2 = map(Pot2, POT_FWD_MIN, POT_FWD_MAX, 1024, 10);
 
  /* Is the pot in the dead zone ? */
  }else
  {
    Speed2 = 0;
  }
 
  /* Set the duty cycle of the clock signal in 100uS increments */
  HCMotor.DutyCycle(0, Speed);
  HCMotor.DutyCycle(1, Speed);
  HCMotor.DutyCycle(2, Speed2);  
//  Serial.println(Speed);
 
}
