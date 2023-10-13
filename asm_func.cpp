#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "asm_func.h"

enum StringAnalyser (PtrToStr *const ptrs_to_strings, const size_t current_str, int *const code_arr, int *const position_in_arr,
                     FILE *binary_file) {

    char first_word[5] = "";    //TODO make len const and assert
    unsigned char code = 0;

    if (!(ptrs_to_strings[current_str] -> pointer_to_string))
        return NULL_STRING;

    scanf (ptrs_to_strings[current_str], "%s", first_word);

    if (strcmp (first_word, "push") == 0) {

        char third_word = "";
        int value = 0;
        int scanf_result = sscanf (ptrs_to_strings[current_str], "%*s %d", value);

        if (scanf_result == 1) {

            code = ARG_FORMAT_IMMED | CMD_PUSH;

            EmitCodeArg (code_arr, position_in_arr, code, value, binary_file);

            if (sscanf ((ptrs_to_strings[current_str], "%*s %*s %s", third_word) == 1)
                return FAIL;
        }

        if (scanf_result == 0) {

            code = ARG_FORMAT_REG | CMD_PUSH;

            int reg_num = 0;

            RegFind (ptrs_to_strings, current_str, &reg_num);
            EmitCodeNoArg (code_arr, position_in_arr, code, reg_num, binary_file);

            if (sscanf ((ptrs_to_strings[current_str], "%*s %*s %s", third_word) == 1)
                return FAIL;
        }

        return OK;
    }

    if (strcmp (curr_word, "pop") == 0) {

        code = ARG_FORMAT_REG | CMD_POP;

        EmitCodeNoArg (code_arr, position_in_arr, code, reg_num, binary_file);

    }

    if (strcmp (curr_word, "HLT") == 0)
        command |=

    }

    if (strcmp (curr_word, "div") == 0)
        command |=

    }

`   if (strcmp (curr_word, "sub") == 0)
        command |=

    }

    return FAIL;
}

enum RegFind (PtrToStr *ptrs_to_strs, size_t curr_str, int *reg_number) {

    char reg_symbol = 0;
    int scanf_scanned_symbols = 0;

    sscanf (ptrs_to_strs[current_str], "%*s r%cx%n", reg_symbol, scanf_scanned_symbols);

    if (scanf_scanned_symbols != 0 && 'a' <= reg_symbol && reg_symbol <= 'd') {

        *reg_number = (reg_symbol - 'a' + 1);

        return OK;
    }

    return FAIL;
}

enum EmitCodeArg (int *const array_of_code, int *const pos, unsigned int cmd_code, int val, FILE *bin_file) {

    successful_writes = 0;

    successful_writes += fwrite (array_of_code, cmd_code, sizeof (cmd_code), bin_file);
    successful_writes += fwrite (array_of_code, cmd_code, sizeof (cmd_code), bin_file);
    successful_writes += fwrite (array_of_code, cmd_code, sizeof (cmd_code), bin_file);

    if (fwrite (array_of_code, ) < 3)
        return FAIL;

    return OK;
}

