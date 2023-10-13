#ifndef MY_INTERFACE__H
#define MY_INTERFACE__H

#include "src/stack/my_stack.h"

enum MY_INTERFACE_ENUM {
	INTERFACE_PUSH,
	INTERFACE_POP,
	INTERFACE_DISPLAY,
	INTERFACE_DISPLAY_TOP,
	INTERFACE_FIND,
	INTERFACE_SAVE,
	INTERFACE_READ,
	INTERFACE_CLEAR,
	INTERFACE_STOP,
	// (...)
	INTERFACE_TOTAL // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

void menu();
void stdin_clear();

// Internal functions, there is no need to declare them in the header file

/*

static void push(MY_DATA_TYPE type);

static void clear();

static void pop();

static void display();

static void displayTop();

static void find(MY_DATA_TYPE type);

static void save();

static void read();

*/

#endif // MY_INTERFACE__H