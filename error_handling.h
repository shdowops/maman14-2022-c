#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include "global.h"

/* File errors */
#define FILE_NAME_MEM_ALLOCATION_FAILURE "Could not allocate memory for the file name you provided"

#define ERROR_CREATE_FILE	"Could not create file"
#define MISSING_INPUT_FILE "missing input files "
#define FILENAME_TOO_LONG "filename is too long"

/*File Errors*/
#define ER_OPEN_FILE "could not open the file.\n"
#define NO_FILE_SPECIFIED "No file specified for the compiler.\n"
#define FILENOTFOUND "The requested file %s not found.\n"

/*Label Errors*/
#define ER_LABEL_NOT_FIRST_ALPHA_NUMERIC "Label not starting with alphanumeric\n"
#define ER_LABEL_TOO_LONG "The label is too long, max length allowed is 30 chars.\n"
#define ER_LABEL_NAME_ILLEGAL "Label is a keyword or a register.\n"
#define ER_LABEL_SPACE "There is a space before the colon in label declaration.\n"
#define ER_LABEL_ALPHA "Label is not entirely alpha numeric\n"
#define LABEL_ALREADY_EXISTS "Label already exists.\n"

/*Instruction Errors*/
#define INSTRUCTION_NOT_EXIST "No such instraction %s.\n"



/** A global alert that prints an error in relation to file
 *Parameters:
 *@desc: error description
 */
void alertFileError(char *desc);

/**
*A global alert that that prints an error message in regards to an error during a pass (compilation error)
*@desc: The description of the error
*/
void alertError(char *desc);

#endif