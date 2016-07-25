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

  static void setMaxBrightness(byte brightness);

  static void setPulseInterval(unsigned int pulse_int);

  static void setReactiveCooldown(unsigned int react_cd);

  static void setWaveInterval(unsigned int wave_int);

  static void setRandomInterval(unsigned int random_int);

  static void key_down(uint8_t key_id);

private:
  /*
  * 0 - Constant
  * 1 - Pulse
  * 2 - Reactive
  * 3 - Wave
  * 4 - Random 
  */
  static byte light_mode;

  // Maximum brightness(0 - 10)
  static byte max_brightness;

  // Time interval for pulsing in milliseconds
  static unsigned int pulse_interval;

  // Cooldown time for reactive in milliseconds
  static unsigned int reactive_cooldown;

  // Time interval for wave in milliseconds
  // Defines how much time ellapsed between wave starts
  static unsigned int wave_interval;

  // Time interval for random in milliseconds
  // Defines how often randomizing will happen
  static unsigned int random_interval;

  static uint8_t led_pins[6];
  static uint8_t double_led_pin;

  static byte pulseWay;
  static unsigned int pulseValue;
  static unsigned long pulseLastMillis;
  static unsigned int pulseBaseValue;

  static void lightingConstant();
  static void lightingPulse();
  static void lightingReactive();
  static void lightingWave();
  static void lightingRandom();
};

#endif
