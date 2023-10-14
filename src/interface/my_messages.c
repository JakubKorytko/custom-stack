// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"
#include "src/interface/my_messages.h"

#include <stdarg.h>

static const char* custom_messages[] = {
    "Unknown operation code\n",
    "Enter student name: ",
    "\nList of fields of study:\n",
    "Enter year of birth of student: ",
    "\n\nSelect a field of study from the list above: ",

    // notice the lack of commas between the strings
    // this is because its only one string,
    // but split into multiple lines
    "\n"
    "--- STUDENT ---\n"
    "Student's name: %s\n"
    "Year of birth: %u\n"
    "Field of study: %s (%d)\n"
    "---"
    "\n",

    "\nStack is empty\n",
    "Read:\n\n",
    "\n",
    "\nFound: \n",
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
