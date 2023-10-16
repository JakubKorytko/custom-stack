// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"
#include "src/interface/my_messages.h"

const char* generic_messages[] = {
    "Unknown operation code\n",
    "\nStack is empty\n",
    "\nRead:\n\n",
    "\n",
    "\nFound: \n",
    "\nElement not found\n",
    "\nSelect options from the menu below:\n\n",
    "\nSelect: ",
    "\nSaved %u items to the file\n",
    "\nRead %u items from the file\n"
};


void generic_output(enum GENERIC_MESSAGES message) {
    printf_s(generic_messages[message]);
}

void output(enum CUSTOM_MESSAGES message) {
    printf_s(custom_messages[message]);
}
