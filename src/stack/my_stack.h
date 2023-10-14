// Copyright: 2023 Jakub Korytko

#ifndef SRC_STACK_MY_STACK_H_
#define SRC_STACK_MY_STACK_H_

#include "src/stack/data_types.h"
#include "src/stack/function_pointers.h"

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


struct MY_STACK* MY_STACK_GetTopElement();
size_t MY_STACK_GetStackLength();

// the size of reserved memory
// for records when writing and reading to/from a file
#define rec_type __int64
#define rec_size sizeof(rec_type)

extern const char STACK_DATA_FILENAME[];
extern const char FILE_WRITE_MODE[];
extern const char FILE_READ_MODE[];

#endif  // SRC_STACK_MY_STACK_H_
