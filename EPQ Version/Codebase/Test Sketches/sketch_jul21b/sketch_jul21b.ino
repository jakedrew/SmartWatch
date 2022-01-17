#include <Time.h>
void setup()
{
 Serial.begin(9600);
 Serial.println("waiting for sync");
}

void loop()
{
  time_t t = now(); // Store the current time in time 
 // variable t 
 hour(t); // Returns the hour for the given
 // time t
 minute(t); // Returns the minute for the given
 // time t
 second(t); // Returns the second for the given
 // time t 
 day(t); // The day for the given time t

 weekday(t); // Day of the week for the given
 // time t 
 month(t); // The month for the given time t

 year(t); // The year for the given time t

 Serial.println(hour(t));
}

