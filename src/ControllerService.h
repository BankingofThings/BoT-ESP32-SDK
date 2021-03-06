/*
  ControllerService.h - Class and Methods to interface between Webserver End Points
                        and the backend service components
  Created by Lokesh H K, April 24, 2019.
  Released into the repository BoT-ESP32-SDK.
*/

#ifndef ControllerService_h
#define ControllerService_h
#include "BoTESP32SDK.h"
#include "Storage.h"
#include "PairingService.h"
#include "ActionService.h"
#include "ActivationService.h"
#include "ConfigurationService.h"

class ActionService;
class ControllerService {
  public:
          ControllerService();
          void getActions(AsyncWebServerRequest *request);
          void pairDevice(AsyncWebServerRequest *request);
          void activateDevice(AsyncWebServerRequest *request);
          void getQRCode(AsyncWebServerRequest *request);
          void postAction(AsyncWebServerRequest *request);
  private:
    KeyStore* store;
    ActionService* actionService;
    int triggerAction(const char* actionID);
};
#endif
