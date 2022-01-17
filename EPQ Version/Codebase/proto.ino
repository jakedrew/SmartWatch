#include <Wire.h>
#include "SSD1306.h"
#include "SH1106.h"
#include "images.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int button = 0;
SH1106 display(0x3c, D1, D2);

const char *ssid = "SmartWatch D1";

const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {

  server.send(200, "text/html", "<h1>You are connected</h1>");

}
void handleWifi() {
  String message = "";
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
  button = 1;
}



int demoMode = 0;
int counter = 1;
void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.on("/", handleRoot);
  server.on("/wifi", handleWifi);
  
  server.begin();
}


void drawImage() {
    
    if(button == 1){
        display.setFont(ArialMT_Plain_10);

         display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(64, 22, "/wifi opened");
    }else{
      //display.drawXbm(34, 14, WiFi_lw, WiFi_lh, WiFi_lb);
      display.drawXbm(34, 14, WiFi_iw, WiFi_ih, WiFi_ib);
    }
}


long timeSinceLastModeSwitch = 0;

void loop() {
  display.clear();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  display.display();

  if (millis() - timeSinceLastModeSwitch > 1000) {
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  
  server.handleClient();
  delay(10);
}


