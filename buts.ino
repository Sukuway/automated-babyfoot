#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "PinChangeInterrupt.h"

#define vibration_sensor 2
#define TFT_DC 9
#define TFT_CS 10

const unsigned long dureeAntiRebond = 1;
int sensorState = 0;
byte score=0,scoreMem=0;
String scoreFinal;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {

tft.begin();
tft.setRotation(1);
tft.fillScreen(ILI9341_WHITE);
tft.setTextColor(ILI9341_MAGENTA);
tft.setTextSize(12);
scoreFinal = String(score)+"-0";
tft.setCursor(60,20);
tft.println(scoreFinal);
attachPCINT(digitalPinToPCINT(vibration_sensor), goal, RISING);

}

void goal(void){
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
       if (sensorState == HIGH && score<8 ) {
          score = score + 1;  
      do{
        sensorState = digitalRead(vibration_sensor);
      }while(sensorState);
     }
  }
}

void loop() {

  sensorState = digitalRead(vibration_sensor);

  if(score!=scoreMem){
     tft.setTextColor(ILI9341_WHITE);
     tft.setCursor(60,20);
     tft.println(scoreFinal);
     scoreFinal = "0-"+String(score);
     tft.setTextColor(ILI9341_MAGENTA);
     tft.setCursor(60,20);
     tft.println(scoreFinal);
     scoreMem=score;
  }
  
}

