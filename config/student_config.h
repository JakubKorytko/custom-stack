#ifndef CONFIG_STUDENT_CONFIG_H_
#define CONFIG_STUDENT_CONFIG_H_

#ifndef STUDENT_CONFIG_CUSTOM_MESSAGES
#define STUDENT_CONFIG_CUSTOM_MESSAGES                  \
                                                        \
"Enter student name: ",                                 \
"\nList of fields of study:\n",                         \
"Enter year of birth of student: ",                     \
"\n\nSelect a field of study from the list above: ",    \
"\n"                                                    \
"--- STUDENT ---\n"                                     \
"Student's name: %s\n"                                  \
"Year of birth: %u\n"                                   \
"Field of study: %s (%d)\n"                             \
"---"                                                   \
"\n",                                                   \

#endif  // STUDENT_CONFIG_CUSTOM_MESSAGES

#ifndef STUDENT_CONFIG_CUSTOM_MESSAGES_ENUM
#define STUDENT_CONFIG_CUSTOM_MESSAGES_ENUM             \
                                                        \
MESSAGE__MY_STUDENT__SURNAME_INPUT,                     \
MESSAGE__MY_STUDENT__STUDY_FIELD_LIST,                  \
MESSAGE__MY_STUDENT__BIRTHDAY_INPUT,                    \
MESSAGE__MY_STUDENT__STUDY_FIELD_INPUT,                 \
MESSAGE__MY_STUDENT__STUDENT_PRINT,                     \

#endif  // STUDENT_CONFIG_CUSTOM_MESSAGES_ENUM

extern struct MY_DATA_POINTERS MY_STUDENT__POINTERS;

#endif  // CONFIG_STUDENT_CONFIG_H_
