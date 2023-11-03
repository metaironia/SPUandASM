#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <math.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"
#include "math_operation.h"


#define JMP_CODE                                        {position_in_code_array =                          \
                                                         (size_t) code_array[position_in_code_array + 1];} \


#define DEF_JMP                                          DEF_CMD


#define DEF_COND_JMP(cmd_name, cmd_code, have_arg, ...)  DEF_CMD (cmd_name, cmd_code, have_arg,            \
                                                                 {double first_num = POP;                  \
                                                                  double second_num = POP;                 \
                                                                                                           \
                                                                  if (__VA_ARGS__(first_num, second_num))  \
                                                                      {JMP_CODE}                           \
                                                                  else                                     \
                                                                      position_in_code_array += 2;})


#define DEF_CMD(cmd_name, cmd_code, have_arg, ...)       case cmd_code:                                    \
                                                             {__VA_ARGS__}                                 \
                                                             break;

enum SpuFuncStatus RunByteCode (FILE *bin_file) {

    assert (bin_file);

    if (SignAndVersionChecker (bin_file) == SPU_FUNC_FAIL)
        return SPU_FUNC_FAIL;

    struct stat bin_file_stat = {};
    fstat (fileno (bin_file), &bin_file_stat);

    SpuStruct main_spu = {};

    StackCtor (&(main_spu.stk), 1);
    StackCtor (&(main_spu.stk_ret_addresses), 1);

    long long command = 0;

    double *code_array = (double *) calloc (bin_file_stat.st_size, 1);

    for (size_t i = 0; !feof (bin_file); i++)
        fread (&code_array[i], sizeof (code_array[0]), 1, bin_file);

    size_t position_in_code_array = 0;

    while (1) {

        command = (long long) code_array[position_in_code_array];

        switch (command & BYTE_MASK_FOR_CMD) {

            #include "commands.h"

            default:
                return SPU_FUNC_FAIL;
        }
    }
}

double *GetArgument (const double *code_arr, size_t *code_arr_position, const char *const command_name,
                     double *spu_RAM, double *spu_regs) {

    assert (code_arr);

    long long cmd = (long long) code_arr[(*code_arr_position)++];

    static double result = 0;

    result = 0;

    double *address = NULL;

    bool is_pop = (strcmp ("pop", command_name) == 0);
    bool pop_arg_immed = false;
    bool pop_arg_ram = false;

    result = 0;

    if (cmd & ARG_FORMAT_IMMED) {

        if (is_pop)
            pop_arg_immed = true;

        result += code_arr[(*code_arr_position)++];
    }

    if (cmd & ARG_FORMAT_REG) {

        address = (double *) spu_regs + (long long) code_arr[*code_arr_position];

        result += spu_regs[(long long) code_arr[(*code_arr_position)++]];
    }

    if (cmd & ARG_FORMAT_RAM) {

        if (is_pop)
            pop_arg_ram = true;

        address = (double *) spu_RAM + (long long) result;

        result = spu_RAM[(long long) result];
    }

    if (is_pop) {

        if (pop_arg_immed && !pop_arg_ram)
            return NULL;
        else
            return address;
    }

    return &result;
}

enum SpuFuncStatus CommandLineArgChecker (const int argcc, const char *argvv[]) {

    assert (argvv);

    if (argcc < 2) {

        fprintf (stderr, "Not enough arguments.");

        return SPU_FUNC_FAIL;
    }

    if (argcc > 2) {

        fprintf (stderr, "Too much arguments.");

        return SPU_FUNC_FAIL;
    }

    return SPU_FUNC_OK;
}

enum SpuFuncStatus SignAndVersionChecker (FILE *bin_to_check) {

    assert (bin_to_check);

    char signature[SIGNATURE_SIZE_BYTES + 1] = {};
    double version = 0;

    int is_signature_read = fread (signature, 1, SIGNATURE_SIZE_BYTES, bin_to_check);

    fseek (bin_to_check, sizeof (double),     SEEK_SET);

    int is_version_read   = fread (&version,  sizeof (version),   1, bin_to_check);

    fseek (bin_to_check, sizeof (double) * 2, SEEK_SET);

    if (is_signature_read && is_version_read && IsDoubleEqual (version, SPU_VERSION) &&
        strcmp (signature, SPU_SIGNATURE) == 0)

        return SPU_FUNC_OK;

    else {

        fprintf (stderr, "Byte code is not compatible.");

        return SPU_FUNC_FAIL;
    }
}

const char *BytecodeFileName (const char *argvv[]) {

    return argvv[1];
}
