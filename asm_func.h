#ifndef ASM_FUNC_H
#define ASM_FUNC_H


#define ASM_FILE              "program on asm.txt" //TODO make flag instead of const here

#define BYTE_CODE             "byte code.bin"



const char COMMENTARY_MARK = ';';

enum AsmFuncStatus {

    OK,
    FAIL
};

const int ARG_FORMAT_IMMED = (1 << 5);
const int ARG_FORMAT_REG   = (1 << 6);

enum Commands {

    #define DEF_CMD(name, num, have_arg, ...)  CMD_##name = num,

    #define DEF_COND_JMP DEF_JMP

    #define DEF_JMP(cmd_name, cmd_num, ...)

    #include "commands.h"

    #undef DEF_CMD

    #undef DEF_COND_JMP

    #undef DEF_JMP
};

const int MAX_WORD_LENGTH = 20;
const int MAX_NUM_OF_LABELS = 10;

struct LabelForJump {

    size_t address;
    char name[MAX_WORD_LENGTH];
};

enum AsmFuncStatus Assemble (PtrToStr *const ptrs_to_strings, const size_t current_str,
                             double *const code_arr, size_t *const position_in_code_arr,
                             LabelForJump *const labels, size_t *label_counter,
                             const int num_of_compilation);

enum AsmFuncStatus EmitCodeNoArg (double *const arr_of_code,  size_t *const pos,
                                  const int command_code);

enum AsmFuncStatus EmitCodeArg (double *const arr_of_code,  size_t *const pos,
                                const int command_code, const double val);

enum AsmFuncStatus EmitCodeReg (double *const arr_of_code,  size_t *const pos,
                                const int command_code, const int reg);

enum AsmFuncStatus EmitCodeRegAndArg (double *const arr_of_code,  size_t *const pos,
                                      const int command_code, const int reg, const double val);

enum AsmFuncStatus FindCommentaryInString (PtrToStr *const ptr_to_strs, const size_t curr_str);

enum AsmFuncStatus WriteToBinFile (double *const arr_of_code, size_t pos, FILE *bin_to_write);

enum AsmFuncStatus PrintError (const size_t line, const char* const string_with_error);

enum AsmFuncStatus ParseAndSetArgs (int command_num,              const char* const asm_string,
                                    double * const array_of_code, size_t *const position,
                                    const int num_of_args);

enum AsmFuncStatus JumpParse (const int command_num, const char* const asm_string,
                              double * const array_of_code, size_t *const position,
                              LabelForJump *const label_jmp, const size_t label_count,
                              int compilation_num);

bool IsRestStringEmpty (const char *const string_to_check, size_t position_in_string);

bool IsSquareBracket (const char *const string_to_check, size_t *position_in_string,
                      const char bracket_type);

enum AsmFuncStatus PrintJumpLabel (const LabelForJump *const label_jmp);

#endif
