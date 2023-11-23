#include "pch_source/stdafx.h"

#include "student/my_student_input.h"

// NOLINTNEXTLINE(build/include_order)
#include <string.h>  // must be included after stdafx.h

const char *fieldsOfStudyName[] = {"Computer Science", "Mathematics",
                                   "Engineer", "Physics", "Chemistry"};

static void *MY_STUDENT_Init(char *surname, int year,
                             enum FIELDS_OF_STUDY field_of_study) {
  struct MY_STUDENT *pdata;
  pdata = (struct MY_STUDENT *)malloc(sizeof(struct MY_STUDENT));

  if (pdata) {
    if (surname) {
      size_t pdata_length = strlen(surname) + 1;

      pdata->student_surname = (char *)malloc(pdata_length * sizeof(char));
      if (pdata->student_surname) {
        strncpy_s(pdata->student_surname, pdata_length, surname,
                  strlen(surname));
      }
    } else {
      pdata->student_surname = NULL;
    }
    pdata->field_of_study = field_of_study;
    pdata->birth_year = year;

    if (surname) {
      free(surname);
    }

    surname = NULL;

    return (void *)pdata;
  } else {
    if (surname) {
      free(surname);
    }

    surname = NULL;

    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    return NULL;
  }
}

void stdin_clear() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) continue;
}

char *readSurname() {
  // function that shortens allocated memory to the maximum length needed
  char *buff;
  size_t buff_len = 0;

  while (buff_len <= 1) {
    buff = (char *)malloc(MAX_SURNAME_SIZE * sizeof(char));

    if (!buff) {
      handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
      return NULL;
    }

    fgets(buff, MAX_SURNAME_SIZE, stdin);

    buff_len = strlen(buff);

    if (buff_len > 1) {
      break;
    }

    if (buff) {
      free(buff);
    }
  }

  if (buff_len > 0 && buff[buff_len - 1] == '\n') {
    buff[buff_len - 1] = '\0';
  }

  size_t surname_len = (buff_len + 1);

  char *surname = (char *)malloc(surname_len * sizeof(char));

  if (!surname) {
    if (buff) {
      free(buff);
    }
    handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    return NULL;
  }

  if (strcpy_s(surname, surname_len, buff) != 0) {
    if (buff) {
      free(buff);
    }

    if (surname) {
      free(surname);
    }

    return NULL;
  }

  if (buff) {
    free(buff);
  }

  return surname;
}

int MY_STUDENT_SaveDynamicString(const char *str, FILE *pf) {
  if (str == NULL || pf == NULL) {
    handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
    return 0;
  }

  size_t length = strlen(str);

  // saving the length of the string
  if (fwrite(&length, sizeof(size_t), 1, pf) != 1) {
    handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    return 0;
  }

  // saving the string
  if (length <= 0 || fwrite(str, sizeof(char), length, pf) != length) {
    handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    return 0;
  }

  return 1;
}

int MY_STUDENT_ReadDynamicString(char **str, FILE *pf) {
  if (str == NULL || pf == NULL) {
    handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
    return 0;
  }

  size_t length = 0;

  if (fread(&length, sizeof(size_t), 1, pf) != 1) {
    if (feof(pf)) {
      return 0;
    } else {
      handle_error(ERROR__FILE_READ, __FILE__, __LINE__);
      return -1;
    }
  }

  *str = NULL;

  if (length > 0) {
    *str = (char *)malloc((length + 1) * sizeof(char));

    if (*str) {
      if (fread(*str, sizeof(char), length, pf) != length) {
        handle_error(ERROR__FILE_READ, __FILE__, __LINE__);

        free(*str);
        *str = NULL;
        return -1;
      }
      (*str)[length] = '\0';
    } else {
      handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
      return -1;
    }
  }

  return 1;
}

void *MY_STUDENT_Input() {
  output(MESSAGE__MY_STUDENT__SURNAME_INPUT);

  char *surname = readSurname();

  output(MESSAGE__MY_STUDENT__BIRTHDAY_INPUT);

  int birth_year;
  int inp = scanf_s("%d", &birth_year);
  stdin_clear();

  if (inp != 1) {
    handle_error(ERROR__INVALID_INPUT, __FILE__, __LINE__);
    return NULL;
  }

  output(MESSAGE__MY_STUDENT__STUDY_FIELD_LIST);

  for (int i = 0; i < FIELDS_OF_STUDY_TOTAL; i++) {
    printf("\n%s - %d", fieldsOfStudyName[i], i);
  }

  output(MESSAGE__MY_STUDENT__STUDY_FIELD_INPUT);

  enum FIELDS_OF_STUDY field_of_study;
  size_t input;

  scanf_s("%zu", &input);
  stdin_clear();

  if (input < FIELDS_OF_STUDY_TOTAL) {
    field_of_study = (enum FIELDS_OF_STUDY)input;
  } else {
    handle_error(ERROR__INVALID_STUDY_FIELD, __FILE__, __LINE__);
    exit(0);
  }

  return MY_STUDENT_Init(surname, birth_year, field_of_study);
}