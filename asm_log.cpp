#include <stdlib.h>

#include "asm_log.h"

FILE *LOG_FILE = LogFileOpen (ASSEMBLING_LOG_TXT);

FILE *LogFileOpen (const char *log_file) {

    atexit (LogFileClose);

    return fopen (log_file, "w");
}

void LogFileClose (void) {

    if (LOG_FILE)
        fclose (LOG_FILE);

    LOG_FILE = NULL;
}
