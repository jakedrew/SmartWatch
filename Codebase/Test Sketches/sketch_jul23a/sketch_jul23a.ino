void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

//set values
int leapyrs[] = {100,200,300,500,600}; 
int leapYear(int yr){
  //check if is divisible by 4
  if(yr % 4 == 0){
    if(yr % 100 == 0){
      if(yr % 400 == 0){
        return 29;
      }else {
        return 28;
      }
    }else{
      return 29;
    }
  }else{
    return 28;
  }
}
//jan 1st 2017 was a sunday -- this will be the day I work from
//jan 1st 2018 == monday
//jan 1st 2019 == tuesday
//jan 1st 2020 is wednesday
//jan 1st 2021 is friday because 2020 was a leap year
//Because jan 1st is start date the days array has been altered to make the modulus output of the days since to correspond to the array place.
String days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
String months[] = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int monthDays[] = {31,0,31,30,31,30,31,31,30,31,30,31}; //feb set to 0 to allow me to easily change it.
void checkdate(int d, int m, int y){
  String monthI = months[m-1];
  String dayI = days[d-1];
  int daysSince = 0;
  int daysInYr = 0;
  int i = m - 1;
  for (i > 0; i = i - 1;) {
    if(i == 1){
      daysInYr = daysInYr + leapYear(y);
    }else{
      daysInYr = daysInYr + monthDays[m-2];
    }
  }
  daysInYr = daysInYr + d;
  daysSince = daysInYr;
  if(y > 17){
    int yd = y - 17;
    while(yd > 0){
      if(leapYear(y + yd) == 29){
        daysSince = daysSince + 366;
      }else{
        daysSince = daysSince + 365;
      }
      yd = yd -1;
    }
  }else{
    daysSince = daysInYr;
  }
  String daysSinceS = String(daysSince);
 Serial.println(days[daysSince % 7]);
 Serial.println(daysSinceS);
}
void loop() {
  // put your ma in code here, to run repeatedly:
  int randD = random(1, 28);
  int randM = random(1, 12);
  int randY = random(17, 99);
  String randDS = String(randD);
  String randMS = String(randM);
  String randYS = String(randY);
  Serial.println("--------------------");
  Serial.println(randDS + "/" + randMS + "/" + randYS);
  checkdate(randD, randM, randY);
  delay(10000);
}
