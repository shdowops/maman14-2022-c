#ifndef SECONDPASS_H
#define SECONDPASS_H
#define SQUARE(x) ((x)*(x))
#include <stdio.h>

#include "global.h"
void secondpass(char *filename);
#endif

int binary_converter(char binary[]);

void save_files(FILE *ent_fptr, FILE *ext_fptr, FILE *obj_fptr);