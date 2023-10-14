#ifndef SPU_H
#define SPU_H


#include "mystacklib/my_stack_func.h"

#define BYTE_CODE             "byte code.bin"

enum SpuFuncStatus {

    OK,
    FAIL
};

struct SpuStruct {

    Stack stk;
    int regs[4]; // rax, rbx, rcx, rdx
};


#endif
