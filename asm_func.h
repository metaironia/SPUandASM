#ifndef ASM_FUNC_H
#define ASM_FUNC_H


#define ASM_FILE              "program on asm.txt" //TODO make flag instead of const here

#define BYTE_CODE             "byte code.bin"


const char COMMENTARY_MARK = ';';

enum AsmFuncStatus {

    OK,
    FAIL
};

const int ARG_FORMAT_IMMED = (1 << 4);
const int ARG_FORMAT_REG   = (1 << 5);

enum Commands {

    #define DEF_CMD(name, num)  CMD_##name = num,

    #include "commands.h"

    #undef DEF_CMD
};

enum AsmFuncStatus Assemble (PtrToStr *const ptrs_to_strings, const size_t current_str,
                             double *const code_arr, size_t *const position_in_code_arr);

enum AsmFuncStatus RegFind (PtrToStr *ptrs_to_strs, size_t curr_str, int *reg_number);

enum AsmFuncStatus EmitCodeArg (double *const array_of_code,  size_t *const position,
                                int command_code, double val);

enum AsmFuncStatus EmitCodeReg (double *const array_of_code,  size_t *const position,
                                int command_code, int reg);

enum AsmFuncStatus EmitCodeNoArg (double *const array_of_code,  size_t *const position,
                                  int command_code);

enum AsmFuncStatus FindCommentaryInString (PtrToStr *const ptr_to_strs, const size_t curr_str);

enum AsmFuncStatus WriteToBinFile (double *const arr_of_code, size_t pos, FILE *bin_to_write);


#endif
