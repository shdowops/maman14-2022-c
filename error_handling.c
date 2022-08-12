#include "error_handling.h"




/** Prints an error while opening or creating a file
 *Parameters:
 *@desc: The description of the error
 */
void alertFileError(char* desc)
{
	fprintf(stderr, "[%s] : %s %s\n", filename, "[Error] ", desc);
}


/**
*A global alert that that prints an error message in regards to an error during a pass (compilation error)
*@desc: The description of the error
*/
void printError(char *desc )
{
	fprintf(stderr, "[%s]->[Please revise line - %d] %s %s]\n", filename, linenumber, "[Error-", desc);
}

 