/*
  Webserver.h - Library for conecting to given WiFi Network and
                Starting Async Webserver to serve the BoT requests.
  Created by Lokesh H K, April 7, 2019.
  Released into the repository BoT-ESP32-SDK.
*/
#ifndef Webserver_h
#define Webserver_h
#include "BoTESP32SDK.h"
#include "Storage.h"
#include "ControllerService.h"
#include "ConfigurationService.h"
#include "BluetoothService.h"
#include "PairingService.h"
#define STARTED 1
#define NOT_STARTED 0

class ConfigurationService;
class Webserver
{
  public:
    static Webserver* getWebserverInstance(bool loadConfig, const char *ssid = NULL,
                          const char *passwd = NULL, const int logLevel = BoT_INFO);
    bool isWiFiConnected();
    bool isServerAvailable();
    void blinkLED();
    void connectWiFi();
    void startServer();
    IPAddress getBoardIP();
  private:
    int port;
    int ledPin;
    int serverStatus;
    int debugLevel;
    String *WiFi_SSID;
    String *WiFi_Passwd;
    KeyStore *store;
    AsyncWebServer *server;
    ConfigurationService *config;
    static Webserver *webServer;
    BluetoothService *ble;
    bool isDevicePaired();
    Webserver(bool loadConfig, const char *ssid = NULL, const char *passwd = NULL,
                                                   const int logLevel = BoT_INFO);
};

#endif
