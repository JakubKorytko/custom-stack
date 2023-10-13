#include "src/pch_source/stdafx.h"

#include "src/stack/my_stack.h"

static struct ExecResult MY_STACK_Read__Open_file(FILE** file) {
    fopen_s(file, STACK_DATA_FILENAME, "rb");

    if (*file == NULL)
    {
        return error(ERROR__FILE_OPEN, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Read_file_length(FILE* file, unsigned int* length) {
    if (fread((void*)length, sizeof(*length), 1, file) != 1) {
        return error(ERROR__FILE_READ, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Allocate_memory(rec_type** file_desc, unsigned int length) {
    *file_desc = (rec_type*)malloc((size_t)(length + 1) * sizeof(rec_type));

    if (!*file_desc) {
        return error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Read_data_type(FILE* file, enum MY_DATA_TYPE* type) {
    if (fread(type, sizeof(enum MY_DATA_TYPE), 1, file) != 1) {
        return error(ERROR__FILE_READ, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Allocate_tmp_memory(struct MY_STACK** tmp) {
    *tmp = (struct MY_STACK*)malloc(sizeof(struct MY_STACK));

    if (!*tmp) {
        return error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Prepare_tmp_stack_element(FILE* file, struct MY_STACK** tmp, enum MY_DATA_TYPE* type) {
    struct ExecResult result;

    result = MY_STACK_Read__Read_data_type(file, type);

    if (result.errorCode != -1) {
        return result;
    }

    result = MY_STACK_Read__Allocate_tmp_memory(tmp);

    if (result.errorCode != -1) {
        if (*tmp) {
            free(*tmp);
        }

        return result;
    }

    SetFunctionPointers(*type, &(*tmp)->ptr_fun_prnt,
        &(*tmp)->ptr_fun_free, &(*tmp)->ptr_fun_push, &(*tmp)->ptr_fun_save, &(*tmp)->ptr_fun_read,
        &(*tmp)->ptr_fun_comp, &(*tmp)->fun_search_data, &(*tmp)->fun_free_search_data,
        &(*tmp)->ptr_fun_get_type);

    return success();
}

static struct ExecResult MY_STACK_Read__Process_data(FILE* file, rec_type* file_desc, unsigned int length) {
    
    _fseeki64(file, sizeof(length), SEEK_SET);

    struct ExecResult result;
    unsigned int rec;
    enum MY_DATA_TYPE type;

    for (unsigned int it = 0; it < length; ++it)
    {

        // we use a temporary variable because every time we call MY_STACK_Push
        // the original variable gets bigger anyway so we would be duplicating the data
        struct MY_STACK* tmp;
        void* pData = NULL;

        rec = length - it - 1;  // we read the records in reverse order: no_items-1, ... , 0 
        _fseeki64(file, file_desc[rec], SEEK_SET);

        result = MY_STACK_Read__Prepare_tmp_stack_element(file, &tmp, &type);

        if (result.errorCode != -1) {
            return result;
        }

        if ((*tmp->ptr_fun_read)(&pData, file) != 0)
        {

            tmp->pData = pData;
            tmp->typ = type;

            MY_STACK_Push(tmp);
            output(MESSAGE__STACK_ELEMENT_LOADED);
            (*tmp->ptr_fun_prnt)(pData);
            output(MESSAGE__NEWLINE);
        }
    }

    return success();
}

static struct ExecResult MY_STACK_Read__Read_file_desc(FILE* file, rec_type** file_desc, unsigned int length) {

    if (fread(*file_desc, sizeof(*file_desc[0]), (size_t)length + 1, file) != (size_t)length + 1)
    {
        return error(ERROR__FILE_READ, __FILE__, __LINE__);
    }

    return success();
}

void MY_STACK_Read()
{
    FILE* file = NULL;
    rec_type* file_desc = NULL;
    unsigned int tmp_length = 0;
    struct ExecResult result;

    MY_STACK_Free(); // Cleaning the existing stack before loading the data

    result = MY_STACK_Read__Open_file(&file);

    if (result.errorCode == -1) {
        result = MY_STACK_Read__Read_file_length(file, &tmp_length);
    }

    if (result.errorCode == -1) {
        result = MY_STACK_Read__Allocate_memory(&file_desc, tmp_length);
    }

    if (result.errorCode == -1) {
        result = MY_STACK_Read__Read_file_desc(file, &file_desc, tmp_length);
    }

    if (result.errorCode == -1) {
        result = MY_STACK_Read__Process_data(file, file_desc, tmp_length);
    }

    if (file) {
        fclose(file);
    }

    if (file_desc) {
        free(file_desc);
    }

    if (result.errorCode != -1) {
        handle_error(result.errorCode, result.file, result.line);
    }
}
