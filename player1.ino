#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "PinChangeInterrupt.h"

#define BOUTON_AUGMENTATION1 14
#define BOUTON_REDUCTION1 15
#define BOUTON_TEMPS_MORT1 16
#define BOUTON_FIN 17
#define BUZZER 7
#define TFT_DC 9
#define TFT_CS 10

const unsigned long dureeAntiRebond = 2;

boolean bp1;
boolean bp2;
boolean bp3;
boolean tM_OK=0;
byte score_1=0,scoreMem=0;
unsigned long tempo;
int count=0;
String scoreFinal_1;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  

Serial.begin(9600);
pinMode(BOUTON_AUGMENTATION1,INPUT);
pinMode(BOUTON_REDUCTION1,INPUT);
pinMode(BOUTON_TEMPS_MORT1,INPUT);
pinMode(BOUTON_FIN,INPUT);
pinMode(BUZZER, OUTPUT);
//Serial.begin(9600);
attachPCINT(digitalPinToPCINT(BOUTON_TEMPS_MORT1), timeout, RISING);
tft.begin();
tft.setRotation(1);
tft.fillScreen(ILI9341_WHITE);
tft.setTextColor(ILI9341_MAGENTA);
tft.setTextSize(12);
scoreFinal_1 = String(score_1)+"-0";
tft.setCursor(60,20);
tft.println(scoreFinal_1);
tft.drawCircle(110,180,30,ILI9341_RED);
tft.drawCircle(200,180,30,ILI9341_RED);
}

void timeout(void){
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
    count++;
    //Serial.println(count);
    if(count==1){
      tft.fillCircle(110,180,30,ILI9341_RED);   
    }
    if(count==2){
      tft.fillCircle(200,180,30,ILI9341_RED);
      count=0;
    }
    tM_OK=1;
    tempo=millis();
    //Serial.println("tempo = "+String(tempo));
  }
}

void loop() {
  delay(200);
  bp2 = digitalRead(BOUTON_AUGMENTATION1);
  bp3 = digitalRead(BOUTON_REDUCTION1);
  
  if(tM_OK && (millis()-tempo)>30000){
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
    tM_OK=0;
  }
    

  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
     if(bp2 == 1 && score_1<8){
      score_1 = score_1 + 1;
      do{
        bp2 = digitalRead(BOUTON_AUGMENTATION1);
      }while(bp2);
     }
  }

  if ((date - dateDernierChangement) > dureeAntiRebond) {
     if(bp3 == 1 && score_1>0){
      score_1 = score_1 - 1;
      do{
        bp3 = digitalRead(BOUTON_REDUCTION1);
      }while(bp3);
     }
  }
  if(score_1!=scoreMem){
     tft.setTextColor(ILI9341_WHITE);
     tft.setCursor(60,20);
     tft.println(scoreFinal_1);
     scoreFinal_1 = String(score_1)+"-0";
     tft.setTextColor(ILI9341_MAGENTA);
     tft.setCursor(60,20);
     tft.println(scoreFinal_1);
     scoreMem=score_1;
  }
}
