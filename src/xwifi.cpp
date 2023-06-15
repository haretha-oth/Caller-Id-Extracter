

//including

#include <arduino.h>
#include <ESP8266WiFi.h>
#include <Preferences.h>


#include "xwifi.h"
#include "cloudServer.h"
#include "telephone.h"


//WiFi variabls
Preferences preferences;


int wifi_mode;

unsigned long volatile  wifi_xtimer;
int  No_Data;// 0 mean there are a ssid and password   1 mean there are not ssid or passowrd

int chip_id;


char ssid[100] ;//customer ssid
char password[100]  ;//customer password

int  wifi_connect_steps;


///////////////////////////////////
void wifiSetup() 
{ 
  wifiServer_Setup();

  
  wifi_mode = WIFI_MODE_STA ; 
  wifi_connect_steps = 0;

  No_Data = 0 ;// 0 mean there are a ssid and password   1 mean there are not ssid or passowrd



   chip_id = ESP.getChipId();
   Serial.print("chip id : ");
   Serial.println (chip_id);
   
   preferences.begin("credentials", false);
   int y = preferences.getString("ssid",ssid,100);
   int x  = preferences.getString("password",password, 100); 
   preferences.end();
   
   if (y==0 || x==0)
   {
      //Serial.println("there is no data to copy..");
      //wifi_mode = WIFI_MODE_AP;
      No_Data = 1;       
   }

}
  
void wifiLoop() 
{
   if(wifi_mode == WIFI_MODE_STA) 
   {
      wifi_connect(); 
   }
   else if ( wifi_mode == WIFI_MODE_AP)
   {
      wifi_server();
   }   
}

//////////////////////////////////////////////////////////////////////////
void setWifiMode(int x)
{
  wifi_mode = x;
}

void setNoData(int x)
{
  No_Data = x;
}


int getWifiMode()
{
  return wifi_mode;
}

int getNoData()
{
  return No_Data;
}

bool isWifiConnected()
{

  return (WiFi.status() == WL_CONNECTED);
}

//////////////////////////////////////////////////////////////////////////
void wifi_connect() 
{
  unsigned long time_ms = millis();

  if(wifi_connect_steps == 0)
  {
    if(WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Trying to connect to12 wifi");
      wifi_connect_steps++;      
    }
  }
  else if(wifi_connect_steps == 1)
  {
      //WiFi.mode(WIFI_STA);
      wifi_xtimer =  time_ms + 1000L;
      Serial.println(String(wifi_xtimer));
      wifi_connect_steps++; 
  }
  else if(wifi_connect_steps == 2)
  {
    if(wifi_xtimer < time_ms)
    {
      WiFi.begin(ssid, password); 
      Serial.print("trying to connect to ");
      Serial.println(ssid);
      wifi_xtimer =  time_ms + 100000L;    
      wifi_connect_steps++;   
    } 
  }
  else if(wifi_connect_steps == 3)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      wifi_connect_steps = 0;

      Serial.println("");  
      Serial.print("WiFi connected to: "); 
      Serial.println(ssid);  
      Serial.println("IP address: ");  
      Serial.println(WiFi.localIP());
    }
    else if(wifi_xtimer < time_ms)
    {
        wifi_connect_steps = 0;
        Serial.println("\r\n will change mode to host mode for 2 mintes.. ");
        Serial.println("fiald to connet with ssid and password  : ");
        Serial.println(ssid);
        Serial.println(password);
        wifi_mode = WIFI_MODE_AP;
    }
  }
   
}
