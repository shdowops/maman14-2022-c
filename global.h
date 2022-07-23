#ifndef GLOBAL_H
#define GLOBAL_H
#define ORIGINAL_EXT ".as"
#define EXPANDED_EXT ".am"
#define SEPARATOR "."
#define EXTERN ".extern"
#define ENTRY ".entry"
#define DATA ".data"
#define STRING ".string"
#define STRUCT ".struct"
#define MAX_LINE_LENGTH 81
#define MAX_LABLE_LENGTH 30
#define START_OF_LINE 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


/*
Description: check if there is a lable in line
             return true if it does, false otherwise.
*/
bool isLabel(char *line);

/*
Description: check if lines contains entry symbol
             True if it does, false otherwise.
*/
bool isEntry(char *line);

/*
Description: check if lines contains extern symbol
             True if it does, false otherwise.
*/
bool isExtern(char *line);

/*
Description: check if lines contains data string or struct symbol
             True if it does, false otherwise.
*/
bool isDataSymbol(char *line);

/*
Description: Check if line contains only whitespace characters
*/
bool isEmptyLine(char *line);

/*
Description: Check if the line is comment - true, otherwise false.
*/
bool isComment(char *line);

/*
Description: trim spaces from the line, return the trimmed string.
*/
char *trim(char *line);

int IC, DC;
#endif