#ifndef ASM_FUNC_H
#define ASM_FUNC_H


#define DEBUG


#define ASM_FILE              "program on asm.txt"

#define BYTE_CODE             "byte code.bin"


#ifdef DEBUG
    #define ON_DEBUG(...)     __VA_ARGS__
#else
    #define ON_DEBUG(...)
#endif


enum AsmFuncStatus {

    OK,
    FAIL
}

enum Commands {

    #define DEF_CMD(name, num)  CMD_##name = num,

    #include "commands.h"

    #undef DEF_CMD
}


#endif
