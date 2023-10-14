#include "src/pch_source/stdafx.h"
#include "src/stack/data_types.h"

#include "src/student/my_student.h"

struct MY_DATA_POINTERS MY_STUDENT__POINTERS = {
    .typ = DATA_TYPE_MY_STUDENT,
    .ptr_fun_push = &MY_STUDENT_Push,
    .pfunprint = &MY_STUDENT_Print,
    .pfunfree = &MY_STUDENT_Free,
    .pfunsave = &MY_STUDENT_Save,
    .pfunread = &MY_STUDENT_Read,
    .ptr_fun_comp = &MY_STUDENT_Compare,
    .fun_search_data = &MY_STUDENT_SearchData,
    .fun_free_search_data = &MY_STUDENT_SearchData_Free,
    .pfungettyp = &MY_STUDENT_GetType
};

const struct MY_DATA_POINTERS* MY_DATA_POINTERS_ARRAY[1] = {
    &MY_STUDENT__POINTERS
};
