// Copyright: 2023 Jakub Korytko

#ifndef STACK_DATA_STUDENT_MY_STUDENT_H_
#define STACK_DATA_STUDENT_MY_STUDENT_H_

// To make the types in this header recognized by the IDE
#include <stdio.h>

void MY_STUDENT_Print(void *ptr);
void MY_STUDENT_Free(void *ptr);
int MY_STUDENT_Save(void **pdat, FILE *pf);
int MY_STUDENT_Read(void **pdat, FILE *pf);
void *MY_STUDENT_Push();
int MY_STUDENT_Compare(void *pCurData, void *pSearchData);
void *MY_STUDENT_SearchData();
void MY_STUDENT_SearchData_Free(void *searchDat);
enum MY_DATA_TYPE MY_STUDENT_GetType();

#endif  // STACK_DATA_STUDENT_MY_STUDENT_H_
