#ifndef GLOBAL_H
#define GLOBAL_H
#define ORIGINAL_EXT ".as"
#define EXPANDED_EXT ".am"
#define SEPARATOR "."
#define COMMA ','
#define ARGUMENT_SEPARATOR " ,."
#define EXTERN ".extern"
#define ENTRY ".entry"
#define DATA ".data"
#define COMMENT ';'
#define STRING ".string"
#define STRUCT ".struct"
#define LABELMARK ":"
#define LINE_SPACE " "
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define START_OF_LINE 0
#define NUM_OF_REGISTERS 8
#define NUM_OF_KEYWORDS 21
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "error_handling.h"
#include "symbol.h"

extern long linenumber;
extern char *filename;

/*
Base32 - "!","@","#","$","%","^","&","*",">","<","a","b","c","d","e","f",
         "g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v",
*/

/*
Description: check that the given label is legit.
*/
bool check_label(char *temp, char *label);
/*
Description: check if there is a lable in line
             return true if it does, false otherwise.
*/
bool isLabel(char *line, char *label);

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
Description: check if string contains .data
*/
bool isData(char *line);

/*
Description: check if string contains .string
*/
bool isString(char *line);

/*
Description: check if string contains .struct
*/
bool isStruct(char *line);

/*
Description: check if line contains data declaration
*/
bool contains(char *line, char *data);

/*
Description: Check if line contains only whitespace characters
*/
bool isEmptyLine(char *line);

/*
Description: Check if the line is comment - true, otherwise false.
*/
bool isComment(char *line);

/*
Description: get the entry label.
*/
char *getEntry(char *entryline);
/*
Description: trim spaces from the line, return the trimmed string.
*/
char *trim(char *line);

/*
Description: check if opcode exists.
*/
bool check_opcode(char *line);

/*
Description: check if label is keyword
*/
bool isKeyword(char *line);

/*
Description: check if it's a register.
*/
bool isRegister(char *line);

/*
Description: check if it's a command.
*/
bool isCommand(char *line, int * type);


/*Assisting function for the isCommand Method.
 *This method checks how many operands there are in the line
 */
int numOfTokens(char *tok);
#endif