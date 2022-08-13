#ifndef GLOBAL_H
#define GLOBAL_H
#define ORIGINAL_EXT ".as"
#define EXPANDED_EXT ".am"
#define ENTRY_EXT ".ent"
#define EXTERN_EXT ".ext"
#define OBJECT_EXT ".ob"
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
#define OPCODE_LENGTH 5
#define OPCODE_AMOUNT 16
#define BINARY_LENGTH 10
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 30
#define START_OF_LINE 0
#define NUM_OF_REGISTERS 8
#define NUM_OF_KEYWORDS 21
#define NO_OPERANDS 0
#define ONE_OPERAND 1
#define TWO_OPERANDS 2
#define NUMBERSTART "#"
#define STURCT_FIRST_ARG '1'
#define STRUCT_SECOND_ARG '2'
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "error_handling.h"
#include "symbol.h"
char *Registers[NUM_OF_REGISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
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
bool checkoperand(char *firstop);

/*
Description: Check if a number is valid
*/
bool checkNumbers(char * line);

/*
Description: check that a string is valid
*/
bool checkString(char * line);

/*
Description: check that struct is valid.
*/
bool checkStruct(char * line);

/*
Description: Get opcode from line
*/
char* getopcode(char * line);


/*Assisting function for the isCommand Method.
 *This method checks how many operands there are in the line
 */
int numOfTokens(char *tok);


char *convert_decimal_Binary(long num);

#endif