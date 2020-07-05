#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define SSD1306_128_64 1
#define SSD1306_LCDHEIGHT 64
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


const int lBtn =  13;
const int cBtn =  12;
const int rBtn =  11;

uint32_t timer; //it's a timer, saved as a big-ass unsigned int.  We use it to save times from the "micros()" command and subtract the present time in microseconds from the time stored in timer to calculate the time for each loop.
double compAngleX, compAngleY; //These are the angles in the complementary filter
#define degconvert 57.2957786


const int MPU_addr = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void bootScreen() {
  setText(3, WHITE, 50, 20);
  display.println("D1");
  display.display();
}

void setText(int sz, float clr, int cw, int ch) {
  display.setTextSize(sz);
  display.setTextColor(clr);
  display.setCursor(cw, ch);
}
int screen = 0;
int twoctrl =0;
int selection = 1;
int lastpress = 0;
int isselecting = 0;
void ctrlBtn() {  
 
  if((millis() - lastpress) > 300){
  
    if(screen == 0){
      screen = 1;
    }else if(screen = 1){
    
      if(twoctrl == 1){
        if(selection == 1){
          screen = 0;
        }else if(selection == 1){
          screen = 2;
        }else if(selection == 2){
          screen = 3;
        }else if(selection == 3){
          screen = 4;
        }else if(selection == 4){
          screen = 5;
        }else if(selection == 5){
          screen = 6;
        }
        twoctrl = 0;
      }else{
        twoctrl = 1;
      }
    }else if(screen == 2){
      screen = 1;
    }else if(screen == 3){
      screen = 1;
    }else if(screen == 4){
      screen = 1;
    }else if(screen == 5){
      screen = 1;
    }else if(screen == 6){
      screen = 1;
    }
  }
  lastpress = millis();
}

void incrementSelection(){
  if((millis() - lastpress) > 200){
    selection = selection + 1;
    if(selection == 7){
       selection = 1;
     }
  }
  lastpress = millis();
}
void decrementSelection(){
  if((millis() - lastpress) > 200){
    selection = selection -1;
    if(selection == 0){
       selection = 6;
     }
  }
  lastpress = millis();
}

void menuDisplay() {
  isselecting = 1;
  display.clearDisplay();
  screen = 1;
 
  display.drawRect(0, 0, 16, 8, 1);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(44, 1);
  display.println("Menu");

  String menuItems[] = {"Home", "Temperature", "Accelerommeter", "Gyro", "Info", "Settings"};
  String menuItemsSecondPage[] = {"Info", "Settings"};
  display.setTextSize(1);
  display.setTextColor(WHITE);

  if(selection > 4){
    for (int i = 0; i < 2; i++) {
      
      display.setCursor(20, (10+((i+1)*10)));
      display.println(menuItemsSecondPage[i]);
      
      if(selection >= 1){
        display.drawCircle(12,(13+((selection-4)*10)),2,WHITE);
      }
    }
      
  }else{
  
    for (int i = 0; i < 6; i++) {
      
      display.setCursor(20, (10+((i+1)*10)));
      display.println(menuItems[i]);
      
      if(selection >= 1){
        display.drawCircle(12,(13+(selection*10)),2,WHITE);
      }
    }
  }

  display.display();



}
void gyroDisplay(){
  screen = 0;
}
void infoDisplay(){
  screen = 0;
}
void setDisplay(){
  screen = 0;
}
 

void tempDisplay() {
  
  display.clearDisplay();
  display.drawRect(0, 0, 16, 8, 1);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(34, 1);
  display.println("Temperature");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 23);
  String TmpS = String(Tmp);
  String TmpFS = String((Tmp * 9 / 5) + 32);
  String TmpKS = String(round(Tmp + 273.15));
  display.println(TmpS + "C | " + TmpFS + "F | " + TmpKS + "K");

  display.display();
  delay(0);
  display.clearDisplay();

}

void accDisplay() {
   display.clearDisplay();

  display.drawRect(0, 0, 16, 8, 1);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(34, 1);
  display.println("");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 23);
  String AcXs = String(AcX);
  String AcYs = String(AcY);
  String AcZs = String(AcX);
  String Tmps = String(Tmp);
  String GyXs = String(GyX);
  String GyYs = String(GyY);
  String GyZs = String(GyZ);
  display.println(AcXs + "|" + AcYs + "|" + AcZs + "|" + Tmps + "|" + GyXs + "|" + GyYs + "|" + GyZs);
  display.display();
  delay(1600);
  display.clearDisplay();




}
int lState, cState, rState = 0;
int lowPowerMode = 0;

void setup()   {

  // Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  bootScreen();


  pinMode(9, INPUT);
  pinMode(10, INPUT);

  // attachInterrupt(digitalPinToInterrupt(2), homeBtn, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ctrlBtn, CHANGE);

  delay(1200);
  display.clearDisplay();
  delay(400);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);


  timeSet(EEPROM.read(0), EEPROM.read(1));
}
int minutes = 00;
int hours = 00;
int mil = millis();
int disState = 0;
int tstate = 0;
int cstate = 1;
unsigned long lbt = millis() - 100;
String input = "";
void timeSet(int h, int m) {
  hours = h;
  minutes = m;
  EEPROM.write(0, hours);
  EEPROM.write(1, minutes);
}

void requestAcc(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void loop() {

  //  if (Serial.available() > 0) {
  //      input = Serial.readString();
  //      if (input.substring(0,4) == "time") {
  ////        Serial.println("got time");
  ////        Serial.println(input.substring(5,7 ));
  ////        Serial.println(input.substring(8,10 ));
  //        hours = input.substring(5,7 ).toInt();
  //        minutes = input.substring(8,10 ).toInt();
  //        EEPROM.write(0, hours);
  //        EEPROM.write(1, minutes);
  //     }
  //  }
 
  if(screen == 0){
    displaym();
   
  }else if(screen == 1){
     menuDisplay();
     charge();
     if(digitalRead(9) == HIGH){
      incrementSelection();
     }else if(digitalRead(10) == HIGH){
      decrementSelection();
     }
  }else if(screen == 2){
     tempDisplay();
     
  }else if(screen == 3){
     accDisplay();
     
  }else if(screen == 4){
     gyroDisplay();
     
  }else if(screen == 5){
     infoDisplay();
     
  }else if(screen == 6){
     setDisplay();
     
  }


  
  
  
  
  requestAcc();
  //accDisplay();
  Tmp = Tmp / 340.00 + 36.53;
  Tmp = Tmp * 10;
  Tmp = round(Tmp * 10) / 10;
  Tmp = Tmp / 10;
  //  tempDisplay(Tmp);




  double roll = atan2(AcY, AcZ) * degconvert;
  double pitch = atan2(-AcX, AcZ) * degconvert;

  //3) set the starting angle to this pitch and roll
  double gyroXangle = roll;
  double gyroYangle = pitch;
  double compAngleX = roll;
  double compAngleY = pitch;

  //start a timer
  timer = micros();


  double dt = (double)(micros() - timer) / 1000000; //This line does three things: 1) stops the timer, 2)converts the timer's output to seconds from microseconds, 3)casts the value as a double saved to "dt".
  timer = micros(); //start the timer again so that we can calculate the next dt.


  double gyroXrate = GyX / 131.0;
  double gyroYrate = GyY / 131.0;
  compAngleX = 0.99 * (compAngleX + gyroXrate * dt) + 0.01 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.99 * (compAngleY + gyroYrate * dt) + 0.01 * pitch;
  if (-compAngleX > 160) {
    lowPowerMode = 1;
    //Serial.print("LowPowerMode = 1");
  }
  if (-compAngleY > 160) {
    lowPowerMode = 1;
    //Serial.print("LowPowerMode = 1");
  }
  //  Serial.print(compAngleX);Serial.print("\t");
  //  Serial.print(compAngleY);Serial.print("\n");


  //  if(millis() > (lbt+100)){
  //    if (digitalRead(3) == HIGH) {
  //       Serial.println("BtnSp: Pressed");
  //        if(disState == 0){
  //          if(tstate == 1){
  //            disState = 1;
  //          }else{
  //            tstate = 1;
  //          }
  //        }
  //        if(disState == 1){
  //          if(cstate == 0){
  //            cstate = 1;
  //          }else{
  //            cstate = 0;
  //          }
  //        }
  //    }else if (digitalRead(4) == HIGH) {
  //       Serial.println("BtnDn: Pressed");
  //       if(disState == 1){
  //        if(cstate == 0){
  //         hours = hours - 1;
  //          if(hours == -1){
  //            hours = 23;
  //          }
  //        }
  //        if(cstate == 1){
  //          minutes = minutes - 1;
  //          if(minutes == -1){
  //            minutes = 59;
  //          }
  //        }.
  //       }
  //    }else if (digitalRead(2) == HIGH) {
  //       Serial.println("BtnUp: Pressed");
  //       if(disState == 1){
  //        if(cstate == 0){
  //         hours = hours + 1;
  //          if(hours == 24){
  //            hours = 0;
  //          }
  //        }
  //        if(cstate == 1){
  //          minutes = minutes + 1;
  //          if(minutes == 60){
  //            minutes = 0;
  //          }
  //        }
  //       }
  //    }
  //   lbt = millis();
  //}


  //  for (int i=0; i< 30; i++) {
  //
  //    Serial.println(millis());
  //    if (i == 30){
  //      minutes = minutes + 1;
  //
  //    }
  //  }
  //displaym();
  
}
int taway = 0;
void displaym() {
  if (disState == 0) {
    display.drawRect(0, 0, 16, 8, 1);
    int i = round(millis() / 1000) - (taway * 60);
    String fstr = String(i);
    String hstr = String(hours);
    if (i > 59) {
      taway = taway + 1;
    }
    int j = round(millis() / 60000);
    String jstr = String(minutes);
    if (j < 10) {
      jstr = "0" + jstr;
    } else {
      jstr = jstr;
    }
    if (hours < 10) {
      hstr = "0" + hstr;
    }
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(19, 14);
    if ( (i % 2) == 0) {
      display.println( hstr + " " + jstr);
    } else {
      display.println(hstr + ":" + jstr);
    }
    display.setTextSize(1);
    display.setCursor(110, 0);
    display.println(fstr + "s");
    //charge(i);
    if (tstate == 1) {
      if (disState == 0) {
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(20, 50);
        display.println("Change Time?");
      }
    }
    display.display();
    delay(0);
    display.clearDisplay();
  }
  if (disState == 1) {
    display.drawRect(0, 0, 16, 8, 1);
    int i = round(millis() / 1000) - (taway * 60);
    String fstr = String(i);
    String hstr = String(hours);
    if (i > 59) {
      taway = taway + 1;
    }
    int j = round(millis() / 60000);
    String jstr = String(j);
    if (j < 10) {
      jstr = "0" + jstr;
    }
    if (hours < 10) {
      hstr = "0" + hstr;
    }
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(19, 14);
    if ( (i % 2) == 0) {
      display.println(hstr + " " + jstr);
    } else {
      display.println(hstr + ":" + jstr);
    }
    if (cstate == 0) {
      display.drawRect(20, 42, 34, 2, 1);
    } else if (cstate == 1) {
      display.drawRect(70, 42, 34, 2, 1);
    }
    display.setTextSize(1);
    display.setCursor(110, 0);
    display.println(fstr + "s");
    //charge(i);
    if (tstate == 1) {
      if (disState == 0) {
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(20, 50);
        display.println("Change Time?");
      }
    }
    display.display();
    delay(0);
    display.clearDisplay();
  }


}

void charge() {
  int c = analogRead(A0) * (5.0 / 1023.0) / (3.3) * 100;
  if (c < 25) {
    if (screen == 0) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.println("Low Power");
    }
  }
  else if (c < 45) {
    display.fillRect(0, 0, 4, 8, 1);
  }
  else if (c < 70) {
    display.fillRect(0, 0, 8, 8, 1);
  }
  else if (c < 95) {
    display.fillRect(0, 0, 12, 8, 1);
  }
  else {
    display.fillRect(0, 0, 16, 8, 1);
  }

}
