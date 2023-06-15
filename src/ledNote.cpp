#include <Arduino.h>
#include "ledNote.h"
#include "xwifi.h"

unsigned long volatile  led_timer;
#define LED 2
int ledStep;
int ledOnTime;
int ledOffTime;

void ledNoteSetup()
{
    pinMode(LED, OUTPUT);
    ledStep = 0 ;
    led_timer = 0;
     ledOnTime = 0;
     ledOffTime = 0;
}


void ledNoteLoop()
{
     getLedMode();

    if (ledStep == 0)
    {
        if (millis()>led_timer)
        {
            digitalWrite(LED, HIGH);
            led_timer = millis() + ledOnTime;
            ledStep = 1;

        }
    }
    else if (ledStep == 1)
    {
        if (millis()>led_timer)
        {
        digitalWrite(LED, LOW);
            led_timer = millis() + ledOffTime;
            ledStep = 0;
        }
    }

    
    
    

}


void  getLedMode(){
    
    if(getWifiMode() == 0) 
    {
        if (isWifiConnected())
        {  
           ledOnTime = 50L;
           ledOffTime = 2000L;

        }
        else 
        {
           ledOnTime = 1000L;
           ledOffTime = 1000L;
        }
    }
    else if (getWifiMode() == 1)
    {  
           ledOnTime = 100L;
           ledOffTime = 100L;
    }


}