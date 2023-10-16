// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"
#include "src/stack/data_types.h"

#include "src/student/my_student.h"

struct MY_DATA_POINTERS MY_STUDENT__POINTERS = {
    .type = DATA_TYPE_MY_STUDENT,
    .fun_push = MY_STUDENT_Push,
    .fun_print = MY_STUDENT_Print,
    .fun_free = MY_STUDENT_Free,
    .fun_save = MY_STUDENT_Save,
    .fun_read = MY_STUDENT_Read,
    .fun_comp = MY_STUDENT_Compare,
    .fun_search_data = MY_STUDENT_SearchData,
    .fun_free_search_data = MY_STUDENT_SearchData_Free,
    .fun_get_type = MY_STUDENT_GetType
};

// add more (DATA_TYPE)__POINTERS here

const struct MY_DATA_POINTERS* MY_DATA_POINTERS_ARRAY[1] = {
    &MY_STUDENT__POINTERS,
    // include (DATA_TYPE)__POINTERS here (remember about the &)
    //
    // and change the size of MY_DATA_POINTERS_ARRAY
    // here but also in the data_types.h file
};

const char* custom_messages[] = {
    /* MY_STUDENT__MESSAGES */

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

    /* (DATA_TYPE)__MESSAGES */

    // (...)
};

// set type that interface should handle
const enum MY_DATA_TYPE interace_type = DATA_TYPE_MY_STUDENT;
