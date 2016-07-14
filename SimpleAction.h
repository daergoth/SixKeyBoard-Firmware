#ifndef _SIMPLEACTION_h
#define _SIMPLEACTION_h

#include "Action.h"

class SimpleAction : public Action{
public:

	/*
	* 0 - Keyboard Press action 
	* 1 - Keyboard Release action
	* 2 - Mouse Press action
	* 3 - Mouse Release action
	* 4 - Mouse Move action ?
 *  5 - Delay
	*/
	byte type;

	/*
	* If type 0 or 1: 
	*	ASCII code or special key code
  * 
	* If type 2 or 3: 
	*	0 - Left mouse button
	*	1 - Right mouse button
	*	2 - Middle mouse button
  * 
  * If type 5:
  * Number of milliseconds delay
	*/
	byte value;

 SimpleAction():type(0), value(0){  
  action_type = 0; 
 }

 SimpleAction(byte t, byte v):type(t), value(v){  
  action_type = 0; 
 }
 
};

#endif
