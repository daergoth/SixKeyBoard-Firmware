#include "StorageHandler.h"
#include "UpdateHandler.h"
#include "KeyHandler.h"

void onFirstPowerOn() 
{
  if (StorageHandler::isDefault()) {
    StorageHandler::setToDefaults();
      
  }
}

void setup()
{
  Serial.begin(250000);

  EEPROM.write(EEPROM.length() - 1, 255);
  
  onFirstPowerOn();

  UpdateHandler::setupSerial();
	KeyHandler::setKeyPins(15, A0, 2, 8, 7, 4);
	KeyHandler::setMappingSwitchPin(A1);
  
}

void loop()
{

	KeyHandler::handleInput();

  UpdateHandler::handleUpdates();

}
