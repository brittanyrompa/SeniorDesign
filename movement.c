#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_PWMServoDriver.h"



#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {3, 4, 5, 6, 7, 8, 9, 10},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);


double Input, Output, Setpoint;
 PID myP(&Input, &Output, &Setpoint,10,1,100, DIRECT);


void setup()
{
  


  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  
  Serial.begin(9600);
  
    delay(1000);
 
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  //motor1
  myMotor1->setSpeed(50);
  myMotor1->run(FORWARD);
  
  
  //motor2
  myMotor2->setSpeed(50);
  myMotor2->run(FORWARD);
    
 Setpoint = 3500;
 myP.SetMode(AUTOMATIC);
 myP.SetOutputLimits(-3000, 3000);
 myP.SetSampleTime(10);

  
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtrrc.read(sensorValues); instead of unsigned int position = qtrrc.readLine(sensorValues);
  unsigned int position = qtrrc.readLine(sensorValues);
  Input = position;
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  
  
  myP.Compute();
  Serial.println(Output);
  
  if(Output < -1000){
    myMotor1->run(RELEASE);
    myMotor2->run(FORWARD);
  }
  else if(Output > 1000){
    myMotor1->run(FORWARD);
    myMotor2->run(RELEASE);
  }
  else{
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
  }
  
  delay(100);
}

