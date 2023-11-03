#ifndef SPU_H
#define SPU_H


#include "mystacklib/my_stack_func.h"


#define PUSH(arg)          StackPush (&(main_spu.stk), arg)

#define POP                StackPop (&(main_spu.stk))

#define PUSH_RET           StackPush (&(main_spu.stk_ret_addresses), position_in_code_array + 2)

#define POP_RET            StackPop (&(main_spu.stk_ret_addresses))


const int ARG_FORMAT_IMMED = (1 << 5);
const int ARG_FORMAT_REG   = (1 << 6);
const int ARG_FORMAT_RAM   = (1 << 7);

const int BYTE_MASK_FOR_CMD = 0x1F;

enum SpuFuncStatus {

    SPU_FUNC_OK,
    SPU_FUNC_FAIL
};

struct SpuStruct {

    Stack stk;
    Stack stk_ret_addresses;
    double regs[4]; // rax, rbx, rcx, rdx
    double RAM[100]; // 100 because of DED advice
};

enum SpuFuncStatus RunByteCode (FILE *bin_file);

enum SpuFuncStatus CommandLineArgChecker (const int argcc, const char *argvv[]);

const char *BytecodeFileName (const char *argvv[]);

double *GetArgument (const double *code_arr, size_t *code_arr_position, const char *const command_name,
                     double *spu_RAM, double *spu_regs);

#endif
