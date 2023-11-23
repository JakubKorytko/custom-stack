// Copyright: 2023 Jakub Korytko

#include "pch_source/stdafx.h"

#include "config/student_config.h"

#include "student/my_student.h"

struct MY_DATA_POINTERS MY_STUDENT__POINTERS = {
    .type = DATA_TYPE__MY_STUDENT,
    .fun_print = MY_STUDENT_Print,
    .fun_free = MY_STUDENT_Free,
    .fun_save = MY_STUDENT_Save,
    .fun_read = MY_STUDENT_Read,
    .fun_push = MY_STUDENT_Push,
    .fun_comp = MY_STUDENT_Compare,
    .fun_search_data = MY_STUDENT_SearchData,
    .fun_free_search_data = MY_STUDENT_SearchData_Free,
    .fun_get_type = MY_STUDENT_GetType};
