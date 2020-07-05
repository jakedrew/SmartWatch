#include <Time.h>           //http://www.arduino.cc/playground/Code/Time  

void setup(void)
{
   tmElements_t tm;
   time_t t;

   delay(2000);
   Serial.begin(9600);
   
   tm.Hour = 12;             //set the tm structure to 12h34m56s on 01Sep2013
   tm.Minute = 34;
   tm.Second = 56;
   tm.Year = 2013 - 1970;    //tmElements_t.Year is the offset from 1970.
   tm.Month = 9;
   tm.Day = 1;
   
   t = makeTime(tm);
   Serial.print(dayStr(weekday(t)));
   Serial.print(' ');
   printI00(day(t), 0);
   Serial.print(monthShortStr(month(t)));
   Serial.print(year(t));
   Serial.print(' ');
   printI00(hour(t), ':');
   printI00(minute(t), ':');
   printI00(second(t), ' ');
   Serial.print("weekday=");
   Serial.print(weekday(t));    //Sun=1, Mon=2, ... Sat=7
}

void loop(void)
{
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
   if (val < 10) Serial.print('0');
   Serial.print(val);
   if (delim > 0) Serial.print(delim);
   return;
}
