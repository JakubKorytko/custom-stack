// Copyright: 2023 Jakub Korytko

#ifndef SRC_STACK_DATA_TYPES_H_
#define SRC_STACK_DATA_TYPES_H_

#include "src/student/my_student.h"
#include "src/stack/function_pointers.h"

struct MY_STACK {
    void* pData;

    // data type
    enum MY_DATA_TYPE typ;

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
    SearchData  fun_search_data;

    // pointer to the function from the data handler
    // that frees the comparison object
    FreeSearchData fun_free_search_data;

    // pointer to a function from the data handler
    // that returns the object type
    GetObjectTyp ptr_fun_get_type;

    struct MY_STACK* next;
};

struct MY_DATA_POINTERS {
    enum MY_DATA_TYPE typ;
    PrintObject* pfunprint;
    FreeObject* pfunfree;
    Push* ptr_fun_push;
    IO_Object* pfunsave;
    IO_Object* pfunread;
    CompData* ptr_fun_comp;
    SearchData* fun_search_data;
    FreeSearchData* fun_free_search_data;
    GetObjectTyp* pfungettyp;
};

enum MY_DATA_TYPE
{
    DATA_TYPE_MY_STUDENT,
    // (...)

    DATA_TYPE_TOTAL
    // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};


extern const struct MY_DATA_POINTERS* MY_DATA_POINTERS_ARRAY[1];

#endif  // SRC_STACK_DATA_TYPES_H_
