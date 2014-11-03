/*
Written by Greg Carkin

Program sets up 4 pins for reading photocell sensors.
Pin data is temporarily stored in a state array.

As sensors store data in state array, their value is checked against
the max. If their value is greater than the current max, the current 
sensor value is the new max value. If there is a max value found that 
is greater than the accepted normal light value, a servo rotates the 
holding rod and another servo presses the rod down, then up.
*/

//dc motor variables
int motorPin1 =  6;	//One motor wire connected to digital pin 6 
int motorPin2 =  5;	//One motor wire connected to digital pin 5 black
int nDRatio = 700;	//time for dc motor to turn
int cSpeed = 200;	//speed for dc motor to turn
int offset = 350;	//offset to account for dc motor turning more forwards than back

//counter
int i;

//photocell variables
int pcPin[4] = {0,1,2,3}; //array of pins
int tmpState[4]; //array for pin states
int lMax; //max light level recorded
int sMax; //sensor number that recorded max light level

//storing variables
int lCount = 0; //value for determining if simon sequence has stopped
int go = 30;
int simonOrder[10] = {5,5,5,5,5,5,5,5,5,5}; //array for simon button order
boolean light = false; //light on / off
boolean stored = false; //did the light that's on get stored
boolean start = false;

void setup(void){
	
	//read at 9600 bits per second
	Serial.begin(9600);
	
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
		
		//set max reading
		if(tmpState[i] > lMax){
			lMax = tmpState[i];
			sMax = i;
		}
	}
	
	//if there is no light sensed, reset light and store
	//increment lCount
	if(lMax < 250){
		light = false;
		stored = false;
		lCount++;
	}
	
	//if there is a light, set light
	//reset lCount
	if(lMax > 250){
		light = true;
		lCount = 0;
                Serial.print(sMax);
                Serial.print(" ");
                Serial.println(lMax);
	}
	
	//if light is on, and it hasn't been stored,
	//store the pin that sensed the light
	//set store back to true
	if(light && !stored){
		for(i=0; i<10; i++){
			if(simonOrder[i] == 5){
				simonOrder[i] = sMax;
                                break;
			}
		}
		stored = true;
		start = true;
	}

	//Serial.println(lCount);
	//if the light has been off for 20 cycles, 
	//send the presser the order to press buttons
	if(lCount > go && start == true){
		press();
                lCount = 0;
                light = false;
                start = false;
	}
	
}

//function for determining how much the rotation plate should turn
void press(void){
	for(i = 0; i<10; i++){
		Serial.print(simonOrder[i]);
	}

        Serial.println(" ");
        Serial.println(" ");
        

	//if first quadrant is sensed dont turn, this is where the pusher is
	/*if(pin == 0){
		Serial.println("1st quad sensed");
		delay(3000);
		Serial.print("Aligned, press down");
	}
      
	//if second quadrant is sensed turn 90 degrees
	else if(pin == 1){
		Serial.println("2nd quad sensed ");
		rotateRight(cSpeed, nDRatio);
		delay(3000);
		rotateLeft(cSpeed, nDRatio - offset);
		Serial.print("Aligned, press down");
	}
      
	//if third quadrant is sensed turn 180 degrees
	else if(pin == 2){
		Serial.println("3rd quad sensed");
		rotateRight(cSpeed, 2 * nDRatio);
		delay(3000);
		rotateLeft(cSpeed, 2 * nDRatio - 2 * offset);
		Serial.print("Aligned, press down");
	}
      
	//if fourth quadrant is sensed turn 270 degrees
	else if(pin == 3){
		Serial.println("4th quad sensed");
		rotateRight(cSpeed, 3 * nDRatio);
		delay(3000);
		rotateLeft(cSpeed, 3 * nDRatio - 3 * offset);
		Serial.print("Aligned, press down");
	}*/
}


void rotateLeft(int speedOfRotate, int length){
	//rotates motor
	analogWrite(motorPin1, speedOfRotate);

 	// set the Pin motorPin2 LOW
	digitalWrite(motorPin2, LOW);   

	//waits
	delay(length); 	
	
	// set the Pin motorPin1 LOW	
	digitalWrite(motorPin1, LOW);    		
}

void rotateRight(int speedOfRotate, int length){
	//rotates motor
	analogWrite(motorPin2, speedOfRotate); 

	// set the Pin motorPin1 LOW
	digitalWrite(motorPin1, LOW);
	
	//waits
	delay(length); 
	
	// set the Pin motorPin2 LOW
	digitalWrite(motorPin2, LOW); 
}