
#include <arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include "newOrder.h"


bool newOrder = false;

HTTPClient http2;
const char* newOrderApi = "https://dealplor.com/api/v1/caller/new";

void checkNewOrderLoop()
{
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();

  Serial.print("Error on sending POST: ");
  Serial.println(httpResponseCode);
  Serial.println("trying GET ..");
  http2.end();
  String getURL = "https://dealplor.com/api/v1/caller/new?deviceId=" + String(ESP.getChipId()) + "&phone=" + getNewNumber() ;
  http2.begin(*client, getURL);
  int httpResponseCode = http2.GET();
      if (httpResponseCode == 200)
            {
              String response = http.getString();
              Serial.println("GET request done"); 
              Serial.println(httpResponseCode);
              Serial.println(response);
            }
            else
            {
              Serial.print("Error on sending GET: ");
              Serial.println(httpResponseCode);
            }

            
    // تحليل الرد المستلم باستخدام JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // الحصول على قيمة المتغير "result" من الرد
    bool result = doc["result"];


    if(newOrder)
    {
        tonePlay();
    }



    void tonePlay()
    {
     for (int i = 0; i < 8; i++) { // مكرر للعب النغمة مرات متعددة
         int note = furElise[i];
         tone(speakerPin, note, noteDuration); // إنتاج النغمة على المكبر الصوتي
         Serial.println("ON");
         delay(noteDuration); // تأخير لمدة مساوية لمدة النغمة
  }
    }

}