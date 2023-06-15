



#include <arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>

#include "xwifi.h"
#include "cloudServer.h"
#include "telephone.h"

//Server Varaibls
const char* server_dealplor = "https://dealplor.com/api/v1/caller/new";


HTTPClient http;

void cloudSetup()
{

}

void cloudLoop()
{
  if (isNewNumber())
  { 
    if(isWifiConnected())
    {
       sentData(); 
    }   
  }
   
}


int sentData()
{
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  
  String body = "{\"deviceId\":" + String(ESP.getChipId()) + ",\"phone\":" + getNewNumber()+"}";
  Serial.print("Body: ");
  Serial.println(body);
  
  setNewNumber(0);
  
  Serial.println();
  Serial.println("sending https post..."); //Serial.println(server)
  
  http.begin(*client, server_dealplor);
  
  http.addHeader("Content-Type", "application/json");
  
  Serial.println("Post");
  int httpResponseCode = http.POST(body);
  Serial.println(httpResponseCode);


  if(httpResponseCode>0)
  {
    String response = http.getString();
    if (httpResponseCode == 200)
    {
      Serial.println("POST request done"); 
      Serial.println(httpResponseCode);
      Serial.println(response);
    }
    else
    {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      Serial.println("trying GET ..");
      http.end();
      String getURL = "https://dealplor.com/api/v1/caller/new?deviceId=" + String(ESP.getChipId()) + "&phone=" + getNewNumber() ;
      http.begin(*client, getURL);
      int httpResponseCode = http.GET();
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



    }
    
    http.end(); 
  }
  else {
    
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      Serial.println("trying GET ..");
      http.end();
      String getURL = "https://dealplor.com/api/v1/caller/new?deviceId=" + String(ESP.getChipId()) + "&phone=" + getNewNumber() ;
      http.begin(*client, getURL);
      int httpResponseCode = http.GET();
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
            http.end();
  }

  return httpResponseCode;
}