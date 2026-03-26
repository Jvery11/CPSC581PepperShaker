#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Oled Documentation:
// https://esp32io.com/tutorials/esp32-oled

////////////////////////////////
////      GPIO Pins         ////
////////////////////////////////

///////////
//  BTN  //
//////////
#define BTN_PIN 32 // red wire
// GND -> GND       //green wire

///////////
// OLED //
//////////
#define SCL_PIN 19 // green wire
#define SDA_PIN 18 // blue wire
// VCC -> 3.3v     //red wire
// GND -> GND      //black wire
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void showText(String, String);

// 0 = show names, 1 = cuisines
int currentMode = 0;
bool lastButtonState = HIGH;
// Will use hold to change mode
unsigned long buttonPressTime = 0;

String names[] = {"Alice", "Bob", "Jason", "Justin", "Julliana"};
String cuisines[] = {"Italian", "Greek", "Mexican", "Thai", "Japanese", "Indian"};

void setup()
{
  delay(1000);
  Serial.begin(115200);
  delay(200);

  pinMode(BTN_PIN, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);
  delay(200);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }

  showText("Howdy", "");
  delay(2000);
  oled.clearDisplay();
  delay(200);

  showText("Mode:", "Names");
}

void loop()
{
  bool currentButtonState = digitalRead(BTN_PIN);

  // button pressed
  if (lastButtonState == HIGH && currentButtonState == LOW)
  {
    buttonPressTime = millis();
  }

  // button released
  if (lastButtonState == LOW && currentButtonState == HIGH)
  {
    // Determine if held so we can switch mode
    unsigned long pressLength = millis() - buttonPressTime;

    if (pressLength > 2000)
    {
      // held so toggle mode
      currentMode = !currentMode;

      if (currentMode == 0)
      {
        showText("Mode:", "Names");
      }
      else
      {
        showText("Mode:", "Food");
      }
    }
    else
    {
      // didnt change mode so pick random item of respective list
      if (currentMode == 0)
      {
        int i = random(0, 5);
        showText("Name:", names[i]);
      }
      else
      {
        int i = random(0, 6);
        showText("Food:", cuisines[i]);
      }
    }
    delay(200);
  }

  lastButtonState = currentButtonState;
}

// defines options and prints to display
void showText(String top, String bottom)
{
  oled.clearDisplay();
  oled.setTextSize(3);
  oled.setTextColor(WHITE);

  oled.setCursor(0, 0);
  oled.println(top);

  oled.setTextSize(2);
  oled.setCursor(0, 35);
  oled.println(bottom);

  oled.display();
}
