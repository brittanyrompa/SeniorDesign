#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo  
 
void setup() 
{ 
  myservo.attach(9,850,1855);  // attaches the servo on pin 9 to the servo object 
} 
  
void loop() 
{ 
    myservo.write(0);              // tell servo to go to the 0 degree position
    delay(5000);                   // waits 5s for interactor to be lowered onto the cube
  
    
    for(int i = 0; i < 180; i += 15){  //loop to rotate back and forth, incrementing to 180 degrees. The back and forth rotation helps the servo and keeps the cube from locking up.
      myservo.write(180);              //start moving to 180 degrees
      delay(150);                      //wait for servo to begin to move
      myservo.write(i - 15);           //move back 15 degrees
      delay(150);                      //wait for servo to begin to move
    };
    
    for(int i = 165; i < 180; i += 5){  //loop to rotate back and forth, this time at lower increments to reach 180 degrees.
      myservo.write(180);               //start moving to 180 degrees 
      delay(150);                       //wait for servo to begin to move
      myservo.write(i - 5);             //move back 15 degrees
      delay(150);                       //wait for servo to begin to move
    };
   
    while(true){};  //pause loop
  
}
