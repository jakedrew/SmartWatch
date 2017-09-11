 //Libraries
#include <Wire.h>
#include "RTClib.h"
#include "U8glib.h"

//Define Globals
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
RTC_DS1307 RTC;
int screen = 0;
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI 
int x = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  DateTime now = RTC.now();
  DateTime future (now + TimeSpan(0,1,0,0));
  RTC.adjust(future);
}

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}


void draw(void) {
  u8g_prepare();
  switch(screen) {
    case 0: u8g_boot(); break;
    case 1: u8g_main(); break;
    // case 2: u8g_time(); break;
    // case 3: u8g_heart(); break;
    // case 4: u8g_temperature(); break;
    // case 5: u8g_battery(); break;
    // case 6: u8g_lowpower(); break;
    // case 7: u8g_shutdown(); break;
  }
}

void u8g_main(){
  
  u8g.setFont(u8g_font_fur17);
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

void u8g_boot(){
  u8g_prepare();
  u8g.drawStr( 10, 10, "Boot");
  u8g.drawBox(14,40,x*2,10);
}

void loop () {
    // DateTime now = RTC.now(); 
    // Serial.print(now.year(), DEC);
    // Serial.print('/');
    // Serial.print(now.month(), DEC);
    // Serial.print('/');
    // Serial.print(now.day(), DEC);
    // Serial.print(' ');
    // Serial.print(now.hour(), DEC);
    // Serial.print(':');
    // Serial.print(now.minute(), DEC);
    // Serial.print(':');
    // Serial.print(now.second(), DEC);
    // Serial.println(); 
    //delay(1000);
   //heart();
      // picture loop  
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
    
    x = x+1;
    if(screen==0){
      if(x > 50){
        screen = 1;
        x=0;
      }
    }
}



