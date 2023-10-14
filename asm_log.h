#ifndef ASM_LOG_H
#define ASM_LOG_H


#define ASSEMBLING_LOG_TXT    "asm log.txt"

FILE *LogFileOpen (const char *log_file);

void LogFileClose (void);


#endif

