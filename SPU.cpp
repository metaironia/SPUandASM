#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>

#include "mystacklib/my_stack_func.h"


int main (const int argc, const char *argv[]) {

//============================

    FILE* byte_code = fopen (BYTE_CODE, "rb");
    assert (byte_code);

    SpuStruct main_spu = {};

    StackCtor (&main_spu -> stk);

    RunByteCode (byte_code, main_spu)
}
