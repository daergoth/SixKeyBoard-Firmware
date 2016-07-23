#include "LightHandler.h"

byte LightHandler::light_mode = 0;

int LightHandler::max_brightness = 5;
int LightHandler::pulse_interval = 1000;
int LightHandler::reactive_cooldown = 500;

uint8_t LightHandler::led_pins[] = {0, 0, 0, 0, 0, 0};
uint8_t LightHandler::double_led_pin = 0;

byte LightHandler::pulseWay = 1;
int LightHandler::pulseValue = 0;
int LightHandler::pulseBaseValue = 8;
long LightHandler::pulseLastMillis = 0;

void LightHandler::handleLighting() {
  
  switch(light_mode) {
  case 0:
    lightingConstant();
    break;
  case 1:
    lightingPulse();
    break;
  case 2:
    lightingReactive();
    break;
  }
  
}

void LightHandler::setLightingPins(uint8_t commonLedOne, uint8_t commonLedTwo, uint8_t three, uint8_t four, uint8_t five, uint8_t six, uint8_t doubleLed) {
  led_pins[0] = commonLedOne;
  led_pins[1] = commonLedTwo;
  led_pins[2] = three;
  led_pins[3] = four;
  led_pins[4] = five;
  led_pins[5] = six;

  double_led_pin = doubleLed;

  for (byte i = 0; i < 6; ++i) {
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(double_led_pin, OUTPUT);
}

void LightHandler::setLightingMode(byte mode) {
  light_mode = mode;
}

void LightHandler::setMaxBrightness(int brightness) {
  max_brightness = brightness;
}

void LightHandler::setPulseInterval(int pulse_int) {
  pulse_interval = pulse_int;
}

void LightHandler::setReactiveCooldown(int react_cd) {
  reactive_cooldown = react_cd;
}

void LightHandler::key_down(uint8_t key_id) {
  
}

void LightHandler::lightingConstant() {
  int actual_brightness = (16.0 / 10.0) * max_brightness;
  
  digitalWrite(led_pins[0], LOW);
  digitalWrite(led_pins[1], LOW);
  analogWrite(double_led_pin, actual_brightness);
  
  for (byte i = 2; i < 6; ++i) {
    analogWrite(led_pins[i], actual_brightness);
  }
}

void LightHandler::lightingPulse() {
  int actual_brightness = pulseBaseValue + max_brightness * ((millis() - pulseLastMillis) / pulseInterval);
  float pulseStep = (millis() - pulseLastMillis) / pulseInterval * max_brightness;
  pulseValue += pulseWay * pulseStep;
  
  digitalWrite(led_pins[0], LOW);
  digitalWrite(led_pins[1], LOW);
  analogWrite(double_led_pin, actual_brightness);
  
  for (byte i = 2; i < 6; ++i) {
    analogWrite(led_pins[i], actual_brightness);
  }

  pulseLastMillis = millis();
}

void LightHandler::lightingReactive() {
  
}



