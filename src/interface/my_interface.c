// Copyright: 2023 Jakub Korytko

#include "pch_source/stdafx.h"

#include "interface/my_interface.h"

#include "stack/my_stack.h"

static void stdin_clear() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) continue;
}

static const char *menu_options[] = {"0 - push",
                                     "1 - pop",
                                     "2 - print stack",
                                     "3 - print top element",
                                     "4 - find",
                                     "5 - save to disk",
                                     "6 - read from disk",
                                     "7 - clear",
                                     "8 - finish"};

static void push(enum MY_DATA_TYPE type) {
  struct MY_STACK *tmp = (struct MY_STACK *)malloc(sizeof(struct MY_STACK));

  if (!tmp) {
    MY_STACK_Free();
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    return;
  }

  SetFunctionPointers(tmp, type);

  tmp->type = type;

  if (!tmp->ptr_fun_push) {
    if (tmp) {
      free(tmp);
    }

    handle_error(ERROR__UNKNOWN, __FILE__, __LINE__);
    return;
  }

  tmp->pData = (*tmp->ptr_fun_push)();

  if (!MY_STACK_Push(tmp)) {
    handle_error(ERROR__UNKNOWN, __FILE__, __LINE__);
    return;
  }
}

static void pop() {
  struct MY_STACK tmp = MY_STACK_Pop();

  if (tmp.pData) {
    (tmp.ptr_fun_prnt)(tmp.pData);
    (tmp.ptr_fun_free)(tmp.pData);
  }
}

static void find(enum MY_DATA_TYPE type) {
  int found = 0;
  struct MY_STACK *tmp = (struct MY_STACK *)malloc(sizeof(struct MY_STACK));

  if (!tmp) {
    MY_STACK_Free();
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    return;
  }

  SetFunctionPointers(tmp, type);

  if (!*tmp->ptr_fun_free_search_data) {
    if (tmp) {
      free(tmp);
    }

    handle_error(ERROR__UNKNOWN, __FILE__, __LINE__);
    return;
  }

  void *searchDat = (*tmp->ptr_fun_search_data)();

  // make a first search
  void *pDat = MY_STACK_Search(searchDat, (*tmp->ptr_fun_comp), 1);

  if (pDat) {
    found = 1;
    generic_output(MESSAGE__ELEMENT_FOUND);
    (*tmp->ptr_fun_prnt)(pDat);
  }

  while (pDat) {
    pDat = MY_STACK_Search(searchDat, (*tmp->ptr_fun_comp), 0);

    if (pDat) {
      found = 1;
      generic_output(MESSAGE__ELEMENT_FOUND);
      (*tmp->ptr_fun_prnt)(pDat);
    }
  }

  (*tmp->ptr_fun_free_search_data)(searchDat);

  if (tmp) {
    free(tmp);
  }

  if (!found) {
    generic_output(MESSAGE__ELEMENT_NOT_FOUND);
  }
}

static void save() {
  MY_STACK_Save();
}

static void read() {
  MY_STACK_Read();
}

static void display() {
  MY_STACK_Display();
}

static void displayTop() {
  MY_STACK_Display_Top();
}

static void clear() {
  MY_STACK_Free();
}

void menu() {
  MY_STACK_Init(&SetFunctionPointers);

  size_t option = 0;
  while (option >= INTERFACE_PUSH && option <= INTERFACE_STOP) {
    generic_output(MESSAGE__MENU);

    for (size_t it = 0; it < INTERFACE_TOTAL; ++it) {
      printf("%s\n", menu_options[it]);
    }

    generic_output(MESSAGE__MENU_INPUT);

    scanf_s("%zu", &option);
    stdin_clear();

    switch (option) {
      case INTERFACE_PUSH:
        push(interace_type);
        break;
      case INTERFACE_POP:
        pop();
        break;
      case INTERFACE_DISPLAY:
        display();
        break;
      case INTERFACE_DISPLAY_TOP:
        displayTop();
        break;
      case INTERFACE_FIND:
        find(interace_type);
        break;
      case INTERFACE_SAVE:
        save();
        break;
      case INTERFACE_READ:
        read();
        break;
      case INTERFACE_CLEAR:
        clear();
        break;
      case INTERFACE_STOP:
        clear();
        return;
      default:
        generic_output(MESSAGE__UNKNOWN_MENU_OPTION);
    }
  }
}
