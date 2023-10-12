#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>

#include "my_stack_func.h"
#include "functions_for_input.h"
#include "asm_func.h"

#define ASM_FILE "program on asm.txt"

int main (void) {

    atexit(LogFileClose);

    FILE *asm_file = fopen (ASM_FILE, "rb");

    struct stat asm_file_stat;
    stat (ASM_FILE, &asm_file_stat);

    char *buf = BufferMaker (asm_file_stat.st_size);

    FileToBuf (asm_file, buf, asm_file_stat.st_size);

    fclose (ASM_FILE);

    size_t number_of_strings = StringCounter (buf, asm_file_stat.st_size);

    PtrToStr *pointers_to_strings = PointersToStringsMaker (number_of_strings);

    assert (pointers_to_strings);

    SetPointersToBuf (pointers_to_strings, buf, asm_file_stat.st_size, number_of_strings);

    rSymbolChecker (pointers_to_strings, number_of_strings);

    FILE *byte_code = fopen ("byte code.txt", "w");

    StringAnalyser (pointers_to_strings);
}
