#include "StorageHandler.h"
#include "UpdateHandler.h"
#include "KeyHandler.h"
#include "LightHandler.h"

void onFirstPowerOn() 
{
  if (StorageHandler::isDefault()) {
    StorageHandler::setToDefaults();
      
  }
}

void initialize() {
  UpdateHandler::setupSerial();
  
  KeyHandler::setKeyPins(15, A0, 2, 8, 7, 4);
  
  KeyHandler::setMappingSwitchPin(A1);
  
  LightHandler::setLightingPins();

  onFirstPowerOn();
}

void setup()
{
  Serial.begin(250000);

  EEPROM.write(EEPROM.length() - 1, 255);

  initialize();
}

void loop()
{
	KeyHandler::handleInput();
  KeyHandler::handleMacros();

  UpdateHandler::handleUpdates();

  LightHandler::handleLighting();

}
