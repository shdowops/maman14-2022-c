#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H


/*File Errors*/
#define OPEN_FILE_ERROR "could not open the file.\n"
#define FILENOTFOUND "The requested file %s not found.\n"
#define LABEL_ALREADY_EXIST "The label %s previously declared.\n"
#define INSTRUCTION_NOT_EXIST "No such instraction %s.\n"
#define NO_FILE_SPECIFIED "No file specified for the compiler.\n"
#define LABEL_ALREADY_EXISTS "Label already exists.\n"


/**Description: Prints an error while opening or creating a file
 *Parameters:
 *@desc: error description
 *@fileName: the file name
 */
void alertFileError(char *desc, char *filename);

void add_error(char *err);
#endif