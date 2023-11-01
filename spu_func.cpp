#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <math.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"


#define DEF_JMP(cmd_name, cmd_code, ...)  case cmd_code:                     \
                                             {__VA_ARGS__}                   \
                                             break;                          \

#define DEF_COND_JMP(...)

#define DEF_CMD(cmd_name, cmd_code, have_arg, ...)  case cmd_code:           \
                                                        {__VA_ARGS__}        \
                                                        break;               \


enum SpuFuncStatus RunByteCode (FILE *bin_file) {

    assert (bin_file);

    struct stat bin_file_stat = {};
    fstat (fileno (bin_file), &bin_file_stat);

    SpuStruct main_spu = {};

    StackCtor (&(main_spu.stk), 1);

    long long command = 0;

    double *code_array = (double *) calloc (bin_file_stat.st_size, 1);     //TODO fix code array size

    for (size_t i = 0; !feof (bin_file); i++)
        fread (&code_array[i], sizeof (code_array[0]), 1, bin_file);

    size_t position_in_code_array = 0;

    while (1) {    //TODO skip empty cmd

        command = (long long) code_array[position_in_code_array];

        switch (command & BYTE_MASK_FOR_CMD) {

            #include "commands.h"

            default:
                return SPU_FUNC_FAIL;
        }
    }
}

double *GetArgument (const double *code_arr, size_t *code_arr_position, const char *const command_name,
                     int *spu_RAM, int *spu_regs) {

    assert (code_arr);

    long long cmd = (long long) code_arr[(*code_arr_position)++];

    static double result = 0;

    double *address = NULL;
printf("getter\n");
    bool is_pop = (strcmp ("pop", command_name) == 0);
    bool pop_arg_immed = false;
    bool pop_arg_ram = false;

    result = 0;

    if (cmd & ARG_FORMAT_IMMED) {

        if (is_pop)
            pop_arg_immed = true;
printf("immed\n");
        result += code_arr[(*code_arr_position)++];
printf("crash");
    }

    if (cmd & ARG_FORMAT_REG) {
printf("reg\n");
        result += spu_regs[(long long) code_arr[*code_arr_position]];

        address = (double *) spu_regs + (long long) code_arr[(*code_arr_position)++];
    }

    if (cmd & ARG_FORMAT_RAM) {
printf("ram\n");
        if (is_pop)
            pop_arg_ram = true;

        result = spu_RAM[(long long) result];

        address = (double *) spu_RAM + (long long) result;
    }
printf("fall");
    if (is_pop) {
printf("why");
        if (pop_arg_immed && !pop_arg_ram)
            return NULL;
        else
            return address;
    }
printf("result address = %p, result = %d\n", &result, (long long) result);
    return &result;
}
