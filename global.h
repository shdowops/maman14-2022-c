#ifndef GLOBAL_H
#define GLOBAL_H
#define ORIGINAL_EXT ".as"
#define EXPANDED_EXT ".am"
#define SEPARATOR "."
#define MAX_LINE_LENGTH 81
#define MAX_LABLE_LENGTH 30
#define START_OF_LINE 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

char *isLabel(char *line);
bool isEmptyLine(char *line);
bool isComment(char *line);
char *trim(char *line);
int IC, DC;
#endif