#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>

#include "mystacklib/my_stack_func.h"
#include "spu_func.h"


int main (const int argc, const char *argv[]) {

//============================

    FILE* byte_code = fopen (BYTE_CODE, "rb");
    assert (byte_code);

    RunByteCode (byte_code);

    return 0;
}
