
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

//colors i like
#define CR  0x05E2
#define P  0xF00F
#define WHITE 0xFFFF
#define BLACK 0x0000

//batter reading
byte Vp = A15; //assigns the voltage input pin
int Vr; //value received from the voltPin
float V; //declare the voltage variable

//bitmap crypto image
extern uint8_t cry[];

//random variables might be useful 
int x, y;
int g=0;
boolean be = true;

//radio stuff
RF24 radio(49, 48); // CE, CSN
const byte address[6] = "00001";

// The Shardware setup
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display set up
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup(void) {
 // while (!Serial);     // used for leonardo debugging
 pinMode(Vp, INPUT);
  Serial.begin(9600);
   //radio start code
   tft.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
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

 
}


void loop(){
  //empty text
const char pic[] = "picture";
const char sec5[] = "00000";
const char sec10[] = "10";
 int Vr = analogRead(Vp);
 V = Vr*(5.0/1023.0);
 
 if (! ts.touched()) {
    return;
  }
  TS_Point p= ts.getPoint();
   p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

//this next next allows to touch once before starting main program couldnt find a way to rest touch input    
if(g>0){
 //get point point and set up for confirmation display
 tft.setCursor(0,0);
 tft.fillScreen(ILI9341_BLACK);
p = ts.getPoint();
 p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
 

if(p.x<108){
  //size five for reciever to read
  

  tft.println("5");
  delay(800);
  tft.println("4");
  delay(800);
  tft.println("3");
  delay(800);
  tft.println("2");
  delay(800);
  tft.println("1");
  delay(800);  
  radio.write(&sec5, sizeof(sec5));
   tft.fillScreen(BLACK);
  tft.setCursor(0,0);
  tft.println("SNAP");
   delay(500);
  
}
else if(p.x<216&&p.x>108){

  radio.write(&pic, sizeof(pic));
  
tft.println("SNAP");
delay(500);
//size 7 for reciever

}
else{
//size 2 for reciever

  tft.println("10");
  delay(800);
  tft.println("9");
  delay(800);
  tft.println("8");
  delay(800);
  tft.println("7");
  delay(800);
  tft.println("6");
  delay(800);
  tft.fillScreen(BLACK);
  tft.setCursor(0,0);
tft.println("5");
  delay(800);
  tft.println("4");
  delay(800);
  tft.println("3");
  delay(800);
  tft.println("2");
  delay(800);
  tft.println("1");
  delay(800); 
  radio.write(&sec10, sizeof(sec10));
  tft.println("SNAP");
  delay(500);
tft.setCursor(0,80);

}
}
g++;
dHome();}


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



void dHome(){
  
  tft.fillScreen(ILI9341_BLACK);

  tft.setRotation(1);
  tft.fillRect(0, 160, 260, 80, BLACK);
  
   tft.setRotation(1);
tft.fillRect(280, 0, 80, 240, BLACK);

 tft.setCursor(260,0 );
  tft.setTextColor(WHITE);    
  tft.setTextSize(1);
  tft.println("Voltage");

  tft.setCursor(260,20 );
 tft.print(V,2);
  tft.println(" V");
  
   
    tft.setRotation(1);
  tft.fillRect(0, 80, 260, 80, WHITE);

   tft.setRotation(1);


   tft.setRotation(1);
  tft.fillRect(0, 0, 260, 80, BLACK);
 
   tft.setRotation(1);

    
    tft.setCursor(20,180);
  tft.setTextColor(WHITE);    
  tft.setTextSize(4);
  tft.println("5 SECONDS");
  
tft.setCursor(90,100);
  tft.setTextColor(BLACK);    
  tft.setTextSize(5);
  tft.println("NOW");
    
  tft.setCursor(10,20);
  tft.setTextColor(WHITE);    
  tft.setTextSize(4);
  tft.println("10 SECONDS");
  
  }
