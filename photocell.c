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


//#define pin constants


//counter
int i;

//photocell variables
int pcPin[4] = {0,1,2,3}; //array of pins
int tmpState[4]; //array for pin states
int lMax; //max light level recorded
double sMax; //sensor number that recorded max light level

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
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(513, 1);
int mPort = 2;
int steps = 513;
int sens = 4;
double sDeg = steps/360.0;
double dSMax;


void setup(void){
	
	//read at 9600 bits per second
	Serial.begin(9600);
	
	//start stepper
	AFMS.begin(1000);
	
	myMotor->setSpeed(20);
}

void loop(void){
	//reset max
	lMax = 0;
	sMax = 0.0;
        dSMax = 0.0;
	
	//set state
	for(i=0; i<4; i++){
	
		//store current sensor reading
		tmpState[i] = analogRead(pcPin[i]);
                //Serial.print(i);
                //Serial.println(tmpState[i]);
		
		//set max reading
		if(tmpState[i] > lMax){
			lMax = tmpState[i];
			sMax = dSMax;
		}
                dSMax = dSMax + 1.0;
	}
        //Serial.println("");
   if(lMax > 250){
      if(sMax == 0){
             Serial.println("Yellow Lit up");
      }
      
      else if(sMax == 1){
             Serial.println("Green Lit up");
      }
      
      else if(sMax == 2){
             Serial.println("Red Lit up");
      }
      
      else if(sMax == 3){
             Serial.println("Blue Lit up");
      }
      
      Serial.print("Pin ");
      Serial.print(sMax);
      Serial.print(" saw light of: ");
      Serial.println(lMax);
	  Serial.println("Turning ");
	  Serial.print(sDeg * sMax * 90.0);
	
		
		//myMotor->step( sDeg * sMax * 90.0,FORWARD, DOUBLE);
		//delay(2000);

	}
	
	delay(10);
}
	