// LightHandler.h

#ifndef _LIGHTHANDLER_h
#define _LIGHTHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

class LightHandler {

public:
  static void handleLighting();
  
  static void setLightingPins();
  static void setLightingMode(byte mode);

  static void key_down(uint8_t key_id);

private:
  /*
  * 0 - Constant
  * 1 - Pulse
  * 2 - Reactive
  */
  static byte light_mode;

  // Maximum brightness(0 - 10)
  static int max_brightness;

  // Time interval for pulsing in milliseconds
  static int pulse_interval;

  // Cooldown time for reactive in milliseconds
  static int reactive_cooldown;
};

#endif
