// StorageHandler.h

#ifndef _STORAGEHANDLER_h
#define _STORAGEHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>
#include "Action.h"
#include "SimpleAction.h"
#include "Macro.h"

class StorageHandler {
public:
	static Action* getActionsForKey(uint8_t key_id, byte switch_status);
  
	static void setActionsForKey(uint8_t key_id, byte switch_status, Action* action);

  static bool isDefault();

  static void setToDefaults();
  
private:
  static unsigned int memory_end;

  static unsigned int memory_addresses[12];

  static void saveSimpleAction(SimpleAction simple);
  static void saveMacro(Macro macro);

  static SimpleAction* readSimpleAction(int byte_pos);
  static Macro* readMacro(int byte_pos);

};

#endif

