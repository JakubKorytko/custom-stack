// Copyright: 2023 Jakub Korytko

#ifndef SRC_INTERFACE_MY_MESSAGES_H_
#define SRC_INTERFACE_MY_MESSAGES_H_

typedef enum CUSTOM_MESSAGES CUSTOM_MESSAGES;

enum GENERIC_MESSAGES {
    MESSAGE__UNKNOWN_MENU_OPTION,
    MESSAGE__STACK_EMPTY,
    MESSAGE__STACK_ELEMENT_LOADED,
    MESSAGE__NEWLINE,
    MESSAGE__ELEMENT_FOUND,
    MESSAGE__ELEMENT_NOT_FOUND,
    MESSAGE__MENU,
    MESSAGE__MENU_INPUT,
    // (...)

    GENERIC_MESSAGES__TOTAL
    // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

void generic_output(enum GENERIC_MESSAGES message);
void output(enum CUSTOM_MESSAGES message);

extern const char* generic_messages[];
extern const char* custom_messages[];

#endif  // SRC_INTERFACE_MY_MESSAGES_H_
