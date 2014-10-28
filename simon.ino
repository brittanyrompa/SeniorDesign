/*
Written by Greg Carkin

Program sets up 8 pins for reading photocell sensors.
Pin data is temporarily stored in a state array.

As sensors store data in state array, their value is checked against
the max. If their value is greater than the current max, the current 
sensor value is the new max value. If there is a max value found that 
is greater than the accepted normal light value, a servo rotates the 
holding rod and another servo presses the rod down, then up.
*/

#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_PWMServoDriver.h"

#include <Servo.h> 
 
int motorPin1 =  6;    // One motor wire connected to digital pin 6 
int motorPin2 =  5;    // One motor wire connected to digital pin 5 black


int nDRatio = 1200;
int cSpeed = 200;
int offset = 350;

//counter
int i;

//photocell variables
int pcPin[4] = {0,1,2,3}; //array of pins
int tmpState[4]; //array for pin states
int lMax; //max light level recorded
int sMax; //sensor number that recorded max light level

/*
//servo variables
Servo rS; //rotation servo
Servo vS; //vertical servo
int gr = 2; //gear ratio between servo and rod
int sRP = 9; //what ever the servo pins are 
int sVP = 10; //what ever the servo pins are
int down = 30; //degrees needed to push the vertical rod down
int rot = 360/8/gr; //degrees between each sensor divided by gear ratio
int wT = 100; //wait timer
*/

//stepper variables
// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
//Adafruit_StepperMotor *myMotor = AFMS.getStepper(513, 1);
//int mPort = 2;
//int steps = 513;
//int sens = 4;
//double sDeg = steps/360.0;
//double dSMax;


void setup(void){
	
	//read at 9600 bits per second
	Serial.begin(9600);
	 
	//start stepper
	//AFMS.begin(1000);
	
	//myMotor->setSpeed(20);
	
  // initialize the digital pins as an output:
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT);  	
}

void loop(void){
	//reset max
         lMax = 0;
         sMax = 0;
	
	//set state
	for(i=0; i<4; i++){
	
		//store current sensor reading
		tmpState[i] = analogRead(pcPin[i]);
               // Serial.print(i);
               // Serial.print("/t");
              //Serial.println(tmpState[i]);
		
		//set max reading
		if(tmpState[i] > lMax){
			lMax = tmpState[i];
			sMax = i;
		}

	}
        //Serial.println("");
   if(lMax > 75){
      if(sMax == 0){
             Serial.println("1st quad sensed");
             	delay(3000);
		
        Serial.print("Aligned, press down)");
      }
      
      else if(sMax == 1){
             Serial.println("2nd quad sensed ");
	    rotateRight(cSpeed, nDRatio);
	delay(3000);
            rotateLeft(cSpeed, nDRatio - offset);
		
        Serial.print("Aligned, press down)");
      }
      
      else if(sMax == 2){
             Serial.println("3rd quad sensed");
	    rotateRight(cSpeed, 2 * nDRatio);
	delay(3000);
            rotateLeft(cSpeed, 2 * nDRatio - 2 * offset);
		
        Serial.print("Aligned, press down)");
      }
      
      else if(sMax == 3){
             Serial.println("4th quad sensed");
	    rotateRight(cSpeed, 3 * nDRatio);

            	delay(3000);
            rotateLeft(cSpeed, 3 * nDRatio - 3 * offset);
		
        Serial.print("Aligned, press down)");
      }
      
        Serial.print("Pin ");
        Serial.print(sMax);
        Serial.print(" saw light of: ");
        Serial.println(lMax);
	


	//while(true){
        
        //}
      }
	
	delay(10);
}


void rotateLeft(int speedOfRotate, int length){
  analogWrite(motorPin1, speedOfRotate); //rotates motor
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
  delay(length); //waits
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
}

void rotateRight(int speedOfRotate, int length){
  analogWrite(motorPin2, speedOfRotate); //rotates motor
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
  delay(length); //waits
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
}
