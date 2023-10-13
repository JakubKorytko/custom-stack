#ifndef ERRORS_HANDLER__H
#define ERRORS_HANDLER__H

enum ErrorCode {
	ERROR__NONE,
	ERROR__MEMORY_ALLOCATION,
	ERROR__INVALID_INPUT,
	ERROR__STACK_EMPTY,
	ERROR__STACK_OVERFLOW,
	ERROR__FILE_OPEN,
	ERROR__FILE_READ,
	ERROR__INVALID_POINTER,
	ERROR__FILE_WRITE,
	ERROR__INVALID_DATA_TYPE,
	ERROR__INVALID_PARAMETER,
	ERROR__INVALID_STUDY_FIELD,
	ERROR__UNKNOWN,
	// (...)
	ERROR__TOTAL // MARKS THE END OF AN ENUM, ALWAYS AT THE END
};

struct ExecResult {
	short errorCode;
	char* file;
	unsigned int line;
};

typedef enum ErrorCode Error;

void handle_error(Error error, const char* file, unsigned int line);

struct ExecResult error(short errorCode, char* file, unsigned int line);

struct ExecResult success();

void setInvalidParameterHandler();


// Internal functions, there is no need to declare them in the header file

/*

static void display_error(Error error, const char* file, unsigned int line);

static void myInvalidParameterHandler(const wchar_t* expression,
	const wchar_t* function,
	const wchar_t* file,
	unsigned int line,
	uintptr_t pReserved);

*/

#endif // ERRORS_HANDLER__H
