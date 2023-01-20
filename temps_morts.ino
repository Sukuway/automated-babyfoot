#include "PinChangeInterrupt.h"

#define DEL1 0
#define DEL2 13
#define BOUTON_AUGMENTATION1 14
#define BOUTON_REDUCTION1 15
#define BOUTON_TEMPS_MORT1 16
#define BOUTON_FIN 17
#define BUZZER 7

const unsigned long dureeAntiRebond = 1;

boolean bp1;
boolean bp2;
boolean bp3;
boolean tM_OK=0;
byte score;
unsigned long tempo;
int count=0;

void setup() {
  
pinMode(DEL1,OUTPUT);
pinMode(DEL2,OUTPUT);
pinMode(BOUTON_AUGMENTATION1,INPUT);
pinMode(BOUTON_REDUCTION1,INPUT);
pinMode(BOUTON_TEMPS_MORT1,INPUT);
pinMode(BOUTON_FIN,INPUT);
pinMode(BUZZER, OUTPUT);
//Serial.begin(9600);
attachPCINT(digitalPinToPCINT(BOUTON_TEMPS_MORT1), timeout, RISING);
digitalWrite(DEL1, LOW);
  digitalWrite(DEL2, LOW);
}

void timeout(void){
  static unsigned long dateDernierChangement = 0;
  unsigned long date = millis();
  if ((date - dateDernierChangement) > dureeAntiRebond) {
    count++;
    //Serial.println(count);
    if(count==1){
      digitalWrite(DEL1, HIGH);
    }
    if(count==2){
      digitalWrite(DEL2, HIGH);
      count=0;
    }
    tM_OK=1;
    tempo=millis();
    //Serial.println("tempo = "+String(tempo));
  }
}

void loop() {
  
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
     if(bp2 == 1){
      score = score + 1;
      do{
        bp2 = digitalRead(BOUTON_AUGMENTATION1);
      }while(bp2);
     }
  }

  if ((date - dateDernierChangement) > dureeAntiRebond) {
     if(bp3 == 1){
      score = score - 1;
      do{
        bp3 = digitalRead(BOUTON_REDUCTION1);
      }while(bp3);
     }
  }
}
