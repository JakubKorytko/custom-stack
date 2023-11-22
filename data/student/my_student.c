// Copyright: 2023 Jakub Korytko
// LINT_C_FILE

#include "pch_source/stdafx.h"

#include "student/my_student.h"

// NOLINTNEXTLINE(build/include_order)
#include <string.h>  // must be included after stdafx.h

#include "student/my_student_input.h"

void MY_STUDENT_Print(void *ptr) {
  struct MY_STUDENT *p = (struct MY_STUDENT *)ptr;
  if (p) {
    printf_s(custom_messages[MESSAGE__MY_STUDENT__STUDENT_PRINT],
             p->student_surname, p->birth_year,
             fieldsOfStudyName[p->field_of_study], p->field_of_study);
  }
}

void MY_STUDENT_Free(void *ptr) {
  struct MY_STUDENT *pDat = (struct MY_STUDENT *)ptr;

  if (pDat) {
    if (pDat->student_surname) {
      free(pDat->student_surname);
      pDat->student_surname = NULL;
    }
    free(pDat);
    pDat = NULL;
  }
}

int MY_STUDENT_Save(void **pdat, FILE *pf) {
  if (pdat == NULL || *pdat == NULL || pf == NULL) {
    handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
    return 0;
  }

  struct MY_STUDENT *student = (struct MY_STUDENT *)*pdat;

  MY_STUDENT_Print(student);

  // saving the entire MY_STUDENT object
  if (fwrite(student, sizeof(struct MY_STUDENT), 1, pf) != 1) {
    handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    return 0;
  }

  // saving the student's name
  // we have to do it separately due to dynamic memory allocation
  // (we need to specify the length of the string and save it)
  if (!MY_STUDENT_SaveDynamicString(student->student_surname, pf)) {
    return 0;
  }

  return 1;
}

int MY_STUDENT_Read(void **pdat, FILE *pf) {
  if (pdat == NULL || pf == NULL) {
    handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
    return 0;
  }

  struct MY_STUDENT *pdata =
      (struct MY_STUDENT *)malloc(sizeof(struct MY_STUDENT));

  if (pdata == NULL) {
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    return 0;
  }

  // read the entire MY_STUDENT object
  if (fread(pdata, sizeof(struct MY_STUDENT), 1, pf) != 1) {
    handle_error(ERROR__FILE_READ, __FILE__, __LINE__);

    if (pdata->student_surname) {
      free(pdata->student_surname);
    }

    free(pdata);
    return -1;
  }

  pdata->student_surname = NULL;

  // reading the student's name
  // we need to do this separately due to dynamic memory allocation
  // (we need to read the text string and its length)
  if (!MY_STUDENT_ReadDynamicString(&(pdata->student_surname), pf)) {
    free(pdata);
    return -1;
  }

  *pdat = pdata;

  return 1;
}

void *MY_STUDENT_Push() {
  return MY_STUDENT_Input();
}

int MY_STUDENT_Compare(void *pCurData, void *pSearchData) {
  const struct MY_STUDENT *pcur = (struct MY_STUDENT *)pCurData;
  const struct MY_STUDENT *psearch = (struct MY_STUDENT *)pSearchData;

  if (strcmp(pcur->student_surname, psearch->student_surname) == 0) return 1;

  return 0;
}

void *MY_STUDENT_SearchData() {
  output(MESSAGE__MY_STUDENT__SURNAME_INPUT);
  char *surname = readSurname();

  if (!surname) {
    handle_error(ERROR__INVALID_INPUT, __FILE__, __LINE__);
    exit(0);
  }

  struct MY_STUDENT *searchDat =
      (struct MY_STUDENT *)malloc(sizeof(struct MY_STUDENT));

  if (!searchDat) {
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    exit(0);
  }

  size_t surname_len = strlen(surname) + 1;

  searchDat->student_surname = (char *)malloc(surname_len * sizeof(char));

  if (!searchDat->student_surname) {
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    exit(0);
  }

  strcpy_s(searchDat->student_surname, surname_len, surname);

  if (surname) free(surname);

  return searchDat;
}

void MY_STUDENT_SearchData_Free(void *searchDat) {
  if (((struct MY_STUDENT *)searchDat)->student_surname) {
    free(((struct MY_STUDENT *)searchDat)->student_surname);
  }
}

enum MY_DATA_TYPE MY_STUDENT_GetType() {
  return DATA_TYPE__MY_STUDENT;
}
