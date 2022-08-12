#ifndef FIRSTPASS_H
#define FIRSTPASS_H
#include "global.h"
#include "secondpass.h"
#include <stdbool.h>
/*
Description: Run the first pass on the expanded file
*/
void firstpass(char *filename);
void updateData(Symbol *head);
#endif