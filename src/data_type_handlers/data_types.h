// Copyright: 2023 Jakub Korytko

#ifndef SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_
#define SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_

// To make the types in this header recognized by the IDE
#include "src/data_type_handlers/function_pointers.h"

struct MY_STACK {
    void* pData;

    // data type
    enum MY_DATA_TYPE type;

    // pointer to a function
    // that prints a data object
    PrintObject ptr_fun_prnt;

    // pointer to a function from the data handler
    // that frees memory
    FreeObject  ptr_fun_free;

    // pointer to a function from the data handler
    // that saves the object to a file
    IO_Object  ptr_fun_save;

    // pointer to a function from data handling
    // that reads an object from a file
    IO_Object  ptr_fun_read;

    // pointer to a function from the data handler
    // that retrieves a new object
    Push ptr_fun_push;

    // pointer to a function from the data handler
    // that compares two objects with each other
    CompData  ptr_fun_comp;

    // pointer to a function from the data handler
    // that prepares an object for comparison
    SearchData  ptr_fun_search_data;

    // pointer to the function from the data handler
    // that frees the comparison object
    FreeSearchData ptr_fun_free_search_data;

    // pointer to a function from the data handler
    // that returns the object type
    GetObjectTyp ptr_fun_get_type;

    struct MY_STACK* next;
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
    GetObjectTyp fun_get_type;
};

enum MY_DATA_TYPE {
    DATA_TYPE_MY_STUDENT,
    // add more data types here
    // (...)

    DATA_TYPE_TOTAL
    // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

enum CUSTOM_MESSAGES {
    MESSAGE__SURNAME_INPUT,
    MESSAGE__STUDY_FIELD_LIST,
    MESSAGE__BIRTHDAY_INPUT,
    MESSAGE__STUDY_FIELD_INPUT,
    MESSAGE__STUDENT_PRINT,
    // add more custom_messages enum variables that points to the
    // custom_messages (data_types.c) values
    // (...)

    CUSTOM_MESSAGES__TOTAL
    // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

extern const struct MY_DATA_POINTERS* MY_DATA_POINTERS_ARRAY[1];
extern const enum MY_DATA_TYPE interace_type;

#endif  // SRC_DATA_TYPE_HANDLERS_DATA_TYPES_H_
