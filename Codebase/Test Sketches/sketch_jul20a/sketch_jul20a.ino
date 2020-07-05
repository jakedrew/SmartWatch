#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define SSD1306_128_64 1
#define SSD1306_LCDHEIGHT 64
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define ThmPin =  A0;     //The analog pin of the thermistor





void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.display();

  pinMode(2, INPUT);
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 

  pinMode(5, OUTPUT); 

}
int minutes = 00;
int hours = 00;
int mil = millis();
int disState = 0;
int tstate = 0;
int cstate = 1;
unsigned long lbt = millis()-100; 

void loop() {

  if(millis() > (lbt+100)){
    if (digitalRead(3) == HIGH) { 
       Serial.println("BtnSp: Pressed"); 
        if(disState == 0){
          if(tstate == 1){
            disState = 1;
          }else{
            tstate = 1;
          }
        }
        if(disState == 1){
          if(cstate == 0){
            cstate = 1;
          }else{
            cstate = 0;
          }
        }
    }else if (digitalRead(4) == HIGH) { 
       Serial.println("BtnDn: Pressed"); 
       if(disState == 1){
        if(cstate == 0){
         hours = hours - 1;
          if(hours == -1){
            hours = 23;
          }
        }
        if(cstate == 1){
          minutes = minutes - 1;
          if(minutes == -1){
            minutes = 59;
          }
        }
       }
    }else if (digitalRead(2) == HIGH) { 
       Serial.println("BtnUp: Pressed");
       if(disState == 1){
        if(cstate == 0){
         hours = hours + 1;
          if(hours == 24){
            hours = 0;
          }
        }
        if(cstate == 1){
          minutes = minutes + 1;
          if(minutes == 60){
            minutes = 0;
          }
        }
       }
    }
    lbt = millis();
  }

  
//  for (int i=0; i< 30; i++) {
//    
//    Serial.println(millis());
//    if (i == 30){
//      minutes = minutes + 1;
//       
//    }
//  }
  displaym();
   
}
int taway = 0;
void displaym(){
  if(disState == 0){
    display.drawRect(0,0,16,8,1);
    int i = round(millis()/1000)-(taway*60);
    String fstr = String(i);
    String hstr = String(hours);
    if(i>59){
      taway = taway+1;
    }
    int j = round(millis()/60000);
    String jstr = String(minutes);
    if(j<10){
      jstr = "0"+jstr;
    }
    if(hours<10){
      hstr = "0"+hstr;
    }
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(19,14);
    if ( (i % 2) == 0) { 
      display.println( hstr + " " + jstr);
    }else{
      display.println(hstr + ":" + jstr);
    }
    display.setTextSize(1);
    display.setCursor(110,0);
    display.println(fstr+ "s");
    charge(i);
    if(tstate == 1){
      if(disState == 0){
            display.setTextColor(WHITE);
            display.setTextSize(1);
            display.setCursor(20,50);
            display.println("Change Time?");
         }
    }
    display.display();
    delay(0);
    display.clearDisplay();
  }
  if(disState == 1){
    display.drawRect(0,0,16,8,1);
    int i = round(millis()/1000)-(taway*60);
    String fstr = String(i);
    String hstr = String(hours);
    if(i>59){
      taway = taway+1;
    }
    int j = round(millis()/60000);
    String jstr = String(j);
    if(j<10){
      jstr = "0"+jstr;
    }
    if(hours<10){
      hstr = "0"+hstr;
    }
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(19,14);
    if ( (i % 2) == 0) { 
      display.println(hstr + " " + jstr);
    }else{
      display.println(hstr + ":" + jstr);
    }
    if(cstate == 0){
      display.drawRect(20,42,34,2,1);
    }else if (cstate == 1){
      display.drawRect(70,42,34,2,1);
    }
    display.setTextSize(1);
    display.setCursor(110,0);
    display.println(fstr+ "s");
    charge(i);
    if(tstate == 1){
      if(disState == 0){
            display.setTextColor(WHITE);
            display.setTextSize(1);
            display.setCursor(20,50);
            display.println("Change Time?");
         }
    }
    display.display();
    delay(0);
    display.clearDisplay();
  }
  
  
}

void charge(int c){
  if (c<25){
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("Low Power");
  }
  else if (c<45){
    display.fillRect(0,0,4,8,1);
  }
  else if (c<70){
    display.fillRect(0,0,8,8,1);
  }
  else if (c<95){
    display.fillRect(0,0,12,8,1);
  }
  else{
    display.fillRect(0,0,16,8,1);
  }
  
}
