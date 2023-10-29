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

    double a = NAN;
    fread (&a, sizeof (a), 1, byte_code);
    printf("%lf", a);
   // RunByteCode (byte_code, main_spu);

    return 0;
}
