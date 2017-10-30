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
   // case 0: u8g_boot(); break;
    case 1: u8g_main(); break;
    case 2: u8g_wifi(); break;
    // case 2: u8g_time(); break;
    // case 3: u8g_heart(); break;
    // case 4: u8g_temperature(); break;
    // case 5: u8g_battery(); break;
    // case 6: u8g_lowpower(); break;
    // case 7: u8g_shutdown(); break;
  }
}

void u8g_main(){
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



void retrieve_api(){
	WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");return;
  }
	
  client.print(String("GET ") + path_ip + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
	
  while(client.available()){
    String output;
    String line, input = client.readStringUntil('\r');

    const int n = 14;
    String api[n];
    
    int c = 0;  
    int li = 0;
    
      for (int i = 0; i < input.length(); i++) {
        if (input.substring(i, i+1) == ",") {
          api[c] = input.substring(li, i);
          li = i + 1;
          c++;
        }
        if (i == input.length() - 1) {
          api[c] = input.substring(li, i);
        }
      }
		
      input = "";
      c, li = 0;
		return api; //7,8 index is latlon, 13 is ip, 5 is location (town/city)
  }
}

void u8g_wifi(){
  u8g.setFont(u8g_font_9x15);
  u8g_prepare();
  u8g.drawStr( 10, 10, "WiFi");
	String api = retrieve_api();
	String localIP = WiFi.localIP().
	u8g.drawStr( 20, 20, localIP);
	
}

// void u8g_boot(){
//   u8g_prepare();
//   u8g.drawStr( 10, 10, "Boot");
//   u8g.drawBox(14,40,x*2,10);
// }

void loop () {
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



