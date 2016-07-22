#include "KeyHandler.h"

byte KeyHandler::current_status[] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH };

Action* KeyHandler::current_macros[] = {0, 0, 0, 0, 0, 0};
byte KeyHandler::next_macro_step[] = {0, 0, 0, 0, 0, 0};
long KeyHandler::last_step_start_time[] = {0, 0, 0, 0, 0, 0};

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
      if ((input = (analogRead(key_pins[i]) < 512 ? HIGH : LOW)) != current_status[i]) {
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

void KeyHandler::handleMacros() {

  for (byte i = 0; i < 6; ++i) {
    if (current_macros[i] == 0)
      continue;

    Macro* m = static_cast<Macro*>(current_macros[i]);

    SimpleList<SimpleAction>::iterator current_step = m->actions.begin() + next_macro_step[i];

    switch (m->repeatability) {
      case 0:
        executeSimpleAction(current_step, i);
        
        if (current_step + 1 == m->actions.end()) {
          delete current_macros[i];
          current_macros[i] = 0;
          next_macro_step[i] = 0;
          last_step_start_time[i] = 0;
        } else {
          next_macro_step[i]++;
        }
        break;
      case 1:
        executeSimpleAction(current_step, i);
        
        if (current_step + 1 == m->actions.end()) {
          next_macro_step[i] = 0;
        } else {
          next_macro_step[i]++;
        }
        break;
      case 2:
        executeSimpleAction(current_step, i);
        
        if (current_step + 1 == m->actions.end()) {
          next_macro_step[i] = 0;
        } else {
          next_macro_step[i]++;
        }
        break;
    }
  }

}

void KeyHandler::pressed(uint8_t key_id, byte switch_status)
{
  Action* key_action = StorageHandler::getActionsForKey(key_id, switch_status);

  if (key_action->action_type == 0) {
    //SimpleAction

    SimpleAction* a = static_cast<SimpleAction*>(key_action);

    if(a->type == 1 || a->type == 3)
      a->type--;
    
    executeSimpleAction(a, 6);

    delete a;

  } else if (key_action->action_type == 1) {
    // Macro
    Macro* m = static_cast<Macro*>(key_action);

    // If Toggle macro pressed again, stop macro
    if (m->repeatability == 2) {
      for (byte i = 0; i < 6; ++i) {
        Macro* stored_macro = static_cast<Macro*>(current_macros[i]);

        if (strcmp(m->name, stored_macro->name) == 0) {
          delete current_macros[i];
          current_macros[i] = 0;
          next_macro_step[i] = 0;
          last_step_start_time[i] = 0;

          delete m;
          return;
        }
      }
    }

    // Search for free space and place macro
    for (byte i = 0; i < 6; ++i) {
      if (current_macros[i] == 0) {
        current_macros[i] = m;
        break;
      }
    }

  }

}

void KeyHandler::released(uint8_t key_id, byte switch_status)
{
  Action* key_action = StorageHandler::getActionsForKey(key_id, switch_status);

  if (key_action->action_type == 0) {
    //SimpleAction

    SimpleAction* a = static_cast<SimpleAction*>(key_action);

    if(a->type == 0 || a->type == 1)
      a->type++;
    
    executeSimpleAction(a, 6);

    delete a;
  }
  else if (key_action->action_type == 1) {
    // Macro
    Macro* m = static_cast<Macro*>(key_action);

    switch (m->repeatability) {
      case 0:
        // Once macro won't stop, if key is released
        // Do nothing.
        break;
      case 1:
        // While pressed macro stops on key release
        for (byte i = 0; i < 6; ++i) {
          Macro* stored_macro = static_cast<Macro*>(current_macros[i]);
          if (strcmp(m->name, stored_macro->name) == 0) {
            delete current_macros[i];
            current_macros[i] = 0;
            next_macro_step[i] = 0;
            last_step_start_time[i] = 0;
            break;
          }
        }
        break;
      case 2:
        // Toggle macro will stop on next key press
        // Do nothing.
        break;
    }

    delete m;

  }

}

void KeyHandler::executeSimpleAction(SimpleAction* simple_action, byte macro_num) {
  switch (simple_action->type) {
    case 0:
      // Keyboard press action
      Keyboard.press(simple_action->value);
      break;
    case 1:
      // Keyboard release action
      Keyboard.release(simple_action->value);
      break;
    case 2:
      //Mouse press action
      switch (simple_action->value) {
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
    case 3:
      // Mouse release action
      switch (simple_action->value) {
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
    case 4:
      // Mouse move action
      // Not implemented yet...
      break;
    case 5:
      // Delay action
      if (simple_action->value >= 50) {
        delay(simple_action->value);
      } else {
        if (last_step_start_time[macro_num] == 0) {
          last_step_start_time[macro_num] = millis();
        } else  {
          if (millis() - last_step_start_time[macro_num] < simple_action->value ) {
            next_macro_step[macro_num]--;
          } else {
            last_step_start_time[macro_num] = 0;            
          }
        }
      }
      break;
  }
}

