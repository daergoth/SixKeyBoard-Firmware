#ifndef _UPDATEHANDLER_H_
#define _UPDATEHANDLER_H_

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "StorageHandler.h"

class UpdateHandler {
public:
  static void setupSerial();
  static void handleUpdates();
  
private:
  
  
};

#endif

