#ifndef FUNCTION_POINTERS__H
#define FUNCTION_POINTERS__H

typedef int (*CompData)(void* pcurData, void* pSearchData); // Type definition: pointer to a function with a prototype int NazwaFunkcji(void *, void *);
typedef void (*PrintObject)(void* pdat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef void (*FreeObject)(void* pdat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef int (*IO_Object)(void** pdat, FILE* pf); // Type definition: pointer to a function with a prototype int NazwaFunkcji(void**, FILE*);
typedef void (*FreeSearchData)(void* searchDat); // Type definition: pointer to a function with a prototype void NazwaFunkcji(void*);
typedef void* (*SearchData)(); // Type definition: pointer to a function with a prototype void* NazwaFunkcji();
typedef void* (*Push)(); // Type definition: pointer to a function with a prototype void* NazwaFunkcji();
typedef enum MY_DATA_TYPE(*GetObjectTyp)(); // Type definition: pointer to a function with a prototype MY_DATA_TYPE NazwaFunkcji();

typedef void (*GetFuncPtr)(
	enum MY_DATA_TYPE typ,
	PrintObject* pfunprint,
	FreeObject* pfunfree,
	Push* ptr_fun_push,
	IO_Object* pfunsave,
	IO_Object* pfunread,
	CompData* ptr_fun_comp,
	SearchData* fun_search_data,
	FreeSearchData* fun_free_search_data,
	GetObjectTyp* pfungettyp
	);

void SetFunctionPointers(enum MY_DATA_TYPE typ, PrintObject* pfunprint,
	FreeObject* pfunfree,
	Push* ptr_fun_push,
	IO_Object* pfunsave,
	IO_Object* pfunread,
	CompData* ptr_fun_comp,
	SearchData* fun_search_data,
	FreeSearchData* fun_free_search_data,
	GetObjectTyp* pfungettyp
);

#endif // FUNCTION_POINTERS__H