// Macro.h

#ifndef _MACRO_h
#define _MACRO_h

#include "SimpleList.h"
#include "Action.h"
#include "SimpleAction.h"

class Macro : public Action{
	/*
	* Name of the macro
	*/
	char name[20];

	SimpleList<SimpleAction> actions;

	/*
	* 0 - Once
	* 1 - While pressed
	* 2 - Toggled
	*/
	byte repeatability;
};

#endif

