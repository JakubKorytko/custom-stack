// Copyright: 2023 Jakub Korytko

#ifndef SRC_INTERFACE_MY_INTERFACE_H_
#define SRC_INTERFACE_MY_INTERFACE_H_

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

  INTERFACE_TOTAL
  // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

void menu();

#endif  // SRC_INTERFACE_MY_INTERFACE_H_
