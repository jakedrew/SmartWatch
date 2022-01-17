/*
  GKScroll.cpp - Library for scrolling long lines of text on an LCD screen..
  Created by Garrett Kendrick, February 23, 2012.

  This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
  To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/deed.en_US.
*/



#include "Arduino.h"
#include "GKScroll.h"

int lineOneStep, lineTwoStep = 0;



String ScrollLine(String lineToScrollLeft, int scrollBuffer, int lcdColumns){
  
int  stringLength = lineToScrollLeft.length();
 if(lineOneStep > lineToScrollLeft.length() + scrollBuffer){
   lineOneStep = 0;
 }
 int stringEndPosition = lineOneStep + lcdColumns;
 if (stringEndPosition > (lineToScrollLeft.length())){
  int difference = stringEndPosition - lineToScrollLeft.length();
  
   for(int i=0; i < scrollBuffer; i++){
 lineToScrollLeft = lineToScrollLeft + " ";
  }
  for(int i=0; i < (difference - scrollBuffer); i++){
    int iplus1 = i + 1;
  String tempString = lineToScrollLeft.substring(i,iplus1);  
  lineToScrollLeft = lineToScrollLeft + tempString ;  
  }
  
 }
 String str = lineToScrollLeft.substring(lineOneStep,stringEndPosition);
 lineOneStep++;
 return str;
   
}

