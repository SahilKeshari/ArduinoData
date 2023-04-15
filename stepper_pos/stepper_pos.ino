#include <AccelStepper.h>
#include <MultiStepper.h>

const int dirPin = 10;
const int stepPin = 11;

AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup(){
  Serial.begin(9600);
  myStepper.setMaxSpeed(1000);
  myStepper.setSpeed(200);
  myStepper.setAcceleration(100);
  myStepper.moveTo(0);
}

void loop(){
  Serial.println(myStepper.distanceToGo());
  
  myStepper.run();
}