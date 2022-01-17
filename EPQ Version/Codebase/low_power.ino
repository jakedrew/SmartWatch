
#define LED 4
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  attachInterrupt(0, interrupt, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

  
  //disable adc
  ADCSRA &= ~(1<<7);
  //Sleep
  SMCR |= (1<<2); //pw dw md
  SMCR |= 1; // enable sleep
  //bod disable
  MCUCR |= (3<<5);
  MCUCR = (MCUCR & ~(1<<5)) | (1 << 6);
  __asm__ __volatile__("sleep");
}
void interrupt(){
  
}

