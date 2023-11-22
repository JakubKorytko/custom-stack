// Copyright: 2023 Jakub Korytko

#include "pch_source/stdafx.h"

#include "./general_config.h"
#include "./student_config.h"

#include "student/my_student.h"

const struct MY_DATA_POINTERS *MY_DATA_POINTERS_ARRAY[DATA_TYPE__TOTAL] = {
    &MY_STUDENT__POINTERS,
};

const char *custom_messages[] = {
    STUDENT_CONFIG_CUSTOM_MESSAGES
};

// set type that interface should handle
const enum MY_DATA_TYPE interface_type = DATA_TYPE__MY_STUDENT;
