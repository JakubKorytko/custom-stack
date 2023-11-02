// Copyright: 2023 Jakub Korytko
// LINT_C_FILE

#include "pch_source/stdafx.h"

#include "stack/my_stack.h"

static struct ExecResult MY_STACK_Save__Open_file(FILE** file) {
    fopen_s(file, STACK_DATA_FILENAME, FILE_WRITE_MODE);
    if (*file == NULL) {
        return error(ERROR__FILE_OPEN, __FILE__, __LINE__);
    }
    return success();
}

static struct ExecResult MY_STACK_Save__Write_no_items(
    FILE* file, const unsigned int no_it) {
    if (!file) {
        return error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    }

    if (fwrite(&no_it, sizeof(unsigned int), 1, file) != 1) {
        return error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Save__Write_data_type(
    FILE* file, const struct MY_STACK* element) {
    if (fwrite(&element->type, sizeof(enum MY_DATA_TYPE), 1, file) != 1) {
        return error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    }
    return success();
}

static struct ExecResult MY_STACK_Save__Write_element(
    FILE* file, struct MY_STACK* element) {
    if ((element->ptr_fun_save)(&element->pData, file) != 1) {
        return error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Save__Rewind_and_write_file_desc(
    FILE* file, rec_type* file_desc, size_t length) {
    _fseeki64(file, sizeof(unsigned int), SEEK_SET);

    if (fwrite(file_desc, sizeof(rec_type), length, file) != length) {
        return error(ERROR__FILE_WRITE, __FILE__, __LINE__);
    }

    return success();
}

static struct ExecResult MY_STACK_Save__Move_items_to_file(
    FILE* file, size_t stack_length) {
    struct ExecResult result;

    size_t it;
    size_t file_desc_size = stack_length + 1;

    rec_type* file_desc = (rec_type*)calloc(file_desc_size, sizeof(rec_type));

    if (!file_desc) {
        MY_STACK_Free();
        return error(ERROR__MEMORY_ALLOCATION, __FILE__, __LINE__);
    }

    _fseeki64(file, file_desc_size * rec_size, SEEK_CUR);

    struct MY_STACK* current = MY_STACK_GetTopElement();

    for (it = 0; it < stack_length; ++it) {
        file_desc[it] = _ftelli64(file);

        result = MY_STACK_Save__Write_data_type(file, current);
        if (result.errorCode != -1) {
            free(file_desc);
            return result;
        }

        result = MY_STACK_Save__Write_element(file, current);
        if (result.errorCode != -1) {
            free(file_desc);
            return result;
        }

        current = current->next;
    }

    if (it < file_desc_size) {
        file_desc[it] = _ftelli64(file);
    }

    result = MY_STACK_Save__Rewind_and_write_file_desc(
        file, file_desc, stack_length + 1);

    if (file_desc) {
        free(file_desc);
    }

    return result;
}

void MY_STACK_Save() {
    size_t stack_length = MY_STACK_GetStackLength();

    FILE* file = NULL;
    unsigned int no_it = (unsigned int)stack_length;

    struct ExecResult result = MY_STACK_Save__Open_file(&file);

    if (result.errorCode == -1) {
        result = MY_STACK_Save__Write_no_items(file, no_it);
    }

    if (stack_length == 0) {
        // no need to save any elements since the stack is empty
        if (file) {
            fclose(file);
        }

        printf_s("\nSaved empty stack to file\n");
        return;
    }

    if (result.errorCode == -1) {
        result = MY_STACK_Save__Move_items_to_file(file, stack_length);
    }

    if (file) {
        fclose(file);
    }

    if (result.errorCode != -1) {
        handle_error(result.errorCode, result.file, result.line);
    }

    printf_s(generic_messages[MESSAGE__SAVED_N_ELEMENTS], no_it);
}
