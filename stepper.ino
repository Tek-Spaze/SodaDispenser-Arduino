/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */


#include <AccelStepper.h>

const int stepsPerRevolution = 6000;  // change this to fit the number of steps per revolution

// defines pins numbers
const unsigned int stepPin = 3; 
const unsigned int dirPin = 4;
const unsigned int inPin = 5;

// Define a stepper and the pins it will use
AccelStepper stepper(1, stepPin,dirPin);

void setup()
{  
    stepper.setMaxSpeed(200.0);
    stepper.setAcceleration(100.0);
    pinMode(inPin, INPUT);
    pinMode(13, OUTPUT);
    Serial.begin(115200);
}

void loop()
{    
    if (Serial.available() > 0) {
      byte incomingByte = Serial.read();
      if(incomingByte == '1'){
        digitalWrite(13, HIGH);
        stepper.runToNewPosition(150);
        stepper.runToNewPosition(0);
        digitalWrite(13, LOW);
      }
    }
}

