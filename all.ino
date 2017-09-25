/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";

const char* host = "ip-api.com";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

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
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/csv/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String output;
    String line = client.readStringUntil('\r');


    
    // Define number of pieces
    const int numberOfPieces = 14;
    String pieces[numberOfPieces];
    
    // This will be the buffered string from Serial.read()
    // up until you hit a \n
    // Should look something like "123,456,789,0"
    String input = line;
    
    // Keep track of current position in array
    int counter = 0;
    
    // Keep track of the last comma so we know where to start the substring
    int lastIndex = 0;
    

 
    
   

      for (int i = 0; i < input.length(); i++) {
        // Loop through each character and check if it's a comma
        if (input.substring(i, i+1) == ",") {
          // Grab the piece from the last index up to the current position and store it
          pieces[counter] = input.substring(lastIndex, i);
          // Update the last position and add 1, so it starts from the next character
          lastIndex = i + 1;
          // Increase the position in the array that we store into
          counter++;
        }

        // If we're at the end of the string (no more commas to stop us)
        if (i == input.length() - 1) {
          // Grab the last part of the string from the lastIndex to the end
          pieces[counter] = input.substring(lastIndex, i);
        }
      }
      

      // Clear out string and counters to get ready for the next incoming string
      input = "";
      counter = 0;
      lastIndex = 0;
    

    

   
    Serial.print("Location:");
    Serial.println(pieces[5]);
    
    Serial.print("IP ADDR:");
    Serial.println(pieces[13]);
   // Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}




////next 




//Including the two libraries
//#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//------- WiFi Settings -------
char ssid[] = "";       // your network SSID (name)
char pass[] = "";  
#define TELEGRAM_BUTTON_PIN D5



// ------- Telegram config --------
#define BOT_TOKEN "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig"  // your Bot Token (Get from Botfather)
//#define CHAT_ID "413136155" // Chat ID of where you want the message to go (You can use MyIdBot to get the chat ID)
#define CHAT_ID "-168977312" // Chat ID of where you want the message to go (You can use MyIdBot to get the chat ID)


// SSL client needed for both libraries
WiFiClientSecure client;

//UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;

void setup() {

  Serial.begin(115200);

  // Initlaze the buttons
  pinMode(TELEGRAM_BUTTON_PIN, INPUT);

  // NOTE:
  // It is important to use interupts when making network calls in your sketch
  // if you just checked the status of te button in the loop you might
  // miss the button press.
//  attachInterrupt(TELEGRAM_BUTTON_PIN, telegramButtonPressed, CHANGE);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
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
      // Print SSID and RSSI for each network found
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

  // Wait a bit before scanning again
  delay(1000);
  // Attempt to connect to Wifi network:
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
  http://ip-api.com/json
  
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
 
// Initialize Wifi connection to the router  
//char ssid[] = "JSE";       // your network SSID (name)
//char pass[] = "jakedrew";  // your network key
char ssid[] = "Homeworking2_EXT";       // your network SSID (name)
char pass[] = "Worldcup66";  // your network key
// Initialize Telegram BOT  
const char* BotToken = "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig";    // your Bot Teken  
WiFiClientSecure client;
TelegramBot bot(BotToken,client);  
const int ledPin = D4;  // the number of the LED pin  
void setup() 
{  
 Serial.begin(115200);  
 while (!Serial) {}  //Start running when the serial is open 
 delay(3000);  
 // attempt to connect to Wifi network:  
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
   bot.sendMessage(m.chat_id, "The Led is now ON");  
 }  
 else if (m.text.equals("Off")) 
       {  
   digitalWrite(ledPin, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led is now OFF");  
 }  
}  


///next 



/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

String signal="";
void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
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
      // Print SSID and RSSI for each network found
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

  // Wait a bit before scanning again
  delay(5000);
}



//next



#include <SPI.h>
#include <WiFi.h>

char ssid[] ="";     //  your network SSID (name)
char pass[] ="";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
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
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
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

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

/////next


//Including the two libraries
#include <UniversalTelegramBot.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- WiFi Settings -------
char ssid[] = "";       // your network SSID (name)
char pass[] = "";  
#define TELEGRAM_BUTTON_PIN D5



// ------- Telegram config --------
#define BOT_TOKEN "351635946:AAHr7qGistKdQ1fIKb-a2MwLxDyDDKgG9ig"  // your Bot Token (Get from Botfather)
//#define CHAT_ID "413136155" // Chat ID of where you want the message to go (You can use MyIdBot to get the chat ID)
#define CHAT_ID "-168977312" // Chat ID of where you want the message to go (You can use MyIdBot to get the chat ID)


// SSL client needed for both libraries
WiFiClientSecure client;

UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;

void setup() {

  Serial.begin(115200);

  // Initlaze the buttons
  pinMode(TELEGRAM_BUTTON_PIN, INPUT);

  // NOTE:
  // It is important to use interupts when making network calls in your sketch
  // if you just checked the status of te button in the loop you might
  // miss the button press.
//  attachInterrupt(TELEGRAM_BUTTON_PIN, telegramButtonPressed, CHANGE);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
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
      // Print SSID and RSSI for each network found
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

  // Wait a bit before scanning again
  delay(1000);
  // Attempt to connect to Wifi network:
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
