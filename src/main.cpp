#include <Arduino.h>

#include "ledNote.h"
#include "xwifi.h"
#include "cloudServer.h"
#include "telephone.h"
#include "newOrder.h"


void setup() {
  
  Serial.begin(1200);
  Serial.println("\r\nTrying to connect to ghtjgjhy wifi\r\n");

  TelephoneSetup();
  cloudSetup();
  ledNoteSetup();
  wifiSetup();

  
 /* preferences.begin("credentials", false);
     if (preferences.clear())
  {
     Serial.println("flash removed ..");
  }
   preferences.end();
   */
}

void loop() {
  wifiLoop();
  TelephoneLoop();
  cloudLoop();
  ledNoteLoop();
  checkNewOrderLoop();

  
}
