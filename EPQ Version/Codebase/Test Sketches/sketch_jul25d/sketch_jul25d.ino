#include <Button.h>


#include <LowPower.h>



// Add libraries
  #include "U8glib.h"
  #include <SPI.h>
  #include <Wire.h>
  #include "RTClib.h"
  
#include <EEPROM.h>
// setup u8g object
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Button btnFour = Button(4, true, false, 250);  //100 ms debounce
Button btnFive = Button(5, true, false, 100);  //100 ms debounce

// Setup RTC
  RTC_DS1307 RTC;
  char monthString[37]= {"JanFebMarAprMayJunJulAugSepOctNovDec"};
  int  monthIndex[122] ={0,3,6,9,12,15,18,21,24,27,30,33};
  String thisMonth = "";
  String thisTime = "";
  String thisDay="";
  
int btnPressed;
int screen;
void setup(void) {
  Serial.begin(9600);
  screen = 0;
  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);
  Wire.begin();
  RTC.begin();
  btnPressed = millis(); 
  //pinMode(5, INPUT);
  
  //pinMode(4, INPUT);
  
//  pinMode(5, INPUT);
//  
//  pinMode(5, INPUT);
 
 // attachInterrupt(digitalPinToInterrupt(4), invertSleep, FALLING);

  //EEPROM.write(11, -2);

}



void draw(void) {
  u8g_prepare();
  switch(screen) {
    case 0: u8g_main(); break;
    case 1: u8g_menu(); break;
//    case 2: u8g_r_frame(draw_state&7); break;
//    case 3: u8g_string(draw_state&7); break;
//    case 4: u8g_line(draw_state&7); break;
//    case 5: u8g_triangle(draw_state&7); break;
//    case 6: u8g_ascii_1(); break;
//    case 7: u8g_ascii_2(); break;
//    case 8: u8g_extra_page(draw_state&7); break;
  }
    
  
}
DateTime now, future;
int timeshift;
int charge = 0;
int timechanged = 0;

void u8g_main() {

  u8g.setScale2x2();
  //**** RTC **********
  now = RTC.now();
//  if(timechanged == 1){
//    DateTime current = RTC.now();
//    if(EEPROM.read(11) == 0){
//      now = current;
//    }else{
//      if(EEPROM.read(11) < 0){
//        int hrShiftN = EEPROM.read(11) * -1;
//        DateTime future (now.unixtime() - (hrShiftN*3600));   
//        now = future;
//      }else{
//        int hrShiftP = EEPROM.read(11);
//        DateTime future (now.unixtime() + (hrShiftP*3600));
//        now = future;
//      }
//    }
//    timechanged = 0;
//  }else{
//    DateTime current = RTC.now();
//    if(EEPROM.read(11) == 0){
//      now = current;
//    }else{
//        now = future;
//      
//    }
//  }
//  // display date at bottom of screen
//  thisDay = String(now.day(), DEC) + "/"; 
//  thisMonth="";
//  for (int i=0; i<=2; i++){
//    thisMonth += monthString[monthIndex[now.month()-1]+i];
//  }  
//  thisDay=thisDay + thisMonth + "/"; 
//  thisDay=thisDay + String(now.year() , DEC);
//  const char* newDay = (const char*) thisDay.c_str(); 
//  u8g.drawStr(32,63, newDay);   
  // ********************* 
  // display time in digital format
  thisTime="";
  if (now.hour() < 10){ thisTime=thisTime + "0";} 
  thisTime=String(now.hour()) + ":";
  if (now.minute() < 10){ thisTime=thisTime + "0";} // add leading zero if required
  thisTime=thisTime + String(now.minute());
  //if (now.second() < 10){ thisTime=thisTime + "0";} // add leading zero if required
 // thisTime=thisTime + String(now.second());
  const char* newTime = (const char*) thisTime.c_str();
  u8g.drawStr(15,7, newTime); 
   //(x,y)
  u8g.undoScale();
  String secondsT = "";
  if (now.second() < 10){ secondsT="0"+secondsT;}
  secondsT =String(now.second());
  const char* newTimeS = (const char*) secondsT.c_str();
  u8g.drawStr(102,26,newTimeS);
  //u8g.drawStr(9,20, times.c_str()); 
  
    //u8g.undoScale();


  //draw the date
  //set date font
  
  u8g.setFont(u8g_font_profont10);
  thisDay = String(now.day(), DEC) + "/"; 
  thisMonth="";
  for (int i=0; i<=2; i++){
    thisMonth += monthString[monthIndex[now.month()-1]+i];
  }  
  thisDay=thisDay + thisMonth + "/"; 
  thisDay=thisDay + String(now.year() , DEC);
  const char* newDay = (const char*) thisDay.c_str(); 
  u8g.drawStr(38,55, newDay);   

  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  //u8g.drawRFrame(5, 10,40,30, a+1);
  //u8g.drawRBox(7, 49,16,8, 1);
  charge = 76;
  if(charge < 30){
    u8g.drawRBox(7, 49,4,8, 1);
  }else if(charge < 50){
    u8g.drawRBox(7, 49,8,8, 1);
  }else if(charge < 70){
    u8g.drawRBox(7, 49,12,8, 1);
  }else{
    u8g.drawRBox(7, 49,16,8, 1);
  }
  u8g.drawRFrame(7, 49,16,8, 1);
}

void u8g_prepare(void) {
  //u8g.setFont(u8g_font_6x10);
  
  u8g.setFont(u8g_font_profont15);
 // u8g.setFont(u8g_font_helvB14);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}


void u8g_menu(){
  //draw time at top of display
  
  now = RTC.now();
  thisTime="";
  if (now.hour() < 10){ thisTime=thisTime + "0";} 
  thisTime=String(now.hour()) + ":";
  if (now.minute() < 10){ thisTime=thisTime + "0";} // add leading zero if required
  thisTime=thisTime + String(now.minute());
  //if (now.second() < 10){ thisTime=thisTime + "0";} // add leading zero if required
 // thisTime=thisTime + String(now.second());
  const char* newTime = (const char*) thisTime.c_str();
  
  u8g.setFont(u8g_font_04b_03);
  u8g.drawStr(56,6, newTime); 

  //end draw
  
  //startmenudraw
  
  u8g.setFont(u8g_font_profont12);
  String menuItems[] = {"Home", "Temperature", "Accelerommeter", "Gyro", "Battery", "Info", "Settings"};

  for (int i = 0; i < 6; i++) {

      const char* menuItem = (const char*) menuItems[i].c_str();
      
      u8g.drawStr(20,(10+(i+1)*11), menuItem); 
//      if(selection >= 1){
//        display.drawCircle(12,(13+((selection-4)*10)),2,WHITE);
//      }
    }
  //end menu draw
  
  
}
void clearOLED(){
    u8g.firstPage();  
    do {
    } while( u8g.nextPage() );
}
int sleepmode = 0;
int enter;

void invertSleep(){
  if(sleepmode == 1){
    sleepmode = 0;
  }else{
    sleepmode =1;
  }
}

int btnFourPressed = millis(); 
int btnFivePressed = millis(); 

void loop(void) {
  // picture loop
  
  
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  btnFour.read();
  if ( btnFour.isPressed() ) {
     if(millis() - btnFourPressed >= 1000){
      Serial.println("pressed");
      btnFourPressed = millis();
     }
  }
  if ( btnFour.pressedFor(10000) ) { 
    Serial.println("PRESSED for 10000ms");
    
  }
  // rebuild the picture after some delay
//  delay(50);
}
