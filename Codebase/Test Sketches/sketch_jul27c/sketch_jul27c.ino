* 
Digital Winding Clock - Arduino Clock for beginners   
No RTC, 
Just set it to exact time using the push buttons each time you switch on the clock 
Made by Techno (sǝɹoɟ ǝǝןuuɐ) 
Feel free to modify 
*/ 
#include <LiquidCrystal.h> 
LiquidCrystal 
lcd(12,11,5,4,3,2); 
int h=12; 
int m; 
int s; 
int flag; 
int TIME; 
const int hs=8; 
const int ms=9; 
int state1; 
int state2; 
void setup() 
{ 
 lcd.begin(16,2); 
} 
void loop() 
{ 
lcd.setCursor(0,0); 
s=s+1; 
lcd.print("TIME:"); 
lcd.print(h); 
lcd.print(":"); 
lcd.print(m); 
lcd.print(":"); 
lcd.print(s); 
if(flag<12)lcd.print("AM"); 
if(flag==12)lcd.print("PM"); 
if(flag>12)lcd.print("PM"); 
if(flag==24)flag=0; 
delay(1000); 
lcd.clear(); 
if(s==60){ 
 s=0; 
 m=m+1; 
} 
if(m==60) 
{ 
 m=0; 
 h=h+1; 
 flag=flag+1; 
} 
if(h==13) 
{ 
 h=1; 
} 
lcd.setCursor(0,1); 
lcd.print("HAVE A NICE DAY"); 
//-------Time 
// setting-------// 
state1=digitalRead(hs); 
if(state1==1) 
{ 
 h=h+1; 
 flag=flag+1; 
 if(flag<12)lcd.print("AM"); 
 if(flag==12)lcd.print("PM"); 
 if(flag>12)lcd.print("PM"); 
 if(flag==24)flag=0; 
 if(h==13)h=1; 
} 
state2=digitalRead(ms); 
if(state2==1){ 
 s=0; 
 m=m+1; 
} 
} 
