// Copyright: 2023 Jakub Korytko

#ifndef SRC_DATA_TYPE_HANDLERS_FUNCTION_POINTERS_H_
#define SRC_DATA_TYPE_HANDLERS_FUNCTION_POINTERS_H_

// Type definition: pointer to
// a function with a prototype int Function(void *, void *);
typedef int (*CompData)(void *pcurData, void *pSearchData);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*PrintObject)(void *pdat);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*FreeObject)(void *pdat);

// Type definition: pointer to
// a function with a prototype int Function(void**, FILE*);
typedef int (*IO_Object)(void **pdat, FILE *pf);

// Type definition: pointer to
// a function with a prototype void Function(void*);
typedef void (*FreeSearchData)(void *searchDat);

// Type definition: pointer to
// a function with a prototype void* Function();
typedef void *(*SearchData)();

// Type definition: pointer to
// a function with a prototype void* Function();
typedef void *(*Push)();

// Type definition: pointer to
// a function with a prototype MY_DATA_TYPE Function();
typedef enum MY_DATA_TYPE (*GetObjectType)();

typedef void (*GetFuncPtr)(struct MY_STACK *element, enum MY_DATA_TYPE type);

void SetFunctionPointers(struct MY_STACK *element, enum MY_DATA_TYPE type);

#endif  // SRC_DATA_TYPE_HANDLERS_FUNCTION_POINTERS_H_
