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

int CPM = 0;
int avg=0;
int count=1;
int ss= 0;
//battery reading
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
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
 radio.startListening();
  Serial.println("on");
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
 
}


void loop(){
  if(radio.available()){
Serial.println("read");
 char text[32] = "";
    radio.read(&text, sizeof(text));
    tft.setRotation(1);
tft.setCursor(0,ss);
  tft.setTextColor(WHITE);    
  tft.setTextSize(3);
    tft.print(text);
    CPM = atoi(text);
    if(sizeof(text)>2){
    Serial.println(CPM);
    avg=(avg+CPM)/count;
    count++;
  
  
     
  tft.print("CPM=");
  tft.print(CPM);
  tft.print(" ");
   tft.print("Avg CPM=");
  tft.println(avg);
  delay(100);
  
    ss=ss+22;
    x++;
   }
  
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
