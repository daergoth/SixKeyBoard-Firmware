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
  
  static void setLightingPins(uint8_t commonLedOne, uint8_t commonLedTwo, uint8_t three, uint8_t four, uint8_t five, uint8_t six, uint8_t doubleLed);
  
  static void setLightingMode(byte mode);

  static void setMaxBrightness(int brightness);

  static void setPulseInterval(int pulse_int);

  static void setReactiveCooldown(int react_cd);

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

  static uint8_t led_pins[6];
  static uint8_t double_led_pin;

  static byte pulseWay;
  static int pulseValue;
  static long pulseLastMillis;
  static int pulseBaseValue;

  static void lightingConstant();
  static void lightingPulse();
  static void lightingReactive();
};

#endif
