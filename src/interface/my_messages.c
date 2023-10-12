#include "src/pch_source/stdafx.h"

#include <stdarg.h>

static const char* custom_messages[] = {
	"Unknown operation code\n",
	"Enter student name: ",
	"\nList of fields of study:\n",
	"Enter year of birth of student: ",
	"\n\nSelect a field of study from the list above: ",
	"\n--- STUDENT ---\nStudent's name: %s\nYear of birth: %u\nField of study: %s (%d)\n---\n",
	"\nStack is empty\n",
	"Read:\n\n",
	"\n",
	"\Found: \n",
	"\nElement not found\n",
	"\nSelect options from the menu below:\n\n",
	"\nSelect: "
};


void output(enum CUSTOM_MESSAGES message) {
	printf_s(custom_messages[message]);
}

void foutput(enum CUSTOM_MESSAGES message, ...) {
	va_list valist;
	va_start(valist, message);
	vprintf_s(custom_messages[message], valist);
	va_end(valist);
}