#include "KeyHandler.h"

byte KeyHandler::current_status[] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH };

uint8_t KeyHandler::key_pins[] = {0, 0, 0, 0, 0, 0};
uint8_t KeyHandler::switch_pin = 0;

void KeyHandler::setKeyPins(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six)
{
	key_pins[0] = one;
	key_pins[1] = two;
	key_pins[2] = three;
	key_pins[3] = four;
	key_pins[4] = five;
	key_pins[5] = six;

	for (short i = 0; i < 6; ++i) {
		if (key_pins[i] >= A0 && key_pins[i] <= A5) {
			pinMode(key_pins[i], INPUT);
			analogWrite(key_pins[i], 0);
		}
		else {
			pinMode(key_pins[i], INPUT_PULLUP);
		}
	}
}

void KeyHandler::setMappingSwitchPin(uint8_t sw)
{
	switch_pin = sw;

  pinMode(sw, INPUT);
  analogWrite(sw, 0);
}

void KeyHandler::handleInput()
{
	byte input = HIGH;
	byte sw = HIGH;
	if (switch_pin >= A0 && switch_pin <= A5) {
		sw = analogRead(switch_pin) > 512 ? HIGH : LOW;
	}
	else {
		sw = digitalRead(switch_pin);
	}

	for (byte i = 0; i < 6; ++i) {
		if (key_pins[i] >= A0 && key_pins[i] <= A5) {
			if ((input = (analogRead(key_pins[i])<512 ? HIGH : LOW)) != current_status[i]) {
				if (input == LOW) {
					pressed(i, sw);
				}
				else {
					released(i, sw);
				}
			}
		}
		else {
			if ((input = digitalRead(key_pins[i])) != current_status[i]) {
				if (input == LOW) {
					pressed(i, sw);
				}
				else {
					released(i, sw);
				}
			}
		}
		current_status[i] = input;
	}
}

void KeyHandler::pressed(uint8_t key_id, byte switch_status)
{
	Action* key_action = StorageHandler::getActionsForKey(key_id, switch_status);

  Serial.println(key_id);
  Serial.println(switch_status);
  Serial.println();
	
	if (key_action->action_type == 0) {
		//SimpleAction

		SimpleAction* a = static_cast<SimpleAction*>(key_action);

		switch (a->type) {
		case 0:
		case 1:
			Keyboard.press(a->value);
			break;
		case 2:
		case 3:
			switch (a->value) {
			case 0:
				Mouse.press(MOUSE_LEFT);
				break;
			case 1:
				Mouse.press(MOUSE_RIGHT);
				break;
			case 2:
				Mouse.press(MOUSE_MIDDLE);
				break;
			}
			break;
		}
		

	} else if (key_action->action_type == 1) {
		// Macro
		Macro* m = static_cast<Macro*>(key_action);

    switch (m->repeatability) {
    case 0:

      for (SimpleList<SimpleAction>::iterator itr = m->actions.begin(); itr != m->actions.end(); ++itr)
      {
        SimpleAction a = *itr;
  
        switch (a.type) {
        case 0:
        case 1:
          Keyboard.press(a.value);
          break;
        case 2:
        case 3:
          switch (a.value) {
          case 0:
            Mouse.press(MOUSE_LEFT);
            break;
          case 1:
            Mouse.press(MOUSE_RIGHT);
            break;
          case 2:
            Mouse.press(MOUSE_MIDDLE);
            break;
          }
          break;
        }
      }
      
      break;
    case 1:
      
      break;
    case 2:
      
      break;
    }
	}

  delete key_action;
}

void KeyHandler::released(uint8_t key_id, byte switch_status)
{
	Action* key_action = StorageHandler::getActionsForKey(key_id, switch_status);

	if (key_action->action_type == 0) {
		//SimpleAction

		SimpleAction* a = static_cast<SimpleAction*>(key_action);

		switch (a->type) {
		case 0:
		case 1:
			Keyboard.release(a->value);
			break;
		case 2:
		case 3:
			switch (a->value) {
			case 0:
				Mouse.release(MOUSE_LEFT);
				break;
			case 1:
				Mouse.release(MOUSE_RIGHT);
				break;
			case 2:
				Mouse.release(MOUSE_MIDDLE);
				break;
			}
			break;
		}


	}
	else if (key_action->action_type == 1) {
		// Macro

		Macro* m = static_cast<Macro*>(key_action);

    switch (m->repeatability) {
    case 0:

      for (SimpleList<SimpleAction>::iterator itr = m->actions.begin(); itr != m->actions.end(); ++itr)
      {
        SimpleAction a = *itr;
  
        switch (a.type) {
        case 0:
        case 1:
          Keyboard.release(a.value);
          break;
        case 2:
        case 3:
          switch (a.value) {
          case 0:
            Mouse.release(MOUSE_LEFT);
            break;
          case 1:
            Mouse.release(MOUSE_RIGHT);
            break;
          case 2:
            Mouse.release(MOUSE_MIDDLE);
            break;
          }
          break;
        }
      }
      
      break;
    case 1:
      
      break;
    case 2:
      
      break;
    }
	}

 delete key_action;
}
