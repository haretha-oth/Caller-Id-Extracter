


#define WIFI_MODE_STA 0
#define WIFI_MODE_AP 1 

#include <Preferences.h>

void wifiSetup();
void wifiLoop();

int getNoData();

void setWifiMode(int x);
int getWifiMode();
bool isWifiConnected();
void setNoData(int x);


//////////////////////////////////
// client
void wifi_connect() ;

///////////////////////////////////
// server

void wifiServer_Setup();
void wifi_server();

void handle_OnConnect();
void handle_Onsave();

extern Preferences preferences;