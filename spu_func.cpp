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

    double cmd = 0;

    fread (&cmd, sizeof (cmd), 1, bin_file);    //TODO skip empty cmd

    if (cmd == 0)
        return FAIL;

    switch (cmd & 0xF) {

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
