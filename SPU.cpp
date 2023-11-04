#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"


int main (const int argc, const char *argv[]) {

    if (CommandLineArgChecker (argc, argv) == SPU_FUNC_FAIL)
        return -1;

    FILE* byte_code = fopen (BytecodeFileName (argv), "rb");
    assert (byte_code);

    if (SignAndVersionChecker (byte_code) == SPU_FUNC_FAIL)
        return -1;

    RunByteCode (byte_code);

    return 0;
}
