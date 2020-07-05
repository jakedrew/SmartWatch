  #include "U8glib.h"
  #include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <TimeLib.h>
  #include <SPI.h>
  
// setup u8g object
  U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C 
//

const int MPU_addr = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
// Setup RTC
tmElements_t tm;

void setup () {
    Serial.begin(9600);
    Wire.begin();
}
  void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(50);
}

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  // display date at bottom of screen
 String times = String(tm.Hour) + ":" +String(tm.Minute)+":" +String(tm.Second);   
  u8g.drawStr(10,20, times.c_str()); 
  
  String times2 = String(tm.Day) + "/" +String(tm.Month)+"/" +String(tm.Year);   
  u8g.drawStr(10,40, times2.c_str()); 

}

