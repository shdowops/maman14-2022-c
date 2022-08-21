#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include "global.h"

/*File Errors*/
#define ER_FAIL_CREATE_FILE "Failure with creating file"
#define ER_OPEN_FILE "could not open the file"
#define NO_FILE_SPECIFIED "No file specified for the compiler"
#define FILENOTFOUND "The requested file not found"
#define ER_FILE_NAME_LENGTH "filename exceeds the proper length"
#define ER_NO_INPUT_FILE "Input files are missing"
#define ER_INPUT_FILE_NOT_EXIST "Input files do not exist"
#define ER_FILE_FAIL_NAME_MEM "Failure with allocating memory for the file name"

/*MACRO ERRORS*/
#define ER_EMPTY_MACRO "Macro declaration without a body. Macro is empty"

/*Label Errors*/
#define ER_LABEL_NOT_FIRST_ALPHA "Label must start with a letter"
#define ER_LABEL_TOO_LONG "The label is too long, max length allowed is 30 chars"
#define ER_LABEL_NAME_ILLEGAL "Label is a keyword or a register"
#define ER_LABEL_NO_COLON "A colon is required immediately after a label"
#define ER_LABEL_ALPHA "Label is not entirely alpha numeric"
#define ER_LABEL_ALREADY_EXISTS "Label already exists"
#define ER_SINGLE_LABEL "only a single label can be declared at a time"
#define ER_LABEL_NOT_DEFINED "Label is undefined"
#define ER_LABEL_CONVERTION "Cannot convert label address"
#define ER_DATA_LABEL_INVALID ".data label contains an invalid number"
#define ER_STRING_DECLARATION "A space is required following a .string declaration"
#define ER_DATA_DECLARATION "A space is required following  .data declaration"
#define ER_LABEL_IS_MISSING "A label is missing"
#define ER_LABEL_KEYWORD "A label cannot have the same name as a keyword"
#define ER_LABEL_REGISTER "A label cannot have the same name as a register"
#define ER_LABEL_SPACE "Label contains space before colon"
#define ER_IS_NOT_LABEL "Operand is not a label"

/*Instruction Errors*/
#define ER_INSTRUCTION_NOT_EXIST "Instraction %s does not exist"
#define ER_JUMPING_NOT_START_LABEL "Jumping with parameters must begin with a label"
#define NOT_VALID_OPERAND "The operand is not valid"
#define ER_MISSING_OPERANDS_IN_COMMAND "Operands are missing in the command"
#define ER_OPERANDS_OVERFLOW_IN_COMMAND "An overflow of operands in the command exists"
#define ER_DESTINATION_OPERAND "Destination operand does not exist"
#define ER_SOURCE_OPERAND "Source operand does not exist"
#define ER_OUT_OF_BOUND_STRUCT "Out of bound struct reference"
#define ER_NON_VALID_STRUCT "Not valid struct decleration"
#define ER_NO_STRUCT_DECLARED "There is no such sturct declared"

/*Data Errors*/
#define ER_DATA_BEGINS_WITH_COMMA ".data starts with comma"
#define ER_DATA_ENDS_WITHOUT_NUMBER ".data ends without a number"
#define ER_STRING_WITHOUT_QUOTES ".string declared without quotes"

/*Opcode Errors*/
#define ER_OPCODE_ILLEGAL "Illegal opcode"

/*Procedure Errors*/
/*First Pass*/
#define ER_FIRST_PASS "errors found during the first pass, operation will be discontinued"

/*Entry Extern Errors*/
#define ER_AFTER_ENTRY "After an entry a space is needed"
#define ER_AFTER_EXTERN "After extern a space is needed"
#define ER_EMPTY_ENTRY "Empty entry statement"

/*General Errors*/
#define ER_NUM_OUT_OF_RANGE "There is a distinct range for numbers. -256 to 256 is the range. The number you provided is out of this range or not integer"
#define ER_MEMORY_ALLOCATION "cannot allocate needed memory"
#define ER_DATA_TYPE_INVALID "Data type is invalid"
#define ER_SPACE_AFTER_COLON "A space is required after a colon"
#define VARIABLE_EQUALS_KEYWORD "A variable cannot have a name that is the same as a keyword"
#define OPERAND_EQUALS_KEYWORD "An operand cannot have a name that is the same as a keyword"
#define ERROR_UNKNOWN_DECLARATION "This declartion is unrecognized"

/**
 * @brief The method print a file error to stderr
 * @param desc Error description
 */
void alertFileError(char *desc);

/**
 * @brief The method prints an error in specific line to stderr
 * @param desc Error description
 */
void alertError(char *desc);

#endif