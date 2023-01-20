#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup()  {
 Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
  tft.begin();
  
 
  
 
// read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  Serial.print("Largeur : ");
  Serial.print(tft.width());
  Serial.println("px");
  Serial.print("Hauteur : ");
  Serial.print(tft.height());
  Serial.println("px");
  tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(80,20);
 tft.setTextColor(ILI9341_MAGENTA);
 tft.setTextSize(9);
 tft.println("7-2");
 tft.drawCircle(110,180,30,ILI9341_RED);
 tft.fillCircle(200,180,30,ILI9341_RED);
}
void loop(){}

