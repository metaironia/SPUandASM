#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "oneginlib/functions_for_input.h"
#include "asm_func.h"
#include "asm_log.h"
#include "extern_for_asm.h"


#define DEF_CMD(cmd_name, cmd_num, have_arg, ...)                                                                \
                                                                                                                 \
                                if (strcmp (first_word, #cmd_name) == 0) {                                       \
                                                                                                                 \
                                    if (ParseAndSetArgs (cmd_num,                                                \
                                                         ptrs_to_strings[current_str].pointer_to_string,         \
                                                         code_arr, position_in_code_arr, have_arg) == FAIL) {    \
                                                                                                                 \
                                        PrintError (current_str + 1,                                             \
                                                    ptrs_to_strings[current_str].pointer_to_string);             \
                                        return FAIL;                                                             \
                                    }                                                                            \
                                }                                                                                \
                                else

#define DEF_COND_JMP DEF_JMP

#define DEF_JMP(cmd_name, cmd_num, ...)                                                                     \
                                                                                                            \
                                if (strcmp (first_word, #cmd_name) == 0) {                                  \
                                                                                                            \
                                    if (JumpParse (cmd_num,                                                 \
                                                   ptrs_to_strings[current_str].pointer_to_string,          \
                                                   code_arr, position_in_code_arr, labels,                  \
                                                   *label_counter, num_of_compilation) == FAIL) {           \
                                                                                                            \
                                        PrintError (current_str + 1,                                        \
                                                    ptrs_to_strings[current_str].pointer_to_string);        \
                                        return FAIL;                                                        \
                                    }                                                                       \
                                }                                                                           \
                                else

enum AsmFuncStatus Assemble (PtrToStr *const ptrs_to_strings, const size_t current_str,
                             double *const code_arr, size_t *const position_in_code_arr,
                             LabelForJump *const labels, size_t *label_counter,
                             const int num_of_compilation) {

    assert (ptrs_to_strings);
    assert (code_arr);
    assert (position_in_code_arr);

    if (IsRestStringEmpty (ptrs_to_strings[current_str].pointer_to_string, 0))
        return OK;

    char first_word[MAX_WORD_LENGTH] = "";

    FindCommentaryInString (ptrs_to_strings, current_str);

    size_t current_pos_str = 0;

    sscanf (ptrs_to_strings[current_str].pointer_to_string, "%s%n", first_word, &current_pos_str);

    if (first_word[0] == ':') {

        if (num_of_compilation >= 2)
            return OK;

        strcpy (labels[*label_counter].name, first_word + 1);           //TODO fix strncpy instead of strcpy
        labels[*label_counter].address = *position_in_code_arr;

        (*label_counter)++;

        if (IsRestStringEmpty (ptrs_to_strings[current_str].pointer_to_string, current_pos_str))
            return OK;
        else
            return FAIL;
    }

    #include "commands.h"

    /* else */ {

        PrintError (current_str + 1, ptrs_to_strings[current_str].pointer_to_string);

        return FAIL;
    }

    return OK;
}

/*enum AsmFuncStatus RegFind (PtrToStr *ptrs_to_strs, size_t curr_str, int *reg_number) {

    char reg_symbol = 0;
    int scanf_scanned_symbols = 0;

    sscanf (ptrs_to_strs[curr_str].pointer_to_string, "%*s r%cx%n", &reg_symbol, &scanf_scanned_symbols);

    if (scanf_scanned_symbols != 0 && 'a' <= reg_symbol && reg_symbol <= 'd') {

        *reg_number = (reg_symbol - 'a');

        return OK;
    }                      //TODO maybe switch FAIL and OK

    return FAIL;
} */

enum AsmFuncStatus EmitCodeNoArg (double *const arr_of_code,  size_t *const pos, const int command_code) {

    assert (arr_of_code);
    assert (pos);

    arr_of_code[(*pos)++] = command_code;

    return OK;
}

enum AsmFuncStatus EmitCodeArg (double *const arr_of_code,  size_t *const pos,
                                const int command_code, const double val) {

    assert (arr_of_code);
    assert (pos);

    arr_of_code[(*pos)++] = command_code;
    arr_of_code[(*pos)++] = val;


    return OK;
}

enum AsmFuncStatus EmitCodeReg (double *const arr_of_code,  size_t *const pos,
                                const int command_code, const int reg) {

    assert (arr_of_code);
    assert (pos);

    arr_of_code[(*pos)++] = command_code;
    arr_of_code[(*pos)++] = reg;

    return OK;
}

enum AsmFuncStatus EmitCodeRegAndArg (double *const arr_of_code,  size_t *const pos,
                                      const int command_code, const int reg, const double val) {

    assert (arr_of_code);
    assert (pos);

    arr_of_code[(*pos)++] = command_code;
    arr_of_code[(*pos)++] = reg;
    arr_of_code[(*pos)++] = val;

    return OK;
}

enum AsmFuncStatus WriteToBinFile (double *const arr_of_code, const size_t pos, FILE *bin_to_write) {

    assert (arr_of_code);
    assert (bin_to_write);

    int writes = -1;

    if ((writes = fwrite (arr_of_code + pos, sizeof (arr_of_code[0]), 1, bin_to_write)) == 1)
        LOG_PRINT_ASM (ASM_LOG_FILE, "Successful write: wrote ");

    else
        LOG_PRINT_ASM (ASM_LOG_FILE, "Write was failed: expected to write ");

    LOG_PRINT_ASM (ASM_LOG_FILE, "value %.5lf in code array to position %Iu (", arr_of_code[pos], pos);

    for (int current_byte = sizeof (double) * 8 - 1; current_byte >= 0; current_byte--)
        LOG_PRINT_ASM (ASM_LOG_FILE, "%d",
                       ((((long long)(arr_of_code[pos]) & (1 << current_byte)) == 0 ? 0 : 1)));

    LOG_PRINT_ASM (ASM_LOG_FILE, ")\n");

    return OK;
}

enum AsmFuncStatus PrintError (const size_t line, const char* const string_with_error) {

    assert (string_with_error);

    printf ("Syntax error at line %d: %s\n", line, string_with_error);

    return OK;
}

enum AsmFuncStatus FindCommentaryInString (PtrToStr *const ptr_to_strs, const size_t curr_str) {

    assert (ptr_to_strs);

    char *is_commentary = strchr (ptr_to_strs[curr_str].pointer_to_string, COMMENTARY_MARK);

    if (is_commentary)
        *is_commentary = '\0';

    return OK;
}

enum AsmFuncStatus ParseAndSetArgs (int command_num,              const char* const asm_string,
                                    double * const array_of_code, size_t *const position,
                                    const int have_arg) {
    if (have_arg == 0) {  //TODO have args instead num

        EmitCodeNoArg (array_of_code, position, command_num);

        return OK;
    }

    size_t current_pos_in_string = 0;

    bool has_bracket = IsSquareBracket (asm_string, &current_pos_in_string, '[');

    if (current_pos_in_string == 0 || IsRestStringEmpty (asm_string, current_pos_in_string))
        return FAIL;

    double value = NAN;
    size_t temp_current_pos_in_string = 0;

    sscanf (asm_string + current_pos_in_string, "%lf%n", &value, &temp_current_pos_in_string);

    current_pos_in_string += temp_current_pos_in_string;

    if (!isnan (value)) {

        command_num |= ARG_FORMAT_IMMED;

        EmitCodeArg (array_of_code, position, command_num, value);
    }

    else {

        char reg_symbol = '\0';

        sscanf (asm_string + current_pos_in_string, "r%cx%n", &reg_symbol, &temp_current_pos_in_string);

        if (reg_symbol != '\0' && tolower (reg_symbol) >= 'a' && tolower (reg_symbol) <= 'd') {

            current_pos_in_string += temp_current_pos_in_string;

            command_num |= ARG_FORMAT_REG;

            int reg_number = reg_symbol - 'a' + 1;

            sscanf (asm_string + current_pos_in_string, "+ %lf%n", &value, &temp_current_pos_in_string);

            if (isnan (value))
                EmitCodeReg (array_of_code, position, command_num, reg_number);

            else {

                current_pos_in_string += temp_current_pos_in_string;

                command_num |= ARG_FORMAT_IMMED;

                EmitCodeRegAndArg (array_of_code, position, command_num, reg_number, value);
            }
        }
    }

    if (has_bracket) {

        if (IsSquareBracket   (asm_string, &current_pos_in_string, ']') &&
            IsRestStringEmpty (asm_string, current_pos_in_string))

            return OK;
    }

    else if (IsRestStringEmpty (asm_string, current_pos_in_string))
        return OK;
printf("fail");
    return FAIL;
}

enum AsmFuncStatus JumpParse (const int command_num, const char* const asm_string,
                              double * const array_of_code, size_t *const position,
                              LabelForJump *const label_jmp, const size_t label_count,
                              const int compilation_num) {

    char current_label_name[MAX_WORD_LENGTH] = "";

    size_t current_pos_in_string = 0;

    sscanf (asm_string + current_pos_in_string, "%*s %s%n", current_label_name, &current_pos_in_string);

    for (size_t i = 0; i < label_count; i++)
        if (strcmp (current_label_name, (label_jmp[i].name)) == 0) {

            array_of_code[(*position)++] = command_num;
            array_of_code[(*position)++] = (label_jmp[i].address);

            if (IsRestStringEmpty (asm_string, current_pos_in_string))
                return OK;
        }

    if (compilation_num == 1) {

        *position += 2;

        return OK;
    }

    return FAIL;
}

bool IsRestStringEmpty (const char *const string_to_check, size_t position_in_string) {

    char current_symbol = *(string_to_check + position_in_string);

    while (current_symbol != '\0') {

        if (!isspace (current_symbol))
            return false;

        current_symbol = *(string_to_check + (++position_in_string));
    }

    return true;
}

bool IsSquareBracket (const char *const string_to_check, size_t *position_in_string,
                      const char bracket_type) {

    char check_bracket = '\0';

    sscanf (string_to_check, "%*s %n%c", position_in_string, &check_bracket);

    if (check_bracket == bracket_type) {

        (*position_in_string)++;

        return true;
    }

    return false;
}

enum AsmFuncStatus PrintJumpLabel (const LabelForJump *const label_jmp) {

    printf ("number of label:    \t");
    printf ("name of label:      \t");
    printf ("address of label:   \t\n");

    for (size_t i = 0; i < MAX_NUM_OF_LABELS; i++) {

        printf ("%-*d\t",   MAX_WORD_LENGTH, i);
        printf ("%-*.*s\t", MAX_WORD_LENGTH, MAX_WORD_LENGTH, label_jmp[i].name);

        if (label_jmp[i].name[0] != '\0')
            printf ("%-*d\t",   MAX_WORD_LENGTH, label_jmp[i].address);

        printf ("\n");
    }

    return OK;
}
