

#include <Wire.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 tSensor = Adafruit_MCP9808();

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_box_frame(uint8_t a) {
  u8g.drawStr( 0, 0, "drawBox");
  u8g.drawBox(5,10,20,10);
  u8g.drawBox(10+a,15,30,7);
  u8g.drawStr( 0, 30, "drawFrame");
  u8g.drawFrame(5,10+30,20,10);
  u8g.drawFrame(10+a,15+30,30,7);
  
  tSensor.begin(0x19);
  tSensor.wake();

  float c = tSensor.readTempC();

  char outstr[15];

  dtostrf(c,7, 3, outstr);
  tSensor.shutdown();
  u8g.drawStr( 10, 10,c);
}





uint8_t draw_state = 0;

void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
  }
}

void setup(void) {

  // flip screen, if required
  //u8g.setRot180();

#if defined(ARDUINO)
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
#endif
}

void loop(void) {
  
  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // increase the state
 // draw_state++;
  //if ( draw_state >= 9*8 )
    //draw_state = 0;
  
  // rebuild the picture after some delay
  //delay(150);

}


