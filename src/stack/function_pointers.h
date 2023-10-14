// Copyright: 2023 Jakub Korytko

#ifndef SRC_STACK_FUNCTION_POINTERS_H_
#define SRC_STACK_FUNCTION_POINTERS_H_

// Type definition: pointer to
// a function with a prototype int Function(void *, void *);
typedef int (*CompData)(void* pcurData, void* pSearchData);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*PrintObject)(void* pdat);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*FreeObject)(void* pdat);

// Type definition: pointer to
// a function with a prototype int Function(void**, FILE*);
typedef int (*IO_Object)(void** pdat, FILE* pf);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*FreeSearchData)(void* searchDat);

// Type definition: pointer to
// a function with a prototype void* Function();
typedef void* (*SearchData)();

// Type definition: pointer to
// a function with a prototype void* Function();
typedef void* (*Push)();

// Type definition: pointer to
// a function with a prototype MY_DATA_TYPE Function();
typedef enum MY_DATA_TYPE(*GetObjectTyp)();

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

#endif  // SRC_STACK_FUNCTION_POINTERS_H_
