#include "src/pch_source/stdafx.h"

#include "src/stack/my_stack.h"

const char STACK_DATA_FILENAME[] = "stack_data.bin";

static struct MY_STACK* top;  // pointer to the first element in the stack
static size_t stack_length;
static GetFuncPtr ptr_fun_get_pointers;


void MY_STACK_SetFuncPointers(GetFuncPtr ptr)
{
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

void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry)
{
    static struct MY_STACK* p;
    struct MY_STACK* ptmp = NULL;

    if (FirstEntry)
        p = top;

    while (p)
    {
        if (!(*ptr_comp_fun)(p->pData, pSearchDat))
        {
            p = p->next;
        }
        else
        {
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


void MY_STACK_Save()
{
    if (stack_length == 0) {
        // no need to save anything since the stack is empty
        return;
    }

    FILE* file;
    size_t it;
    unsigned int no_it = (unsigned int)stack_length;

    rec_type* file_desc = (rec_type*)malloc((stack_length + 1) * sizeof(rec_type));

    if (!file_desc) {
        handle_error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
        return;
    }

    fopen_s(&file, STACK_DATA_FILENAME, "wb");

    if (!file)
    {
        handle_error(ERROR__FILE_OPEN, __FILE__, __LINE__);
        return;
    }

    if (fwrite(&no_it, sizeof(unsigned int), 1, file) != 1) {
        handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
        return;
    };

    _fseeki64(file, (stack_length + 1) * rec_size, SEEK_CUR);

    struct MY_STACK* current = top;

    // moving items from the main stack to a file
    for (it = 0; it < stack_length; ++it)
    {
        file_desc[it] = _ftelli64(file);

        // Save the type before saving the data
        if (fwrite(&(current->typ), sizeof(enum MY_DATA_TYPE), 1, file) != 1) {
            handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
            return;
        }

        (current->ptr_fun_save)(&current->pData, file);

        current = current->next;
    }

    file_desc[it] = _ftelli64(file);

    _fseeki64(file, sizeof(unsigned int), SEEK_SET);
    
    if (fwrite(file_desc, sizeof(rec_type), stack_length + 1, file) != stack_length + 1) {
        handle_error(ERROR__FILE_WRITE, __FILE__, __LINE__);
        return;
    }

    if (file) {
        fclose(file);
    }

    if (file_desc)
        free(file_desc);

    file_desc = NULL;
}