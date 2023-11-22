// Copyright: 2023 Jakub Korytko

#ifndef SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_
#define SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_

// To make the types in this header recognized by the IDE
#include "data_type_handlers/function_pointers.h"
#include "./general_config.h"

struct MY_STACK {
  void *pData;

  // data type
  enum MY_DATA_TYPE type;

  // pointer to a function
  // that prints a data object
  PrintObject ptr_fun_prnt;

  // pointer to a function from the data handler
  // that frees memory
  FreeObject ptr_fun_free;

  // pointer to a function from the data handler
  // that saves the object to a file
  IO_Object ptr_fun_save;

  // pointer to a function from data handling
  // that reads an object from a file
  IO_Object ptr_fun_read;

  // pointer to a function from the data handler
  // that retrieves a new object
  Push ptr_fun_push;

  // pointer to a function from the data handler
  // that compares two objects with each other
  CompData ptr_fun_comp;

  // pointer to a function from the data handler
  // that prepares an object for comparison
  SearchData ptr_fun_search_data;

  // pointer to the function from the data handler
  // that frees the comparison object
  FreeSearchData ptr_fun_free_search_data;

  // pointer to a function from the data handler
  // that returns the object type
  GetObjectType ptr_fun_get_type;

  struct MY_STACK *next;
};

struct MY_DATA_POINTERS {
  enum MY_DATA_TYPE type;
  PrintObject fun_print;
  FreeObject fun_free;
  Push fun_push;
  IO_Object fun_save;
  IO_Object fun_read;
  CompData fun_comp;
  SearchData fun_search_data;
  FreeSearchData fun_free_search_data;
  GetObjectType fun_get_type;
};

extern const enum MY_DATA_TYPE interface_type;

extern const struct MY_DATA_POINTERS *MY_DATA_POINTERS_ARRAY[DATA_TYPE__TOTAL];

#endif  // SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_
