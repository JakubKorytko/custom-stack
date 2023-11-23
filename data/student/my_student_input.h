// Copyright: 2023 Jakub Korytko

#ifndef DATA_STUDENT_MY_STUDENT_INPUT_H_
#define DATA_STUDENT_MY_STUDENT_INPUT_H_

#define MAX_SURNAME_SIZE 128

enum FIELDS_OF_STUDY {
  Computer_Science,
  Mathematics,
  Engineer,
  Physics,
  Chemistry,
  // (...)

  FIELDS_OF_STUDY_TOTAL
  // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

struct MY_STUDENT {
  char *student_surname;
  int birth_year;
  enum FIELDS_OF_STUDY field_of_study;
};

void stdin_clear();

char *readSurname();

int MY_STUDENT_SaveDynamicString(const char *str, FILE *pf);

int MY_STUDENT_ReadDynamicString(char **str, FILE *pf);

void *MY_STUDENT_Input();

extern const char *fieldsOfStudyName[];

#endif  // DATA_STUDENT_MY_STUDENT_INPUT_H_
