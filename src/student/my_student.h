// Copyright: 2023 Jakub Korytko

#ifndef SRC_STUDENT_MY_STUDENT_H_
#define SRC_STUDENT_MY_STUDENT_H_

#include <stdio.h>

enum FIELDS_OF_STUDY {
    Computer_Science,
    Mathematics,
    Engineer,
    Physics,
    Chemistry,
    // (...)
    FIELDS_OF_STUDY_TOTAL  // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

struct MY_STUDENT {
    char* student_surname;
    int birth_year;
    enum FIELDS_OF_STUDY field_of_study;
};

void* MY_STUDENT_Init(char* surname, int rok,
enum FIELDS_OF_STUDY field_of_study);

void MY_STUDENT_Free(void* ptr);
void* MY_STUDENT_Push();
void MY_STUDENT_Print(void* ptr);
int MY_STUDENT_Compare(void* pCurData, void* pSearchData);
int MY_STUDENT_Save(void** pdat, FILE* pf);
int MY_STUDENT_Read(void** pdat, FILE* pf);
void* MY_STUDENT_Input();
void* MY_STUDENT_SearchData();
void MY_STUDENT_SearchData_Free(void* searchDat);
enum MY_DATA_TYPE MY_STUDENT_GetType();

#endif  // SRC_STUDENT_MY_STUDENT_H_
