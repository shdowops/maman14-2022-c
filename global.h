#ifndef GLOBAL_H
#define GLOBAL_H
#define ORIGINAL_EXT ".as"
#define EXPANDED_EXT ".am"
#define ENTRY_EXT ".ent"
#define EXTERN_EXT ".ext"
#define OBJECT_EXT ".ob"
#define MAX_EXT_LENGTH 5
#define SEPARATOR "."
#define COMMA ','
#define ARGUMENT_SEPARATOR " ,"
#define EXTERN ".extern"
#define ENTRY ".entry"
#define DATA ".data"
#define COMMENT ';'
#define STRING ".string"
#define STRUCT ".struct"
#define LABELMARK ":"
#define LINE_SPACE " "
#define STRUCT_STRING_START "\""
#define INSTRUCTION_ARE_BITS "00"
#define OPCODE_LENGTH 5
#define OPCODE_AMOUNT 16
#define BINARY_LENGTH 11
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define START_OF_LINE 0
#define NUM_OF_REGISTERS 8
#define NUM_OF_KEYWORDS 21
#define NO_OPERANDS 0
#define ONE_OPERAND 1
#define TWO_OPERANDS 2
#define MIN_NUMBER -128
#define MAX_NUMBER 127
#define NUMBERSTART "#"
#define NUMBERLENGTH 9
#define STURCT_FIRST_ARG '1'
#define STRUCT_SECOND_ARG '2'
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "error_handling.h"
#include "symbol.h"

extern long IC, DC;
extern long linenumber;
extern char *filename;

typedef struct opcode{
	int decimal;
	char* name;
	char* code;
	int type;
} opcode;


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
bool isDataDeclaration(char *line);

/*
Description: check if string contains .string
*/
bool isStringDeclaration(char *line);

/*
Description: check if string contains .struct
*/
bool isStructDeclaration(char *line);


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
bool check_opcode(char *line, int *type, char *binarydata);

/*
Description: check if label is keyword
*/
bool isKeyword(char *line);

/*
Description: check if it's a register.
*/
bool isRegister(char *line);

/*
Description: check if it is a valid stracture.
*/
bool isStruct(char *line);

/*
Descti
*/
bool isNumber(char *line);

/*
Description: check if it's a command.
*/
bool isCommand(char *line, int * type);

/*
Description: check the first operand
*/
bool checkoperand(char *operand, char *binarydata);

/*
Description: Check if a number is valid
*/
bool checkNumbers(char * line, char **binarydata);

/*
Description: check that a string is valid
*/
bool checkString(char * line, char **binarydata);

/*
Description: check that struct is valid.
*/
bool checkStruct(char * line, char **binarydata);

/*
Description: Get opcode from line
*/
char* getopcode(char * line);

/*
Description convert decimal number to binary
*/
char *convert_decimal_binary(long num);

#endif