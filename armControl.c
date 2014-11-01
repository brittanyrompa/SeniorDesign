#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <servo.h>

//using motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
int mPin = 1;
int stPin = 2;

//motor
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(mPin);

//servo
int sPin = 10;
Servo myServo;
int lDeg = 0;
int rDeg = 179;

//stepper
int steps = 200;
Adafruit_StepperMotor *myStepper = AFMS.getStepper(steps, stPin);

void setup(void){
	//setup motor
	AFMS.begin();  

	//set motor speed
	myMotor1->setSpeed(50);
	
	//setup servo
	myServo.attach(sPin);
	
	//call lower
	lower();
	
	//call run
	run();
	
	//call raise();
	raise();
}

void lower(){
	//rotates motor
	myMotor->run(FORWARD)
	
	//stop motor
	if(/*pressure plate condition*/){
		myMotor->run(RELEASE);
	}
	
	//rotates servo
	myServo.write(lDeg);
	
	//rotates stepper
	step(#steps, direction, steptype)
}

void run(){
	if(/*at Etch*/){
		//call etch code
	}

	else if(/*at Rubik*/){
		//call rubik code
	}

	else if(/*at Simon*/){
		//call simon code
	}

	else if(/*at card*/){
		//call card code
	}
}

void raise(){
	//rotates motor
	myMotor->run(BACKWARD)
	
	//stop motor
	if(/*pressure plate condition*/){
		myMotor->run(RELEASE);
	}
	
	//rotates servo
	myServo.write(rDeg);
	
	//rotates stepper
	step(#steps, direction, steptype)
}
