// Copyright: 2023 Jakub Korytko

#include "src/pch_source/stdafx.h"

#include "src/stack/my_stack.h"

const char STACK_DATA_FILENAME[] = "stack_data.bin";
const char FILE_WRITE_MODE[] = "wb";
const char FILE_READ_MODE[] = "rb";

static struct MY_STACK* top;  // pointer to the first element in the stack

struct MY_STACK* MY_STACK_GetTopElement() {
    return top;
}

static size_t stack_length;

size_t MY_STACK_GetStackLength() {
    return stack_length;
}

static GetFuncPtr ptr_fun_get_pointers;

void MY_STACK_SetFuncPointers(GetFuncPtr ptr) {
    ptr_fun_get_pointers = ptr;
}

void MY_STACK_Init(GetFuncPtr ptr) {
    // clearing the stack if any is already initialized
    MY_STACK_Free();
    MY_STACK_SetFuncPointers(ptr);

    top = NULL;
    stack_length = 0;
}

struct MY_STACK* MY_STACK_Push(struct MY_STACK * current) {
    if (!current) {
        handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
        return NULL;
    }

    current->next = top;
    top = current;

    stack_length += 1;

    return current;
}

struct MY_STACK MY_STACK_Pop() {
    struct MY_STACK rv;

    // return empty struct if there is no top element
    rv = (struct MY_STACK){ .pData = NULL, .next = NULL };

    if (top) {
        struct MY_STACK* next = top->next;

        rv.pData = top->pData;
        rv.ptr_fun_prnt = top->ptr_fun_prnt;
        rv.ptr_fun_free = top->ptr_fun_free;
        rv.next = NULL;

        if (top) {
            free(top);
        }

        stack_length -= 1;
        top = next;
    }

    return rv;
}

void MY_STACK_Display() {
    if (!top) {
        output(MESSAGE__STACK_EMPTY);
        return;
    }

    struct MY_STACK* element = top;

    while (element) {
        (*element->ptr_fun_prnt)(element->pData);
        element = element->next;
    }
}

void MY_STACK_Display_Top() {
    if (!top) {
        output(MESSAGE__STACK_EMPTY);
        return;
    }

(*top->ptr_fun_prnt)(top->pData);
}

void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry) {
    static struct MY_STACK* p;
    struct MY_STACK* ptmp = NULL;

    if (FirstEntry)
        p = top;

    while (p) {
        if (!(*ptr_comp_fun)(p->pData, pSearchDat)) {
            p = p->next;
        } else {
            ptmp = p;
            p = p->next;
            return ptmp->pData;
        }
    }

    return NULL;
}

void MY_STACK_Free() {
    struct MY_STACK* p = top;
    struct MY_STACK* pmpt = NULL;

    while (p) {
        (*p->ptr_fun_free)(p->pData);

        pmpt = p;

        p = p->next;

        if (pmpt) {
            free(pmpt);
        }
    }

    top = NULL;
    stack_length = 0;
}
