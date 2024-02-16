#include<NewPing.h>
NewPing hei(2, 3, 400);

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
pinMode(3,INPUT);


}

void loop() {
hei.ping_cm();
delay([1000]);
  
  
  

}
