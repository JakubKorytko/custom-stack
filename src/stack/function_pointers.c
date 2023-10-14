// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"

#include "src/stack/function_pointers.h"
#include "src/stack/data_types.h"

static void SetFunctionPointers__From_array(enum MY_DATA_TYPE type) {

}

void SetFunctionPointers(struct MY_STACK* element, enum MY_DATA_TYPE type) {

    (*element).ptr_fun_push = NULL;
    (*element).ptr_fun_prnt = NULL;
    (*element).ptr_fun_free = NULL;
    (*element).ptr_fun_save = NULL;
    (*element).ptr_fun_read = NULL;
    (*element).ptr_fun_comp = NULL;
    (*element).fun_search_data = NULL;
    (*element).fun_free_search_data = NULL;
    (*element).ptr_fun_get_type = NULL;


    if (type == DATA_TYPE_MY_STUDENT) {
        (*element).ptr_fun_push = MY_STUDENT_Push;
        (*element).ptr_fun_prnt = MY_STUDENT_Print;
        (*element).ptr_fun_free = MY_STUDENT_Free;
        (*element).ptr_fun_save = MY_STUDENT_Save;
        (*element).ptr_fun_read = MY_STUDENT_Read;
        (*element).ptr_fun_comp = MY_STUDENT_Compare;
        (*element).fun_search_data = MY_STUDENT_SearchData;
        (*element).fun_free_search_data = MY_STUDENT_SearchData_Free;
        (*element).ptr_fun_get_type = MY_STUDENT_GetType;
        return;
    }

    handle_error(ERROR__INVALID_DATA_TYPE, __FILE__, __LINE__);
    return;
}