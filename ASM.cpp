#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>

#include "oneginlib/functions_for_input.h"
#include "asm_func.h"


int main (const int argc, const char *argv[]) {

//============================ Inputting asm file part =================================

    FILE *asm_file = fopen (ASM_FILE, "rb");                 //TODO func from there
    assert (asm_file);

    struct stat asm_file_stat = {};
    stat (asm_file, &asm_file_stat);

    char *buf = BufferMaker (asm_file_stat.st_size);

    FileToBuf (asm_file, buf, asm_file_stat.st_size);

    fclose (asm_file);                                       //TODO func to there
    asm_file = NULL;

    size_t number_of_strings = StringCounter (buf, asm_file_stat.st_size);

    PtrToStr *pointers_to_strings = PointersToStringsMaker (number_of_strings);

    assert (pointers_to_strings);

    SetPointersToBuf (pointers_to_strings, buf, asm_file_stat.st_size, number_of_strings);

    rSymbolChecker (pointers_to_strings, number_of_strings);

//========================== ASM file analysis and byte code creation ==================================

    FILE *byte_code = fopen (BYTE_CODE, "wb");
    assert (byte_code);

    ON_DEBUG (FILE *asm_debug = fopen (ASSEMBLING_DEBUG_TXT, "w"));
    ON_DEBUG (assert (asm_debug));

    int code_array[number_of_strings * 2] = {};
    size_t position_in_code_array = 0;

    for (size_t current_string = 0; current_string < number_of_strings, current_string++)
        Assemble (pointers_to_strings, current_string, code_array, position_in_code_array, BYTE_CODE);

    fclose (byte_code);
    byte_code = NULL;

    return 0;
}
