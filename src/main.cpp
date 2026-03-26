#include <Arduino.h>

////////////////////////////////
////      GPIO Pins         ////
////////////////////////////////

///////////
//  BTN  //
//////////
#define BTN = 1;  //red
// GND -> GND     //green

///////////
// OLED //
//////////
#define SCL = 2;  //green
#define SDA = 3;  //blue
// VCC -> 3.3v    //red
// GND -> GND     //black




void setup() {
  Serial.begin(115200);
  delay(200);



}

void loop() {

}

