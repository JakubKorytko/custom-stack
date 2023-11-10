// Copyright: 2023 Jakub Korytko

#include "pch_source/stdafx.h"

#include "data_type_handlers/function_pointers.h"

static void SetFunctionPointers__From_array(struct MY_STACK *element,
                                            enum MY_DATA_TYPE type) {
  size_t element_size = sizeof(struct MY_DATA_POINTERS *);
  size_t array_size = sizeof(MY_DATA_POINTERS_ARRAY);
  size_t elements_count = array_size / element_size;

  if (type >= elements_count) {
    handle_error(ERROR__INVALID_DATA_TYPE, __FILE__, __LINE__);
    return;
  }

  (*element).ptr_fun_push = MY_DATA_POINTERS_ARRAY[type]->fun_push;

  (*element).ptr_fun_prnt = MY_DATA_POINTERS_ARRAY[type]->fun_print;

  (*element).ptr_fun_free = MY_DATA_POINTERS_ARRAY[type]->fun_free;

  (*element).ptr_fun_save = MY_DATA_POINTERS_ARRAY[type]->fun_save;

  (*element).ptr_fun_read = MY_DATA_POINTERS_ARRAY[type]->fun_read;

  (*element).ptr_fun_comp = MY_DATA_POINTERS_ARRAY[type]->fun_comp;

  (*element).ptr_fun_search_data =
      MY_DATA_POINTERS_ARRAY[type]->fun_search_data;

  (*element).ptr_fun_free_search_data =
      MY_DATA_POINTERS_ARRAY[type]->fun_free_search_data;

  (*element).ptr_fun_get_type = MY_DATA_POINTERS_ARRAY[type]->fun_get_type;
}

void SetFunctionPointers(struct MY_STACK *element, enum MY_DATA_TYPE type) {
  (*element).ptr_fun_push = NULL;
  (*element).ptr_fun_prnt = NULL;
  (*element).ptr_fun_free = NULL;
  (*element).ptr_fun_save = NULL;
  (*element).ptr_fun_read = NULL;
  (*element).ptr_fun_comp = NULL;
  (*element).ptr_fun_search_data = NULL;
  (*element).ptr_fun_free_search_data = NULL;
  (*element).ptr_fun_get_type = NULL;

  SetFunctionPointers__From_array(element, type);
  return;
}
