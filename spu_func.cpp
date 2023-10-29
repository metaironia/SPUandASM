#include <assert.h>
#include <stdio.h>
#include <string.h>

//#include "mystacklib/my_stack_func.h"
#include "spu_func.h"
#include "commands.h"

enum SpuFuncStatus RunByteCode (FILE *bin_file) {

    assert (bin_file);

    SpuStruct main_spu = {};

    StackCtor (&main_spu -> stk);

    long long command = 0;

    double code_array = {};     //TODO fix code array size

    for (size_t i = 0; feof (bin_file); i++)
        fread (&code_array[i], sizeof (code_array[0]), 1, bin_file);

    size_t position_in_code_array = 0;

    while (1) {    //TODO skip empty cmd

        command = (long long) code_array[position_in_code_array];

        switch (cmd & BYTE_MASK_FOR_CMD) {

            case CMD_PUSH: {

                int arg = 0

                double prev_cmd = cmd;

                fread (&cmd, sizeof (cmd), 1, bin_file);

                if (prev_cmd & ARG_FORMAT_IMMED != 0)
                    PUSH (arg);

                else if (prev_cmd & ARG_FORMAT_REG != 0)
                    PUSH (&spu -> regs[arg]);

                break;
            }

            case CMD_POP: {

                int reg = 0;

                fread (&reg, sizeof (reg), 1, bin_file);

                POP (reg);

                break;
            }

            case CMD_ADD:

                int first_number = 0;

                PUSH (POP + POP);  //??

                break;

            case CMD_HLT:

                return FAIL;
        }
    }
}

double *GetArgument (const double *code_arr, size_t *code_arr_position) {

    assert (code_arr);

    long long cmd = code_arr[(*code_arr_position)++]

    static double result = 0;

    if (cmd & ARG_FORMAT_IMMED)
        result += code[(*code_arr_position)++];

    if (cmd & ARG_FORMAT_REG)
        result += regs[(*code_arr_position)++];

    //TODO RAM

    return &result;
}
