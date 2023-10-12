#ifndef MY_STACK__H
#define MY_STACK__H

enum MY_DATA_TYPE
{
	DATA_TYPE_MY_STUDENT,
	// (...)
	DATA_TYPE_TOTAL // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

typedef int (*CompData)(void* pcurData, void* pSearchData); // Type definition: pointer to a function with a prototype int NazwaFunkcji(void *, void *);
typedef void (*PrintObject)(void* pdat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef void (*FreeObject)(void* pdat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef int (*IO_Object)(void** pdat, FILE* pf); // Type definition: pointer to a function with a prototype int NazwaFunkcji(void**, FILE*);
typedef void (*FreeSearchData)(void* searchDat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef void* (*SearchData)(); // Type definition: pointer to a function with a prototype void* NazwaFunkcji();
typedef void* (*Push)(); // Type definition: pointer to a function with a prototype void* NazwaFunkcji();
typedef enum MY_DATA_TYPE(*GetObjectTyp)(void* pdat); // Type definition: pointer to a function with a prototype MY_DATA_TYPE NazwaFunkcji(void*);

typedef void (*GetFuncPtr)(
	enum MY_DATA_TYPE typ,
	PrintObject* pfunprint,
	FreeObject* pfunfree,
	Push* ptr_fun_push,
	IO_Object* pfunsave,
	IO_Object* pfunread,
	CompData*  ptr_fun_comp,
	SearchData*  fun_search_data,
	FreeSearchData* fun_free_search_data,
	GetObjectTyp* pfungettyp
	);

struct MY_STACK {
	void* pData;
	enum MY_DATA_TYPE typ;	// data type
	PrintObject ptr_fun_prnt;   // pointer to a function that prints a data object
	FreeObject  ptr_fun_free;   // pointer to a function from the data handler that frees memory
	IO_Object  ptr_fun_save;    // pointer to a function from the data handler that saves the object to a file
	IO_Object  ptr_fun_read;    // pointer to a function from data handling that reads an object from a file
	Push ptr_fun_push; // pointer to a function from the data handler that retrieves a new object
	CompData  ptr_fun_comp; // pointer to a function from the data handler that compares two objects with each other
	SearchData  fun_search_data; // pointer to a function from the data handler that prepares an object for comparison
	FreeSearchData fun_free_search_data; // pointer to the function from the data handler that frees the comparison object
	GetObjectTyp ptr_fun_get_type; // pointer to a function from the data handler that returns the object type
	struct MY_STACK* next;
};

void MY_STACK_Init(GetFuncPtr ptr);
void MY_STACK_Free();
struct MY_STACK* MY_STACK_Push(struct MY_STACK* pdat);
struct MY_STACK MY_STACK_Pop();
void MY_STACK_Display();
void MY_STACK_Display_Top();
void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry);
void MY_STACK_SetFuncPointers(GetFuncPtr ptr);
void MY_STACK_Save();
void MY_STACK_Read();

#endif // MY_STACK__H