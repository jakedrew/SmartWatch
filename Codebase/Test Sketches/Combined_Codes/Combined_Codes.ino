// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>

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





const int MPU_addr=0x68;  // I2C address of the MPU-6050
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.display();

  pinMode(2, INPUT);
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 

  pinMode(5, OUTPUT); 

  delay(1600);
  
 display.clearDisplay();
 delay(400);
}
int minutes = 00;
int hours = 00;
int mil = millis();
int disState = 0;
int tstate = 0;
int cstate = 1;
unsigned long lbt = millis()-100; 


void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Tmp = Tmp/340.00+36.53;
  Tmp = Tmp*10;
  Tmp = round(Tmp*10)/10;
  Tmp = Tmp/10;
  Serial.print(" | Tmp = "); Serial.print(Tmp);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);
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
    display.setCursor(80,40);
    display.println(String(Tmp)+ "℃");
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
    delay(0);
    
    display.display();
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
