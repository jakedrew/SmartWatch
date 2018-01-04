#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";

const char* host = "ip-api.com";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  String url = "/csv/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  while(client.available()){
    String output;
    String line = client.readStringUntil('\r');


    
    const int numberOfPieces = 14;
    String pieces[numberOfPieces];
    String input = line;
    
    int counter = 0;
    
    int lastIndex = 0;
    

 
    
   

      for (int i = 0; i < input.length(); i++) {
        if (input.substring(i, i+1) == ",") {
          pieces[counter] = input.substring(lastIndex, i);
          lastIndex = i + 1;
          counter++;
        }

        if (i == input.length() - 1) {
          pieces[counter] = input.substring(lastIndex, i);
        }
      }
      

      input = "";
      counter = 0;
      lastIndex = 0;
    

    

   
    Serial.print("Location:");
    Serial.println(pieces[5]);
    
    Serial.print("IP ADDR:");
    Serial.println(pieces[13]);
  }
  
  Serial.println();
  Serial.println("closing connection");
}




////next 




//#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
char ssid[] = "";       
char pass[] = "";  
#define TELEGRAM_BUTTON_PIN D5



#define BOT_TOKEN "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig"
#define CHAT_ID "-168977312" 


WiFiClientSecure client;

//UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;

void setup() {

  Serial.begin(115200);

  pinMode(TELEGRAM_BUTTON_PIN, INPUT);


//  attachInterrupt(TELEGRAM_BUTTON_PIN, telegramButtonPressed, CHANGE);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
    int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  delay(1000);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

}

IPAddress ip;
IPAddress gateway;

void loop() {
  //http://ip-api.com/json
  
  ip = WiFi.localIP();
  Serial.print("LocalIP: ");
  Serial.println(ip);
  gateway = WiFi.gatewayIP();
  Serial.print("GATEWAY: ");
  Serial.println(gateway);
  delay(10000);
}


///next



#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char *ssid = "SmartWatch D1";

const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {

server.send(200, "text/html", "<h1>You are connected</h1>");

}
void handleWifi() {

String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 200, "text/plain", message );

}
void setup() {

delay(1000);

Serial.begin(115200);

Serial.println();

Serial.print("Configuring access point...");

WiFi.softAP(ssid, password);

IPAddress myIP = WiFi.softAPIP();

Serial.print("AP IP address: ");

Serial.println(myIP);

server.on("/", handleRoot);
server.on("/wifi", handleWifi);

server.begin();

Serial.println("HTTP server started");

}

void loop() {

server.handleClient();

}



////next

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SPI.h>  
#include <TelegramBot.h>  
 
char ssid[] = "";       
char pass[] = "";
const char* BotToken = "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig";    
WiFiClientSecure client;
TelegramBot bot(BotToken,client);  
const int ledPin = D4;  
void setup() 
{  
 Serial.begin(115200);  
 while (!Serial) {}  
 delay(3000);  
 Serial.print("Connecting Wifi: ");  
 Serial.println(ssid);  
 while (WiFi.status() != WL_CONNECTED) 
       {  
   Serial.print(".");  
   delay(500);  
 }  
 Serial.println("");  
 Serial.println("WiFi connected");  
 bot.begin();  
 pinMode(ledPin, OUTPUT);  
}  
void loop() 
{  
 message m = bot.getUpdates(); // Read new messages  
 if (m.text.equals("On")) 
       {  
   digitalWrite(ledPin, HIGH);  
   Serial.println("message received");  
 }  
 else if (m.text.equals("Off")) 
       {  
   digitalWrite(ledPin, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "low");  
 }  
}  


///next 



#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

String signal="";
void loop() {
  Serial.println("scan start");

  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      if(WiFi.RSSI(i) <= -100){
        signal = "0"; //dbm is below minimum signal power so we set to 0%
      }else if(WiFi.RSSI(i) >= -10){
        signal = "100"; //dbm is above maximum signal power so we set to 100%
      }else{
        signal = String(round((WiFi.RSSI(i) + 100)/0.9)); //converts dbm to signal %, 
      }
      Serial.print(" : ");
      Serial.print(signal);
      Serial.print("%)");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  delay(5000);
}



//next



#include <SPI.h>
#include <WiFi.h>

char ssid[] ="";  
char pass[] =""; 
int status = WL_IDLE_STATUS;    

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

void loop() {
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

/////next


#include <UniversalTelegramBot.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

char ssid[] = "";     
char pass[] = "";  
#define TELEGRAM_BUTTON_PIN D5



#define BOT_TOKEN "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig"  
#define CHAT_ID "-168977312" 


WiFiClientSecure client;

UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;

void setup() {

  Serial.begin(115200);

  pinMode(TELEGRAM_BUTTON_PIN, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
    int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  delay(1000);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

}

void telegramButtonPressed() {
//  Serial.println("telegramButtonPressed");
//  sendTelegramMessage();
//  int button = digitalRead(TELEGRAM_BUTTON_PIN);
//  if(button == HIGH)
//  {
//    telegramButtonPressedFlag = true;
//  }
  return;
}

void sendTelegramMessage() {
  String message = "/ifttt@ifttt D1 ";
//  message.concat(ssid);
//  message.concat("\n");
//  message.concat("IP: ");
  message.concat(ipAddress);
  //message.concat("\n");
  if(bot.sendMessage(CHAT_ID, message.c_str())){
    Serial.println("TELEGRAM Successfully sent");
    delay(15000);
  }else{
    Serial.println("Failed to send.");
  }
  telegramButtonPressedFlag = false;
}

void loop() {
  
//  int button = digitalRead(TELEGRAM_BUTTON_PIN);
//  if(button == HIGH){
//    sendTelegramMessage();
//  }
//  message m = bot.getUpdates();
//
//  if ( telegramButtonPressedFlag ) {
//    sendTelegramMessage();
//  }
}
