#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <math.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"
#include "math_operation.h"


#define JMP_CODE                                        {position_in_code_array =                         \
                                                         (size_t) code_array[position_in_code_array + 1]; \
                                                         printf("AAAA %Iu\n", position_in_code_array);}


#define DEF_JMP                                          DEF_CMD


#define DEF_COND_JMP(cmd_name, cmd_code, have_arg, ...)  DEF_CMD (cmd_name, cmd_code, have_arg,           \
                                                                 {double first_num = POP;                 \
                                                                  double second_num = POP;                \
                                                                                                          \
                                                                  if (__VA_ARGS__(first_num, second_num)) \
                                                                      {JMP_CODE}                          \
                                                                  else                                    \
                                                                      position_in_code_array += 2;})


#define DEF_CMD(cmd_name, cmd_code, have_arg, ...)       case cmd_code:                                   \
                                                             {__VA_ARGS__}                                \
                                                             break;

enum SpuFuncStatus RunByteCode (FILE *bin_file) {

    assert (bin_file);

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
fprintf(stderr, "getter\n");
    bool is_pop = (strcmp ("pop", command_name) == 0);
    bool pop_arg_immed = false;
    bool pop_arg_ram = false;

    result = 0;

    if (cmd & ARG_FORMAT_IMMED) {

        if (is_pop)
            pop_arg_immed = true;
fprintf(stderr, "immed\n");
        result += code_arr[(*code_arr_position)++];
fprintf(stderr, "result = %d\n", (long long) result);
fprintf(stderr, "crash");
    }

    if (cmd & ARG_FORMAT_REG) {
fprintf(stderr, "reg\n");
        address = (double *) spu_regs + (long long) code_arr[*code_arr_position];
fprintf(stderr, "result = %d\n", (long long) result);
        result += spu_regs[(long long) code_arr[(*code_arr_position)++]];
fprintf(stderr, "last reg");
    }

    if (cmd & ARG_FORMAT_RAM) {
fprintf(stderr, "ram\n");
        if (is_pop)
            pop_arg_ram = true;
fprintf(stderr, "address before = %d", (long long) address);
        address = (double *) spu_RAM + (long long) result;
fprintf(stderr, "address after = %d", (long long) address);
        result = spu_RAM[(long long) result];
    }
fprintf(stderr, "fall");
    if (is_pop) {
fprintf(stderr, "why");
        if (pop_arg_immed && !pop_arg_ram)
            return NULL;
        else
            return address;
    }
fprintf(stderr, "result address = %p, result = %d\n", &result, (long long) result);
    return &result;
}
