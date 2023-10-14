#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "asm_func.h"

enum AsmFuncStatus Assemble (PtrToStr *const ptrs_to_strings, const size_t current_str, int *const code_arr,
                             size_t *const position_in_code_arr, FILE *binary_file) {

    assert (ptrs_to_strings);
    assert (code_arr);
    assert (position_in_arr);
    assert (binary_file);

    char first_word[5] = "";    //TODO make len const and assert
    unsigned char code = 0;

    if (!(ptrs_to_strings[current_str] -> pointer_to_string))     //TODO make commentaries
        return NULL_STRING;

    sscanf (ptrs_to_strings[current_str], "%s", first_word);

    if (strcmp (first_word, "push") == 0) {

        char third_word = "";
        int value = 0;
        int scanf_result = sscanf (ptrs_to_strings[current_str], "%*s %d", value);

        if (scanf_result == 1) {

            code = ARG_FORMAT_IMMED | CMD_PUSH;

            EmitCodeArg (code_arr, position_in_code_arr, code, value, binary_file);

            if (sscanf ((ptrs_to_strings[current_str], "%*s %*s %s", third_word) == 1)
                return FAIL;
        }

        if (scanf_result == 0) {

            code = ARG_FORMAT_REG | CMD_PUSH;

            int reg_num = 0;

            RegFind (ptrs_to_strings, current_str, &reg_num);
            EmitCodeReg (code_arr, position_in_code_arr, code, reg_num, binary_file);

            if (sscanf ((ptrs_to_strings[current_str], "%*s %*s %s", third_word) == 1)
                return FAIL;
        }
    }

    else if (strcmp (curr_word, "pop") == 0) {

        int third_word = "";

        code = ARG_FORMAT_REG | CMD_POP;

        RegFind (ptrs_to_strings, current_str, &reg_num);

        EmitCodeReg (code_arr, position_in_code_arr, code, reg_num, binary_file);

        if (sscanf ((ptrs_to_strings[current_str], "%*s %*s %s", third_word) == 1)
                return FAIL;
    }

    else if (strcmp (curr_word, "HLT") == 0) {

        int second_word = "";

        code = CMD_HLT;
        EmitCodeNoArg (code_arr, position_in_code_arr, code, binary_file);

        if (sscanf ((ptrs_to_strings[current_str], "%*s %s", second_word) == 1)
                return FAIL;
    }

    else if (strcmp (curr_word, "div") == 0)

        int second_word = "";

        code = CMD_DIV;
        EmitCodeNoArg (code_arr, position_in_code_arr, code, binary_file);


        if (sscanf ((ptrs_to_strings[current_str], "%*s %s", second_word) == 1)
                return FAIL;
    }

`   else if (strcmp (curr_word, "sub") == 0)

        int second_word = "";

        code = CMD_SUB;
        EmitCodeArg (code_arr, position_in_code_arr, code, binary_file);


        if (sscanf ((ptrs_to_strings[current_str], "%*s %s", second_word) == 1)
                return FAIL;
    }

    else {

        printf ("Syntax error at line %d: %s\n", current_str, ptrs_to_strings[current_str]);

        return FAIL;
    }

    return OK;
}

enum AsmFuncStatus RegFind (PtrToStr *ptrs_to_strs, size_t curr_str, int *reg_number) {

    char reg_symbol = 0;
    int scanf_scanned_symbols = 0;

    sscanf (ptrs_to_strs[current_str], "%*s r%cx%n", reg_symbol, scanf_scanned_symbols);

    if (scanf_scanned_symbols != 0 && 'a' <= reg_symbol && reg_symbol <= 'd') {

        *reg_number = (reg_symbol - 'a');

        return OK;
    }                      //TODO maybe switch FAIL and OK

    return FAIL;
}

enum AsmFuncStatus EmitCodeArg (int *const array_of_code, size_t *const pos,
                                unsigned int cmd_code, int val, FILE *bin_file) {

    int successful_writes = 0;

    successful_writes += fwrite (array_of_code + (*pos)++, cmd_code, sizeof (cmd_code), bin_file);
    successful_writes += fwrite (array_of_code + (*pos)++, val,      sizeof (val),      bin_file);

    if (successful_writes != 2)
        return FAIL;

    return OK;
}

enum AsmFuncStatus EmitCodeReg (int *const array_of_code, size_t *const pos,
                                unsigned int cmd_code, int reg, FILE *bin_file) {

    int successful_writes = 0;

    successful_writes += fwrite (array_of_code + (*pos)++, cmd_code, sizeof (cmd_code), bin_file);
    successful_writes += fwrite (array_of_code + (*pos)++, reg,      sizeof (reg),      bin_file);



    if (successful_writes != 2)
        return FAIL;

    return OK;
}

enum AsmFuncStatus EmitCodeNoArg (int *const array_of_code, size_t *const pos,
                                  unsigned int cmd_code, FILE *bin_file) {

    int successful_writes = 0;

    successful_writes += fwrite (array_of_code + (*pos)++, cmd_code, sizeof (cmd_code), bin_file)

    if (successful_writes != 1)
        return FAIL;

    return OK;
}
