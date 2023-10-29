#ifndef SPU_H
#define SPU_H


#include "mystacklib/my_stack_func.h"

#define BYTE_CODE  "byte code.bin"

#define PUSH(arg)  StackPush (&spu -> stk, arg)

#define POP(reg)   StackPop (&spu -> stk, &spu -> regs[reg]));
   //??

const int ARG_FORMAT_IMMED  = (1 << 5);
const int ARG_FORMAT_REG    = (1 << 6);

const int BYTE_MASK_FOR_CMD = 0x1F;

enum SpuFuncStatus {

    SPU_FUNC_OK,
    SPU_FUNC_FAIL
};

struct SpuStruct {

    Stack stk;
    int regs[4]; // rax, rbx, rcx, rdx
};

#endif
