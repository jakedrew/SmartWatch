String data;
int a;

void setup()
{
    Serial.begin(9600);                                 
    //Sets the baud for serial data transmission    
    
    for(a=0;a<13;) pinMode(a++,OUTPUT);             
    //sets all pins to output
    
    for(a=0;a<13;) digitalWrite(a++, LOW);          
    //sets all pins to low for power reduction
    
    for (a=A0; a<=A5;) digitalWrite(a++, LOW);
    //set all A0 to low
    
    IPS(A0);
    IPS(A1);
    IPS(A2);
}

void loop()
{
   if(Serial.available())      
   {
      data = Serial.readString();  
      Serial.println(data);
   }
   
   
}
 
void IPS(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

 
ISR (PCINT0_vect) // D8 to D13
 {    
     
 }
 
ISR (PCINT1_vect) // A0 to A5
 {
    //get values for pins
    //then set all low
    //wakeup if not already
 }  
 
ISR (PCINT2_vect) // D0 to D7
 {
 
 }
