#include "src/pch_source/stdafx.h"

#include "src/stack/my_stack.h"
#include "src/student/my_student.h"
#include "src/interface/my_interface.h"

static const char *strtab[] =
{
	"0 - push",
	"1 - pop",
	"2 - print stack",
	"3 - print top element",
	"4 - find by lastname",
	"5 - save to disk",
	"6 - read from disk",
	"7 - clear",
	"8 - finish"
};

static void push(enum MY_DATA_TYPE type) {
	
	struct MY_STACK* tmp = (struct MY_STACK*)malloc(sizeof(struct MY_STACK));

	if (!tmp) {
		handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
		return;
	}

	SetFunctionPointers(type, &tmp->ptr_fun_prnt,
		&tmp->ptr_fun_free, &tmp->ptr_fun_push, &tmp->ptr_fun_save, &tmp->ptr_fun_read,
		&tmp->ptr_fun_comp, &tmp->fun_search_data, &tmp->fun_free_search_data,
		&tmp->ptr_fun_get_type);

	tmp->typ = type;
	tmp->pData = (*tmp->ptr_fun_push)();

	if (!MY_STACK_Push(tmp)) {
		handle_error(ERROR__UNKNOWN, __FILE__, __LINE__);
		return;
	}

}

static void pop()
{
	struct MY_STACK tmp = MY_STACK_Pop();
	(tmp.ptr_fun_prnt)(tmp.pData);
	(tmp.ptr_fun_free)(tmp.pData);
}

static void find(enum MY_DATA_TYPE type)
{

	int found = 0;
	struct MY_STACK* tmp = (struct MY_STACK*)malloc(sizeof(struct MY_STACK));

	if (!tmp) {
		handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
		return;
	}

	SetFunctionPointers(type, &tmp->ptr_fun_prnt,
		&tmp->ptr_fun_free, &tmp->ptr_fun_push, &tmp->ptr_fun_save, &tmp->ptr_fun_read,
		&tmp->ptr_fun_comp, &tmp->fun_search_data, &tmp->fun_free_search_data,
		&tmp->ptr_fun_get_type);

	void* searchDat = (*tmp->fun_search_data)();

	void* pDat = MY_STACK_Search(searchDat, (*tmp->ptr_fun_comp), 1); //make a first search

	if (pDat)
	{
		found = 1;
		output(MESSAGE__ELEMENT_FOUND);
		(*tmp->ptr_fun_prnt)(pDat);
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(searchDat, (*tmp->ptr_fun_comp), 0);
		if (pDat)
		{
			found = 1;
			output(MESSAGE__ELEMENT_FOUND);
			(*tmp->ptr_fun_prnt)(pDat);
		}
	}

	(*tmp->fun_free_search_data)(searchDat);

	if (tmp) {
		free(tmp);
	}

	if (!found) {
		output(MESSAGE__ELEMENT_NOT_FOUND);
	}

}

static void save()
{
	MY_STACK_Save();
}

static void read()
{
	MY_STACK_Read();
}

static void display() {
	MY_STACK_Display();
}

static void displayTop() {
	MY_STACK_Display_Top();
}

static void clear() {
	MY_STACK_Free();
}

void menu() {

	MY_STACK_Init(SetFunctionPointers);

	size_t op = 0;
	while (op >= INTERFACE_PUSH && op <= INTERFACE_STOP)
	{
		size_t it;

		output(MESSAGE__MENU);

		for (it = 0; it < INTERFACE_TOTAL; ++it) {
			printf("%s\n", strtab[it]);
		}

		output(MESSAGE__MENU_INPUT);

		scanf_s("%zu", &op);
		stdin_clear();
		switch (op)
		{
		case INTERFACE_PUSH: push(DATA_TYPE_MY_STUDENT);
			break;
		case INTERFACE_POP: pop();
			break;
		case INTERFACE_DISPLAY: display();
			break;
		case INTERFACE_DISPLAY_TOP: displayTop();
			break;
		case INTERFACE_FIND: find(DATA_TYPE_MY_STUDENT);
			break;
		case INTERFACE_SAVE: save();
			break;
		case INTERFACE_READ: read();
			break;
		case INTERFACE_CLEAR: clear();
			break;
		case INTERFACE_STOP: clear();
			return;
		default:
			output(MESSAGE__UNKNOWN_MENU_OPTION);
		};

	}

}

void SetFunctionPointers(enum MY_DATA_TYPE typ, PrintObject* pfunprint,
	FreeObject* pfunfree,
	Push* ptr_fun_push,
	IO_Object* pfunsave,
	IO_Object* pfunread,
	CompData*  ptr_fun_comp,
	SearchData*  fun_search_data,
	FreeSearchData* fun_free_search_data,
	GetObjectTyp* pfungettyp) {

	*pfunprint = NULL;
	*pfunfree = NULL;
	*pfunsave = NULL;
	*pfunread = NULL;
	*ptr_fun_comp = NULL;
	*fun_search_data = NULL;
	*fun_free_search_data = NULL;
	*pfungettyp = NULL;

	switch (typ) {
	case DATA_TYPE_MY_STUDENT:
		*ptr_fun_push = MY_STUDENT_Push;
		*pfunprint = MY_STUDENT_Print;
		*pfunfree = MY_STUDENT_Free;
		*pfunsave = MY_STUDENT_Save;
		*pfunread = MY_STUDENT_Read;
		*ptr_fun_comp = MY_STUDENT_Compare;
		*fun_search_data = MY_STUDENT_SearchData;
		*fun_free_search_data = MY_STUDENT_SearchData_Free;
		*pfungettyp = MY_STUDENT_GetType;
		break;
	// case DATA_TYPE_:
	// (...)
	default:
		handle_error(ERROR__INVALID_DATA_TYPE, __FILE__, __LINE__);
		return;
	}

}

void stdin_clear()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
};
