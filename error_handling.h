#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H
#define FILENOTFOUND "The requested file %s not found.\n"
#define LABEL_ALREADY_EXIST "The label %s previously declared.\n"
#define INSTRUCTION_NOT_EXIST "No such instraction %s.\n"
#define NO_FILE_SPECIFIED "No file specified for the compiler.\n"

void add_error(char *err);
#endif