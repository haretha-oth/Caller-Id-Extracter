

#include <arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "xwifi.h"


int wifi_srv_steps;
const char* esp_ssid = "dealplor";       //Set your own name for ESP32
const char* esp_password = "12345678";  //Set the password of SSID

ESP8266WebServer server(80);

unsigned long  srv_xtimer;


String HTML = "<!DOCTYPE html><html><body><h2>Wellcome to DEALPLOR</h2><p>please enter your router's <strong>SSID and password</strong> to be able to contact with enternet:</p><form action=\"/save\"> <label for=\"fname\">Your router SSID:</label><br> <input type=\"text\" id=\"fname\" name=\"SSIDC\"><br>  <label for=\"lname\">Your router password:</label><br>  <input type=\"text\" id=\"lname\" name=\"PASSC\"><br><br>  <input type=\"submit\" value=\"Submit\"></form><p>Note that after you submit, you will lose this page.</p><p>then your device will contact your router automatically.</p><p>Also note that the default width of a text field is 20 characters.</p></body></html>";
String HTML_done = "NOW YOUR DEVICE WILL RESTART AND CONNECT WITH YOUR ROUTER, ";

void wifiServer_Setup()
{
  wifi_srv_steps = 0;
  srv_xtimer = 0;
}



void wifi_server()
{
  if(wifi_srv_steps == 0)
  {
      //WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      srv_xtimer =  millis() + 100;    
      wifi_srv_steps++;
  }
  else if(wifi_srv_steps == 1)
  {
      if(srv_xtimer <  millis())   
      {
        WiFi.softAP(esp_ssid, esp_password);

        server.on("/", handle_OnConnect);
        server.on("/save", handle_Onsave);
        //server.onNotFound(handle_NotFound);
        server.begin();
        Serial.println("wifi server started.. connect with 192.168.4.1  : ");
   
        srv_xtimer =  millis() + 200000;  
        wifi_srv_steps++;
      }
  }
  else if(wifi_srv_steps == 2)
  {
      server.handleClient();
      
      if(srv_xtimer <  millis()) 
      {
        srv_xtimer =  millis() + 200000; 
        Serial.println("------------ no action -----------");
        
        if(getNoData() == false)
        {
          wifi_srv_steps = 0;
          setWifiMode(WIFI_MODE_STA);
        }
      }
  }
 
}



void handle_OnConnect() 
{
  server.send(200, "text/html", HTML);
}


void handle_Onsave() 
{
  
  String ssid_arg = server.arg("SSIDC");
  String pass_arg = server.arg("PASSC");
  
  server.send(200, "text/html", HTML_done);

  preferences.begin("credentials", false);
  if (preferences.clear())
  {
     Serial.println("flash removed ..");
     preferences.putString("ssid",ssid_arg);
     preferences.putString("password",pass_arg);
     preferences.end();
     setNoData(0);
   }
    else Serial.println("couldn't remove");           

  ESP.restart();
                 
                 
}
