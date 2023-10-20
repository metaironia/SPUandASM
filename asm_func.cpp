#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "oneginlib/functions_for_input.h"
#include "asm_func.h"
#include "asm_log.h"
#include "extern_for_asm.h"

enum AsmFuncStatus Assemble (PtrToStr *const ptrs_to_strings, const size_t current_str,
                             double *const code_arr, size_t *const position_in_code_arr) {

    assert (ptrs_to_strings);
    assert (code_arr);
    assert (position_in_code_arr);

    char first_word[5] = "";    //TODO make len const
    int code = 0;

    FindCommentaryInString (ptrs_to_strings, current_str);

    if (!(ptrs_to_strings[current_str].pointer_to_string))
        return FAIL;

    sscanf (ptrs_to_strings[current_str].pointer_to_string, "%s", first_word);

    if (strcmp (first_word, "push") == 0) {

        char third_word[5] = "";
        double value = 0;
        int scanf_result = sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %lf", &value);

        if (scanf_result == 1) {

            code = ARG_FORMAT_IMMED | CMD_PUSH;

            EmitCodeArg (code_arr, position_in_code_arr, code, value);
        }

        if (scanf_result == 0) {

            code = ARG_FORMAT_REG | CMD_PUSH;

            int reg_num = 0;
            RegFind (ptrs_to_strings, current_str, &reg_num);

            EmitCodeReg (code_arr, position_in_code_arr, code, reg_num);
        }

        if (sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %*s %s", third_word) == 1) {

            LOG_PRINT_ASM (ASM_LOG_FILE, "Assembly fail.\n");

            return FAIL;
        }
    }

    else if (strcmp (first_word, "pop") == 0) {

        char third_word[5] = "";

        code = ARG_FORMAT_REG | CMD_POP;

        int reg_num = 0;
        RegFind (ptrs_to_strings, current_str, &reg_num);

        EmitCodeReg (code_arr, position_in_code_arr, code, reg_num);

        if (sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %*s %s", third_word) == 1) {

            LOG_PRINT_ASM (ASM_LOG_FILE, "Assembly fail.\n");

            return FAIL;
        }
    }

    else if (strcmp (first_word, "HLT") == 0) {

        char second_word[5] = "";

        code = CMD_HLT;
        EmitCodeNoArg (code_arr, position_in_code_arr, code);

        if (sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %s", second_word) == 1) {

            LOG_PRINT_ASM (ASM_LOG_FILE, "Assembly fail.\n");

            return FAIL;
        }
    }

    else if (strcmp (first_word, "div") == 0) {

        char second_word[5] = "";

        code = CMD_DIV;
        EmitCodeNoArg (code_arr, position_in_code_arr, code);

        if (sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %s", second_word) == 1) {

            LOG_PRINT_ASM (ASM_LOG_FILE, "Assembly fail.\n");

            return FAIL;
        }
    }

    else if (strcmp (first_word, "sub") == 0) {

        char second_word[5] = "";

        code = CMD_SUB;
        EmitCodeNoArg (code_arr, position_in_code_arr, code);

        if (sscanf (ptrs_to_strings[current_str].pointer_to_string, "%*s %s", second_word) == 1) {

            LOG_PRINT_ASM (ASM_LOG_FILE, "Assembly fail.\n");

            return FAIL;
        }
    }

    else {

        printf ("Syntax error at line %d: %s\n", current_str, ptrs_to_strings[current_str].pointer_to_string);

        return FAIL;
    }

    return OK;
}

enum AsmFuncStatus RegFind (PtrToStr *ptrs_to_strs, size_t curr_str, int *reg_number) {

    char reg_symbol = 0;
    int scanf_scanned_symbols = 0;

    sscanf (ptrs_to_strs[curr_str].pointer_to_string, "%*s r%cx%n", &reg_symbol, &scanf_scanned_symbols);

    if (scanf_scanned_symbols != 0 && 'a' <= reg_symbol && reg_symbol <= 'd') {

        *reg_number = (reg_symbol - 'a');

        return OK;
    }                      //TODO maybe switch FAIL and OK

    return FAIL;
}

enum AsmFuncStatus EmitCodeArg (double *const array_of_code,  size_t *const position,
                                int command_code, double val) {

    assert (array_of_code);
    assert (position);

    array_of_code[(*position)++] = command_code;
    array_of_code[(*position)++] = val;


    return OK;
}

enum AsmFuncStatus EmitCodeReg (double *const array_of_code,  size_t *const position,
                                int command_code, int reg) {

    assert (array_of_code);
    assert (position);

    array_of_code[(*position)++] = command_code;
    array_of_code[(*position)++] = reg;

    return OK;
}

enum AsmFuncStatus EmitCodeNoArg (double *const array_of_code,  size_t *const position,
                                  int command_code) {

    assert (array_of_code);
    assert (position);

    array_of_code[(*position)++] = command_code;

    return OK;
}

enum AsmFuncStatus WriteToBinFile (double *const arr_of_code, size_t pos, FILE *bin_to_write) {

    assert (arr_of_code);
    assert (bin_to_write);

    int writes = -1;

    if ((writes = fwrite (arr_of_code + pos, sizeof (arr_of_code[0]), 1, bin_to_write)) == 1)
        LOG_PRINT_ASM (ASM_LOG_FILE, "Successful write: wrote ");

    else
        LOG_PRINT_ASM (ASM_LOG_FILE, "Write was failed: expected to write ");

    LOG_PRINT_ASM (ASM_LOG_FILE, "value %.2lf ", arr_of_code[pos]);

    LOG_PRINT_ASM (ASM_LOG_FILE, "in code array to position %Iu\n", pos);

    return OK;
}

enum AsmFuncStatus FindCommentaryInString (PtrToStr *const ptr_to_strs, const size_t curr_str) {

    assert (ptr_to_strs);

    char *is_commentary = strchr (ptr_to_strs[curr_str].pointer_to_string, COMMENTARY_MARK);

    if (is_commentary)
        *is_commentary = '\0';

    return OK;
}
