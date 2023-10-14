#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"
#include "commands.h"

enum RunByteCode (FILE *bin_file, SpuStruct *spu) {

    int cmd = 0;

    fread (&cmd, sizeof (cmd), 1, bin_file);    //TODO skip empty cmd

    switch (cmd) {

        case CMD_PUSH: {

            int arg = 0

            fread (&cmd, sizeof (cmd), 1, bin_file);

            StackPush (spu -> stk, arg);

            break;
        }

        case CMD_POP: {

            int reg = 0;

            fread (&reg, sizeof (reg), 1, bin_file);

            (spu -> regs[reg]) = StackPop (spu -> stk);

            break;
        }

        case CMD_ADD:

            StackPush (spu -> stk, StackPop(spu -> stk) + StackPop(spu -> stk));

            break;

        case CMD_HLT:

            return
    }
}
