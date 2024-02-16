#include <Servo.h>             //Servo library
 
Servo nu;        //initialize a servo object for the connected servo  
const int pingPin =7;
const int echoPin = 6;
                
int angle = 0;    
 
void setup() 
{ 
  Serial.begin(9600);
  nu.attach(9);      // attach the signal pin of servo to pin9 of arduino
} 
  long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
void loop() 
{ 
 
   long duration, inches;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   if (inches<2){
   Serial.print(inches);
   Serial.print("in, ");

   



  for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    nu.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 
 
  delay(100);
  
  for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
  {                                
    nu.write(angle);              //command to rotate the servo to the specified angle
    delay(5);   }                 
  }}

   
    
