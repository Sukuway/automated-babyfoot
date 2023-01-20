/*
  link between the computer and the SoftSerial Shield
  at 9600 bps 8-N-1
  Computer is connected to Hardware UART
  SoftSerial Shield is connected to the Software UART:D2&D3
*/
 
#include <SoftwareSerial.h>
 
SoftwareSerial SoftSerial(5, 6);

char val;
String id_carte;

void setup()
{
    SoftSerial.begin(9600);    
    Serial.begin(9600);         
}
 
void loop()
{
    if (SoftSerial.available())              
    {
        do{
          val=SoftSerial.read();                
        }while(val!=2);
        id_carte=SoftSerial.readStringUntil(3);
        Serial.println(id_carte);
    }  
}
