/*
 GKScroll Example - Hello, World!
 
 This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
 To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/deed.en_US.
 
 Demonstrates the use of the GKScroll library with a 16x2 LCD display.  
 This example requires the LiquidCrystal library and the GKScroll library.
  
 This sketch prints the fixed line "Hello World!" to the top line of the LCD
 and scrolls "Hello World!" on the bottom line of the LCD.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally created 23 February 2012
 by Garrett Kendrick

 http://www.garrettkendrick.com
 
 */

// include the LiquidCrystal library:
#include <LiquidCrystal.h>
// include the library code:
#include <GKScroll.h>

int scrollBuffer = 5; //number of spaces to leave between end of the line and the start of the next
int lcdColumns = 16; //number of characters per line
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(ScrollLine("Hello World!", scrollBuffer, lcdColumns));
  delay(300); //adjust this delay to achieve the speed desired
}

