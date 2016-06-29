#include "StorageHandler.h"

unsigned int StorageHandler::memory_end = 0;

unsigned int StorageHandler::memory_addresses[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Action* StorageHandler::getActionsForKey(uint8_t key_id, byte switch_status)
{  
	byte t = EEPROM.read(memory_addresses[switch_status * 6 + key_id]);

  if (t == 0) {
    SimpleAction* a = new SimpleAction(0, 0);

    EEPROM.get(memory_addresses[switch_status * 6 + key_id], *a);

    return a;
  } else if (t == 1) {
    
  }

  
  
}

void StorageHandler::setActionsForKey(uint8_t key_id, byte switch_status, Action action)
{

}

bool StorageHandler::isDefault() 
{
    byte r = 1;
    EEPROM.get(EEPROM.length() - 1, r);
    return r != 0;
}

void StorageHandler::setToDefaults() 
{
  unsigned int currentMemoryAddress = 0;
  
  SimpleAction key(0, '1');
  for (byte i = 0; i < 6; ++i) {
    memory_addresses[i] = currentMemoryAddress;
    EEPROM.put(currentMemoryAddress, key);
    key.value = key.value + 1;
    currentMemoryAddress += 3;
    memory_end = currentMemoryAddress;
  }

  byte r = 0;
  EEPROM.put(EEPROM.length() - 1, r);
}

