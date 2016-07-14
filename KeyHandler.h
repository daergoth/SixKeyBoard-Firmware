// KeyHandler.h

#ifndef _KEYHANDLER_h
#define _KEYHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keyboard.h>
#include <Mouse.h>

#include "Action.h"
#include "SimpleAction.h"
#include "Macro.h"
#include "StorageHandler.h"

class KeyHandler {

public:
	static void setKeyPins(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six);
	static void setMappingSwitchPin(uint8_t sw);
	static void handleInput();

private:
	static uint8_t key_pins[6];
	static uint8_t switch_pin;
	static byte current_status[6];

	static void pressed(uint8_t key_num, byte switch_status);
	static void released(uint8_t key_num, byte switch_status);
};

#endif

