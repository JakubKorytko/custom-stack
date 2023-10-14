#include "src/pch_source/stdafx.h"

#include "src/stack/function_pointers.h"
#include "src/stack/data_types.h"

void SetFunctionPointers(enum MY_DATA_TYPE typ, PrintObject* pfunprint,
	FreeObject* pfunfree,
	Push* ptr_fun_push,
	IO_Object* pfunsave,
	IO_Object* pfunread,
	CompData* ptr_fun_comp,
	SearchData* fun_search_data,
	FreeSearchData* fun_free_search_data,
	GetObjectTyp* pfungettyp) {

	*ptr_fun_push = NULL;
	*pfunprint = NULL;
	*pfunfree = NULL;
	*pfunsave = NULL;
	*pfunread = NULL;
	*ptr_fun_comp = NULL;
	*fun_search_data = NULL;
	*fun_free_search_data = NULL;
	*pfungettyp = NULL;

	if (typ == DATA_TYPE_MY_STUDENT) {
		*ptr_fun_push = MY_STUDENT_Push;
		*pfunprint = MY_STUDENT_Print;
		*pfunfree = MY_STUDENT_Free;
		*pfunsave = MY_STUDENT_Save;
		*pfunread = MY_STUDENT_Read;
		*ptr_fun_comp = MY_STUDENT_Compare;
		*fun_search_data = MY_STUDENT_SearchData;
		*fun_free_search_data = MY_STUDENT_SearchData_Free;
		*pfungettyp = MY_STUDENT_GetType;
		return;
	}

	handle_error(ERROR__INVALID_DATA_TYPE, __FILE__, __LINE__);
	return;

}