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
#define ABSOLUTE "00"
#define EXTERNAL "01"
#define RELOCATABLE "10"
#define OPCODE_LENGTH 5
#define OPCODE_AMOUNT 16
#define BINARY_LENGTH 11
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31
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

typedef struct opcode
{
    int decimal;
    char *name;
    char *code;
    int type;
} opcode;

/**
 * @brief The method checks if the label is in the standards
 * @param temp The string that will be checked
 * @param lable The storage for the label
 * @return true if it is a lable , false if it is not a label
 */
bool check_label(char *temp, char *label);

/**
 * @brief The method checks if the first argument in line is a label
 * @param line The string that will be checked
 * @param lable A pointer to array to store the lable name in
 * @return true if it is a label , false if it is not a label
 */
bool isLabel(char *line, char *label);

/**
 * @brief The method checks if the string contains the work ".entry"
 * @param line The string that will be checked
 * @return true if it is an entry , false if it is not an entry
 */
bool isEntry(char *line);

/**
 * @brief The method checks if the string contains the work ".extern"
 * @param line The string that will be checked
 * @return true if it is an extern , false if it is not an extern
 */
bool isExtern(char *line);

/**
 * @brief The method checks if the string contains the work ".string/.struct/.data"
 * @param line The string that will be checked
 * @return true if it fullfills the requirements, false otherwise
 */
bool isDataSymbol(char *line);

/**
 * @brief The method checks if the string contains the work ".data"
 * @param line The string that will be checked
 * @return true if it is an data , false if it is not an data
 */
bool isDataDeclaration(char *line);

/**
 * @brief The method checks if the string contains the work ".string"
 * @param line The string that will be checked
 * @return true if it is an string , false if it is not an string
 */
bool isStringDeclaration(char *line);

/**
 * @brief The method checks if the string contains the work ".struct"
 * @param line The string that will be checked
 * @return true if it is an struct , false if it is not an struct
 */
bool isStructDeclaration(char *line);

/**
 * @brief The method checks if the string is empty
 * @param line The string that will be checked
 * @return true if the string is empty , false if it is not
 */
bool isEmptyLine(char *line);

/**
 * @brief The method checks if the string starts with ;
 * @param line The string that will be checked
 * @return true if the string is comment , false if it is not
 */
bool isComment(char *line);

/**
 * @brief The method extarts label name of entry from struct
 * @param entryline: The line that contains .entry
 * @return label name
 */
char *getEntry(char *entryline);

/**
 * @brief The method trims the spaces from the left and the right of the line.
 * @param line The line that contains spaces
 * @return Trimmed line
 */
char *trim(char *line);

/**
 * @brief The method builds the binary data of the instruction
 * @param line command to identify
 * @param type type of opcode
 * @param binarydata storage for binary conversion
 * @return true if the command is valid
 */
bool check_opcode(char *line, int *type, char **binarydata);

/**
 * @brief The method checks if the string contains a keyword
 * @param line The string that will be checked
 * @return true if it is a keyword , false if it is not
 */
bool isKeyword(char *line);

/**
 * @brief The method checks if the string contains a register
 * @param line The string that will be checked
 * @return true if it is a register , false if it is not
 */
bool isRegister(char *line);

/**
 * @brief The method checks if the string contains a structure definition
 * @param line The string that will be checked
 * @return true if it is a structure , false if it is not
 */
bool isStruct(char *line);

/**
 * @brief The method checks if the string contains a number
 * @param line The string that will be checked
 * @return true if it is a number , false if it is not
 */
bool isNumber(char *line);

/**
 * @brief The method checks if the instruction is valid
 * @param line The string that will be checked
 * @param type instruction type
 * @return true if it is a valid instruction , false if it is not
 */
bool isCommand(char *line, int *type);

/**
 * @brief The method checks the operand if the operand is valid operand and adds the right addressing to binary data
 * @param operand The operand to check
 * @param binarydata pointer to the symbol binary data
 * @return true if it is a valid opreand, false otherwise
 */
bool checkoperand(char *operand, char **binarydata);

/**
 * @brief The method check that the number is valid
 * @param line Number data
 * @param binarydata pointer to the symbol binary data
 * @return true if it is a valid number, false otherwise
 */
bool checkNumbers(char *line, char **binarydata);

/**
 * @brief The method check that string data is valid and saves it to the symbol
 * @param line String data
 * @param binarydata pointer to the symbol binary data
 * @return true if it is a valid string, false otherwise
 */
bool checkString(char *line, char **binarydata);

/**
 * @brief The method check that struct data is valid and saves it to the symbol
 * @param line Struct data
 * @param binarydata pointer to the symbol binary data
 * @return true if it is a valid struct, false otherwise
 */
bool checkStruct(char *line, char **binarydata);

/**
 * @brief The method checks for the binary opcode of the insturction
 * @param line The instruction
 * @return the binary representation of the instruction
 */
char *getopcode(char *line);

/**
 * @brief The method converts a decimal to binary
 * @param num The number
 * @return Binary representation of a number
 */
char *convert_decimal_binary(long num);

#endif