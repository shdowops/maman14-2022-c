#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 81
#define SEPARATOR "."
#define MACROSTART "macro"
#define MACROEND "endmacro"

typedef struct Macro
{
    char *name;
    char *macro;
    struct Macro *next;
} Macro;

void preprocessor(FILE *codefile, char *filename);
Macro *isMacro(char *str, Macro *head);
void  addToMacroList(Macro *newMacro,Macro *head);
void freeMacros(Macro *head);
#endif
