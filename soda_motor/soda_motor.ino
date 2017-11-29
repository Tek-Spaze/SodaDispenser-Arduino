/*     Simple Stepper Motor Control Exaple Code

    by Dejan Nedelkovski, www.HowToMechatronics.com

*/


#include <AccelStepper.h>

const int stepsPerRevolution = 6000;  // change this to fit the number of steps per revolution

// defines pins numbers
const unsigned int stepPin = 22;
const unsigned int dirPin = 24;
const unsigned int inPin = 5;
const unsigned int calibPin = 30;
const unsigned int disp1En = 40;

// Define a stepper and the pins it will use
AccelStepper stepper(1, stepPin, dirPin);

void setup()
{
  stepper.setMaxSpeed(600.0f);
  //stepper.setSpeed(200.0f);
  stepper.setAcceleration(200.0);
  pinMode(inPin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(calibPin, INPUT);
  for(int i = 40; i < 46; i++){
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(115200);
  Serial.println("Booting v.1");
}


#define ST_INIT  0
#define ST_NEG   1
#define ST_POS   2
#define ST_RESET 3
#define ST_IDLE  4
#define ST_DISP  5


#define DISPENSERENABLEOFFSET 40

int calibState = ST_IDLE;

int dispenserEn = 0;
void loop()
{
  if (Serial.available() > 0) {
    byte incomingByte = Serial.read();
    calibState = ST_INIT;
    dispenserEn = DISPENSERENABLEOFFSET + incomingByte - '0';
    Serial.println(dispenserEn);
  }

  switch (calibState) {
    case ST_INIT:
      Serial.println("Starting calib...");
      setEnable(dispenserEn);
      calibState = (digitalRead(calibPin) == HIGH ? ST_POS : ST_NEG);
      break;

    case ST_NEG:
      stepper.setSpeed(-200);
      if (digitalRead(calibPin) == HIGH) {
        calibState = ST_POS;
        stepper.setCurrentPosition(0);
        stepper.runToNewPosition(-10);
      }
      stepper.runSpeed();
      break;

    case ST_POS:
      stepper.setSpeed(200);
      if (digitalRead(calibPin) == LOW) {
        calibState = ST_RESET;
      }
      stepper.runSpeed();
      break;

    case ST_RESET:
      stepper.setCurrentPosition(0);
      Serial.println("Calib done");
      calibState = ST_DISP;
      break;
      
    case ST_DISP:
      stepper.runToNewPosition(90);
      stepper.runToNewPosition(0);
      setDisable(dispenserEn);
      calibState = ST_IDLE;

      break;

    case ST_IDLE:
      break;
  }
}

void setEnable(int dispPin){
  digitalWrite(dispPin, HIGH);
}

void setDisable(int dispPin){
  digitalWrite(dispPin, LOW);
}

