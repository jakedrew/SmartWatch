#include <Wire.h>
#include "RTClib.h"
#include "U8glib.h"


RTC_DS1307 RTC;
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
#define Addr 0x48
String data;
unsigned int dataT[2];
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int a, s, x = 0;

void setup()
{
    Serial.begin(9600);

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

   uDraw();
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
  switch(s) {
    case 0: uBoot(); break;
    case 1: uMain(); break;
    //case 2: uBLE(); break;
    case 2: uTemp(); break;
    //case 3: uGyro(); break;
  }
}

void uBoot(){
  uPrepare();
}

void uMain(){
  uPrepare();
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
//   u8g.drawStr( 10, 10, "BLE");
// }

void uTemp(){
  uPrepare();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 byte of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // temp msb, temp lsb
  if (Wire.available() == 2)
  {
    dataT[0] = Wire.read();
    dataT[1] = Wire.read();
  }

  // Convert the data to 12 bits
  int temp = ((dataT[0] * 256) + dataT[1]) / 16;
  if(temp > 2047)
  {
  	temp -= 4096;
  }
  float cTemp = temp * 0.0625;
  String csTemp =  String(cTemp, 3);
  String STemp =  String(csTemp + "*C");
  u8g.drawStr( 10, 10,STemp.c_str());
}
