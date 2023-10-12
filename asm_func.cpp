#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "asm_func.h"

enum StringAnalyser (PtrToStr *ptrs_to_strings, int64_t num_of_str) {

    char *curr_word = NULL;
    unsigned int command = 0;

    for (int i = 0; i < num_of_str; i++) {

        if (!(ptrs_to_strings -> pointer_to_string))
            continue;

        curr_word = strtok ((ptrs_to_strings -> pointer_to_string), delimiters);

        if (strcmp (curr_word, "push") == 0)
            command |=

    }

    return OK;
}
