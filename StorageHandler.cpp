#include "StorageHandler.h"

unsigned int StorageHandler::memory_end = 0;

unsigned int StorageHandler::memory_addresses[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Action* StorageHandler::getActionsForKey(uint8_t key_id, byte switch_status)
{  
	byte t = EEPROM.read(memory_addresses[switch_status * 6 + key_id]);

  Serial.print("MODE+KEY: ");
  Serial.println(switch_status * 6 + key_id);
  
  Serial.print("MEMORY ADDRESS: ");
  Serial.println(memory_addresses[switch_status * 6 + key_id]);
  
  Serial.print("TYPE: ");
  Serial.println(t);

  if (t == 0) {
    return readSimpleAction(memory_addresses[switch_status * 6 + key_id]);
  } else if (t == 1) {
    return readMacro(memory_addresses[switch_status * 6 + key_id]);
  }
}

void StorageHandler::setActionsForKey(uint8_t key_id, byte switch_status, Action* action)
{
  memory_addresses[switch_status * 6 + key_id] = memory_end;

  if (action->action_type == 0) {
    SimpleAction* simple = static_cast<SimpleAction*>(action);
    saveSimpleAction(*simple);
    
  } else if (action->action_type == 1) {
    Macro* macro = static_cast<Macro*>(action);
    saveMacro(*macro);
  }
}

bool StorageHandler::isDefault() 
{
    byte r = 1;
    EEPROM.get(EEPROM.length() - 1, r);
    return r != 0;
}

void StorageHandler::setToDefaults() 
{
  // Mode 1: utility keys
  SimpleAction key(0, 209);
  for (byte i = 0; i < 6; ++i) {
    memory_addresses[i] = memory_end;
    saveSimpleAction(key);
    key.value += 1;
  }

  // Mode 2: arrows
  byte nav_keys[6] = {128, 218, 129, 216, 217, 215};
  for (byte i = 0; i < 6; ++i) {
    memory_addresses[i + 6] = memory_end;
    key.value = nav_keys[i];
    saveSimpleAction(key);
  }

  // Create macro
  char name[21] = {'E', 'x', 'a', 'm', 'p', 'l', 'e', ' ', 'n', 'a', 'm', 'e', '\0'};
  Macro macro(name, 21);

  SimpleAction s(0, 'm');
  macro.addAction(s);
  s.type = 1;
  macro.addAction(s);

  s.type = 0;
  s.value = 'a';
  macro.addAction(s);
  s.type = 1;
  macro.addAction(s);

  s.type = 0;
  s.value = 'c';
  macro.addAction(s);
  s.type = 1;
  macro.addAction(s);

  macro.setRepeatability(0);
  
  memory_addresses[0] = memory_end;

  // Save macro
  saveMacro(macro);

  // Byte for first poweron set
  byte r = 0;
  EEPROM.put(EEPROM.length() - 1, r);
}

void StorageHandler::saveSimpleAction(SimpleAction simple) {
  EEPROM.put(memory_end, simple);
  memory_end += sizeof(SimpleAction);
}

void StorageHandler::saveMacro(Macro macro) {
  EEPROM.write(memory_end, macro.action_type);
  memory_end += 1;

  EEPROM.write(memory_end, macro.actions.size());
  memory_end += 1;
  
  for (byte i = 0; i < 21; ++i) {
    EEPROM.write(memory_end + i, macro.name[i]);
  }
  memory_end += 21;

  for (SimpleList<SimpleAction>::iterator itr = macro.actions.begin(); itr != macro.actions.end(); ++itr)
  {
    EEPROM.put(memory_end, *itr);
    memory_end += 3;
  } 

  EEPROM.write(memory_end, macro.repeatability);
  memory_end += 1;
}

SimpleAction* StorageHandler::readSimpleAction(int byte_pos) {
  SimpleAction* simple = new SimpleAction();
  EEPROM.get(byte_pos, *simple);
  return simple;
}

Macro* StorageHandler::readMacro(int byte_pos) {
  byte action_num = EEPROM.read(byte_pos + 1);

  char name[21];
  for (byte i = 0; i < 21; ++i) {
    name[i] = EEPROM.read(byte_pos + 2 + i);
  }

  Macro* m = new Macro(name, 21);

  SimpleAction s(0, 0);
  for (byte i = 0; i < action_num; ++i) {
    EEPROM.get(byte_pos + 23 + (i * 3), s);
      
    m->addAction(s);
  }

  byte rep = 0;
  
  EEPROM.get(byte_pos + 23 + (action_num * 3), rep);

  m->setRepeatability(rep);

  return m;
}

