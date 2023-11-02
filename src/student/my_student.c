// Copyright: 2023 Jakub Korytko
// LINT_C_FILE

#include "pch_source/stdafx.h"
#include "student/my_student.h"

// NOLINTNEXTLINE(build/include_order)
#include <string.h>  // must be included after stdafx.h

#define MAX_SURNAME_SIZE 128

static const char* fieldsOfStudyName[] = {
    "Computer Science",
    "Mathematics",
    "Engineer",
    "Physics",
    "Chemistry"
};

static void stdin_clear() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) continue;
}

static char* readSurname() {
    // function that shortens allocated memory to the maximum length needed
    char* buff;
    size_t buff_len = 0;

    while (buff_len <= 1) {
        buff = (char*)malloc(MAX_SURNAME_SIZE * sizeof(char));

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

    char* surname = (char*)malloc(surname_len * sizeof(char));

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

void *MY_STUDENT_Init(char * surname, int year,
enum FIELDS_OF_STUDY field_of_study) {
    struct MY_STUDENT* pdata;
    pdata = (struct MY_STUDENT*)malloc(sizeof(struct MY_STUDENT));

    if (pdata) {
        if (surname) {
            size_t pdata_length = strlen(surname) + 1;

            pdata->student_surname = (char*)malloc(pdata_length * sizeof(char));
            if (pdata->student_surname) {
                strncpy_s(pdata->student_surname,
                pdata_length, surname, strlen(surname));
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

        return (void*)pdata;
    } else {
        if (surname) {
            free(surname);
        }

        surname = NULL;

        handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
        return NULL;
    }
}

void MY_STUDENT_Free(void* ptr) {
    struct MY_STUDENT* pDat = (struct MY_STUDENT*)ptr;

    if (pDat) {
        if (pDat->student_surname) {
            free(pDat->student_surname);
            pDat->student_surname = NULL;
        }
        free(pDat);
        pDat = NULL;
    }
}

void* MY_STUDENT_Push() {
    return MY_STUDENT_Input();
}

void MY_STUDENT_Print(void* ptr) {
    struct MY_STUDENT* p = (struct MY_STUDENT*)ptr;
    if (p) {
        printf_s(
            custom_messages[MESSAGE__STUDENT_PRINT],
            p->student_surname, p->birth_year,
            fieldsOfStudyName[p->field_of_study],
            p->field_of_study);
    }
}

int MY_STUDENT_Compare(void* pCurData, void* pSearchData) {
    const struct MY_STUDENT* pcur = (struct MY_STUDENT*)pCurData;
    const struct MY_STUDENT* psearch = (struct MY_STUDENT*)pSearchData;

    if (strcmp(pcur->student_surname, psearch->student_surname) == 0)
        return 1;

    return 0;
}

static int MY_STUDENT_SaveDynamicString(const char* str, FILE* pf) {
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

static int MY_STUDENT_ReadDynamicString(char** str, FILE* pf) {
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
        *str = (char*)malloc((length + 1) * sizeof(char));

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

int MY_STUDENT_Save(void** pdat, FILE* pf) {
    if (pdat == NULL || *pdat == NULL || pf == NULL) {
        handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
        return 0;
    }

    struct MY_STUDENT* student = (struct MY_STUDENT*)*pdat;

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

int MY_STUDENT_Read(void** pdat, FILE* pf) {
    if (pdat == NULL || pf == NULL) {
        handle_error(ERROR__INVALID_POINTER, __FILE__, __LINE__);
        return 0;
    }

    struct MY_STUDENT* pdata = (struct MY_STUDENT*)malloc(
        sizeof(struct MY_STUDENT));

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

void* MY_STUDENT_Input() {
    output(MESSAGE__SURNAME_INPUT);

    char* surname = readSurname();

    output(MESSAGE__BIRTHDAY_INPUT);

    int birth_year;
    int inp = scanf_s("%d", &birth_year);
    stdin_clear();

    if (inp != 1) {
        handle_error(ERROR__INVALID_INPUT, __FILE__, __LINE__);
        return NULL;
    }

    output(MESSAGE__STUDY_FIELD_LIST);

    for (int i = 0; i < FIELDS_OF_STUDY_TOTAL; i++) {
        printf("\n%s - %d", fieldsOfStudyName[i], i);
    }

    output(MESSAGE__STUDY_FIELD_INPUT);

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

void* MY_STUDENT_SearchData() {
    output(MESSAGE__SURNAME_INPUT);
    char* surname = readSurname();

    if (!surname) {
        handle_error(ERROR__INVALID_INPUT, __FILE__, __LINE__);
        exit(0);
    }

    struct MY_STUDENT* searchDat = (struct MY_STUDENT*)malloc(
        sizeof(struct MY_STUDENT));

    if (!searchDat) {
        handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
        exit(0);
    }

    size_t surname_len = strlen(surname) + 1;

    searchDat->student_surname = (char*)malloc(surname_len * sizeof(char));

    if (!searchDat->student_surname) {
        handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
        exit(0);
    }

    strcpy_s(searchDat->student_surname, surname_len, surname);

    if (surname)
        free(surname);

    return searchDat;
}

void MY_STUDENT_SearchData_Free(void * searchDat) {
    if (((struct MY_STUDENT*)searchDat)->student_surname) {
        free(((struct MY_STUDENT*)searchDat)->student_surname);
    }
}

enum MY_DATA_TYPE MY_STUDENT_GetType() {
    return DATA_TYPE_MY_STUDENT;
}
