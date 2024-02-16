#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include "PinChangeInterrupt.h"

#define LOG_PERIOD 15000     //Logging period in milliseconds, recommended value 15000-60000.

#define MAX_PERIOD 60000    //Maximum logging period

unsigned long counts;             //variable for GM Tube events

unsigned long cpm;                 //variable for CPM

unsigned int multiplier;             //variable for calculation CPM in this sketch

unsigned long previousMillis;      //variable for time measurement
unsigned int avg;
unsigned int ss;
 unsigned int c;
 unsigned int x;
#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
extern uint8_t cry[];
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define CR  0x05E2
#define P  0xF00F
#define WHITE 0xFFFF
#define BLACK 0x0000

// The display set up
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void tube_impulse(){               //procedure for capturing events from Geiger Kit

  counts++;
  Serial.print('t');

}


void attachInterrupts() {
//    attachInterrupt(digitalPinToInterrupt(PIN_SENSE_1), isrFan1, RISING);
    attachPCINT(digitalPinToPCINT(50), tube_impulse, FALLING);


}




void setup(){                                               //setup procedure
avg = 0;
ss=0;
  counts = 0;
c=1;
  cpm = 0;
  x=0;

  multiplier = MAX_PERIOD / LOG_PERIOD;      //calculating multiplier, depend on your log period

  Serial.begin(9600);                                    // start serial monitor
 tft.begin();
   if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");

  //radio start code
   

  
  //start loading screen
  tft.fillScreen(ILI9341_BLACK);
   tft.setRotation(1);
   drawBitmap(35,0,cry,252,240,ILI9341_GREEN);
  
   tft.setRotation(1);
tft.setCursor(60,170);
  tft.setTextColor(WHITE);    
  tft.setTextSize(5);
  
 tft.print("W");
delay(100);
 tft.print("E");
delay(100);
 tft.print("L");
delay(100);
 tft.print("C");
delay(100);
 tft.print("O");
delay(100);
 tft.print("M");
delay(100);
 tft.print("E");
delay(1000);
tft.fillScreen(ILI9341_BLACK);
                                  
  pinMode(50, INPUT);                                   // set pin INT0 input for capturing GM Tube events

  //digitalWrite(20, LOW);                                 // turn on internal pullup resistors, solder C-INT on the PCB

  attachInterrupts();  //define external interrupts

}

 

void loop(){                                               //main cycle

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > LOG_PERIOD){

    previousMillis = currentMillis;

    cpm = counts * multiplier;

        Serial.print(cpm);                              // send cpm data to Radiation Logger

        Serial.write(' ');                                // send null character to separate next data

    counts = 0;
tft.setRotation(1);
tft.setCursor(0,ss);
  tft.setTextColor(WHITE);    
  tft.setTextSize(3);
    
    if(cpm>0){
    
   
    avg=(avg+cpm);
    
  
  
     
  tft.print("CPM=");
  tft.print(cpm);
  tft.print(" ");
   tft.print("Avg CPM=");
  tft.println(avg/c);
  delay(100);
  
    ss=ss+22;
    x++;
    c++;}
   
  
  }
if(x>10){
tft.fillScreen(ILI9341_BLACK);
  ss=0;  
  x=0;
}}
void drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}
  
