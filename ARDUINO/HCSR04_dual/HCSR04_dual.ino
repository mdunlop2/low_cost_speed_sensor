
// POINT 1
#define echoPin1 6 // Echo Pin
#define trigPin1 9 // Trigger Pin

// POINT 2
#define echoPin2 7 // Echo Pin
#define trigPin2 8 // Trigger Pin
#define LEDPin 13 // Onboard LED


int maximumRange = 98; // Maximum range needed
int minimumRange = 10; // Minimum range needed
long duration, distance;
long leg_distance = 550;
unsigned long TRIGGER_TIME, FINISH_TIME; // Duration used to calculate distance
float runner_speed;
boolean TRIGGERED = false;

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin1, LOW);
 duration = pulseIn(echoPin1, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 digitalWrite(LEDPin, HIGH);
 bool TRIGGERED = false;
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. 
 Serial.println(distance);*/
 digitalWrite(LEDPin, LOW);
 TRIGGERED = !TRIGGERED;
 TRIGGER_TIME = millis();
 delay(43);
 }
 
 while (TRIGGERED == true){
   //POINT2:
   digitalWrite(trigPin2, LOW); 
   delayMicroseconds(2); 
   
   digitalWrite(trigPin2, HIGH);
   delayMicroseconds(10); 
    
   digitalWrite(trigPin2, LOW);
   duration = pulseIn(echoPin2, HIGH);
   
   //Calculate the distance (in cm) based on the speed of sound.
   distance = duration/58.2;
   
   if (distance >= maximumRange || distance <= minimumRange){
   /* Send a negative number to computer and Turn LED ON 
   to indicate "out of range" */
   digitalWrite(LEDPin, HIGH);
   }
   else {
   /* Send the distance to the computer using Serial protocol, and
   turn LED OFF to indicate successful reading. 
   Serial.println(distance); */
   digitalWrite(LEDPin, LOW);
   FINISH_TIME = millis();
   runner_speed = (float)(leg_distance)/(FINISH_TIME - TRIGGER_TIME);
   Serial.println(runner_speed);
   TRIGGERED = !TRIGGERED;
   delay(10000);
   }
 }
 //Delay 50ms before next reading.
 delay(50);
}
