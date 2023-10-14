// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"
#include "src/interface/errors_handler.h"

#include <crtdbg.h>
#include "src/stack/my_stack.h"

static const char* error_messages[] = {
    "No error",
    "Memory allocation error",
    "Invalid input detected",
    "Stack is empty",
    "Stack overflow error",
    "Failed to open file",
    "Failed to read from file",
    "Invalid pointer provided",
    "Failed to write to file. Closing file handles and performing cleanup.",
    "Unknown data type added to the stack",
    "Invalid parameter detected",
    "Invalid study field number",
    "Unknown error occurred"
};


static void display_error(Error error, const char* file, unsigned int line) {
    if (error >= 0 && error < ERROR__TOTAL)

        // notice the lack of commas between the strings
        // this is because its only one string,
        // but split into multiple lines
        printf(
        "Error: %s\n"
        "At file: %s\n"
        "Line: %u\n",
        error_messages[error], file, line);
    else
        printf("%s\n", error_messages[ERROR__UNKNOWN]);
}

void handle_error(Error error, const char* file, unsigned int line) {
    display_error(error, file, line);

    if (error == ERROR__MEMORY_ALLOCATION) {
        MY_STACK_Free();
    }

    system("pause");
    exit(1);
}

static void myInvalidParameterHandler(const wchar_t* expression,
    const wchar_t* function,
    const wchar_t* file,
    unsigned int line) {

    // notice the lack of commas between the strings
    // this is because its only one string,
    // but split into multiple lines
    wprintf(
        L"Invalid parameter detected in function %s."
        L" File: %s"
        "Line: %d\n",
        function, file, line);

    wprintf(L"Expression: %s\n\n", expression);

    // Handle the invalid parameter error
    handle_error(ERROR__INVALID_PARAMETER, (const char*)file, line);
}

_invalid_parameter_handler setInvalidParameterHandler() {
    // Set terminate handler
    _invalid_parameter_handler old_param_hadler;
    old_param_hadler = _set_invalid_parameter_handler(
        &myInvalidParameterHandler);

    // Disable the message box for assertions.
    _CrtSetReportMode(_CRT_ASSERT, 0);

    return old_param_hadler;
}

struct ExecResult error(int errorCode, char* file, unsigned int line) {
    struct ExecResult res = {
        .errorCode = errorCode,
        .line = line,
        .file = file
    };

    return res;
}

struct ExecResult success() {
    struct ExecResult res = {
    .errorCode = -1,
    .line = 0,
    .file = NULL
    };

    return res;
}
