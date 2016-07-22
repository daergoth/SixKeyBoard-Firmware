// Macro.h

#ifndef _MACRO_h
#define _MACRO_h

#include <SimpleList.h>
#include "Action.h"
#include "SimpleAction.h"

class Macro : public Action{
public:
	/*
	* Name of the macro
	*/
	char name[21];

	SimpleList<SimpleAction> actions;

	/*
	* 0 - Once
	* 1 - While pressed
	* 2 - Toggled
	*/
	byte repeatability = 0;
 

 Macro(char* n, byte num){

  for (byte i = 0; i < num; ++i) {
    name[i] = n[i];
  }
  
  action_type = 1; 
 }

 void addAction(SimpleAction a) {
  actions.push_back(a); 
 }

 void setRepeatability(byte r) {
  repeatability = r;
 }
 
};

#endif

