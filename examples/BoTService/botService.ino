/*
  botService.ino - Example sketch program to show the usage for BoTService Component of ESP-32 SDK.
  Created by Lokesh H K, April 12, 2019.
  Released into the repository BoT-ESP32-SDK.
*/

#include <BoTService.h>
#include <Storage.h>
#include <Webserver.h>

BoTService* bot;
KeyStore* store;
Webserver *server = NULL;

void setup() {

  store = KeyStore :: getKeyStoreInstance();
  store->loadJSONConfiguration();

  //Get WiFi Credentials from given configuration
  //const char* WIFI_SSID = store->getWiFiSSID();
  //const char* WIFI_PASSWD = store->getWiFiPasswd();

  //Provide custom WiFi Credentials
  const char* WIFI_SSID = "LJioWiFi";
  const char* WIFI_PASSWD = "adgjmptw";

  //Override HTTPS
  store->setHTTPS(true);

  //Instantiate Webserver by using the custom WiFi credentials
  bool loadConfig = false;
  int logLevel = BoT_ERROR;
  server = new Webserver(loadConfig,WIFI_SSID, WIFI_PASSWD,logLevel);

  //Enable board to connect to WiFi Network
  server->connectWiFi();

}

void loop() {
  #ifndef DEBUG_DISABLED
    Debug.handle();
  #endif
  
  //Proceed further if board connects to WiFi Network
  if(server->isWiFiConnected()){
    //Create BoT Service Instance
    bot = new BoTService();

    //GET Pairing Status
    debugI("\nPair Status: %s", bot->get("/pair").c_str());

    //Deallocate
    delete bot;

    //Create BoT Service Instance
    bot = new BoTService();

    //GET Actions defined in Maker Portal
    debugI("\nActions: %s", bot->get("/actions").c_str());

    //Deallocate
    delete bot;

    //Prepare JSON Data to trigger an Action through POST call
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& doc = jsonBuffer.createObject();
    JsonObject& botData = doc.createNestedObject("bot");
    botData["deviceID"] = store->getDeviceID();
    botData["actionID"] = "749081B8-664D-4A15-908E-1C3F6590930D";
    botData["queueID"] = "749081B8-6688-4A99-908E-1C3F6590930D";

    char payload[200];
    doc.printTo(payload);
    debugI("\nMinified JSON Data to trigger Action: %s", payload);

    //Create BoT Service Instance
    bot = new BoTService();

    debugI("\nResponse from triggering action: %s", bot->post("/actions",payload).c_str());

    //Deallocate
    delete bot;
  }
  else {
  LOG("\nsdkSample: ESP-32 board not connected to WiFi Network, try again");
  //Enable board to connect to WiFi Network
  server->connectWiFi();
  }

  delay(1*60*1000);
}
