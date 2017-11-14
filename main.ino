#include <Wire.h>
#include "RTClib.h"
#include "U8glib.h"
#include "Adafruit_MCP9808.h"

RTC_DS1307 RTC;
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Adafruit_MCP9808 tSensor = Adafruit_MCP9808();

String data;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int a, s, x = 0;

void setup()
{
    Serial.begin(9600);                                 
    //Sets the baud for serial data transmission    
    
    Wire.begin();
    RTC.begin();
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    DateTime now = RTC.now();

    for(a=0;a<13;) pinMode(a++,OUTPUT);             
    //sets all pins to output
    
    for(a=0;a<13;) digitalWrite(a++, LOW);          
    //sets all pins to low for power reduction
    
    for (a=A0; a<=A5;) digitalWrite(a++, LOW);
    //set all A0 to low
    
    IPS(A0);
    IPS(A1);
    IPS(A2);
}

void loop()
{
   if(Serial.available())      
   {
      data = Serial.readString();  
      Serial.println(data);
   }
   
   draw();
   if(s == 0) s = 1;
}
 
void IPS(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

 
ISR (PCINT0_vect) // D8 to D13
 {    
     
 }
 
ISR (PCINT1_vect) // A0 to A5
 {
    //get values for pins
    //then set all low
    //wakeup if not already
 }  
 
ISR (PCINT2_vect) // D0 to D7
 {
 
 }

void uPrepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}


void uDraw(void) {
  uPrepare();
  switch(screen) {
    case 0: uBoot(); break;
    case 1: uMain(); break;
    case 2: uBLE(); break;
    case 2: uTemp(); break;
    case 3: uGyro(); break;
  }
}

void uBoot(){
  u8g_prepare();
}
    
void uMain(){
  u8g.setFont(u8g_font_9x15);
 
  DateTime now = RTC.now();
  String hour = String(now.hour());
  if(now.hour()<10){
    hour = "0" + hour;
  }
  String min = String(now.minute());
  if(now.minute()<10){
    min = "0" + min;
  }
  String time = String(hour + ":" + min);
  u8g.drawStr( 34, 38, time.c_str());
  u8g.setFont(u8g_font_5x7);
  String day = daysOfTheWeek[now.dayOfTheWeek()];
  String btmstr = String(now.day()) + "/" + String(now.month())+"/" + String(now.year());
  u8g.drawStr( 5, 62, day.c_str());
  u8g.drawStr( 75, 62, btmstr.c_str());
  String secs = String(now.second());
  u8g.drawStr( 95, 38, secs.c_str());
}

// void uBLE(){
//   u8g_prepare();
//   u8g.drawStr( 10, 10, "Boot");
//   u8g.drawBox(14,40,x*2,10);
// }
    
void uTemp(){
  u8g_prepare();
  digitalWrite(D4, HIGH);
  tSensor.begin(0x19);
  tSensor.wake();

  float c = tempsensor.readTempC();
  
  tSensor.shutdown();
  u8g.drawStr( 10, 10,[ c + "*C"]);
  digitalWrite(D4, LOW);
}
    
// void uGyro(){
//   u8g_prepare();
//   u8g.drawStr( 10, 10, "Boot");
//   u8g.drawBox(14,40,x*2,10);
// }



