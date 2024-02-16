#include <Servo.h> 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Servo nu;
int angle = 0;
#define LOG_PERIOD 15000     //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000    //Maximum logging period
unsigned long counts;             //variable for GM Tube events
unsigned long cpm;                 //variable for CPM
unsigned int multiplier;             //variable for calculation CPM in this sketch
unsigned long previousMillis;      //variable for time measurement

void tube_impulse(){               //procedure for capturing events from Geiger Kit
  counts++;
}


void setup() {
   counts = 0;

  cpm = 0;

  multiplier = MAX_PERIOD / LOG_PERIOD; 
  Serial.begin(9600);
  nu.attach(9); 


   radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("on");

  pinMode(2, INPUT);                                   // set pin INT0 input for capturing GM Tube events

  digitalWrite(2, LOW);                                 // turn on internal pullup resistors, solder C-INT on the PCB

  attachInterrupt(0, tube_impulse, FALLING);  //define external interrupts
}
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > LOG_PERIOD){

    previousMillis = currentMillis;

    cpm = counts * multiplier;

        Serial.print(cpm);                              // send cpm data to Radiation Logger

        Serial.write(' ');                                // send null character to separate next data

    
int a=cpm;

char b[3];

String str;

str=String(a);

str.toCharArray(b,3);
Serial.print(str);
 

radio.write(&cpm, sizeof(cpm));
    counts = 0;
  }
  }
