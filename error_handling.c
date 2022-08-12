#include "error_handling.h"




/**Description: Prints an error while opening or creating a file
 *Parameters:
 *@desc: The description of the error
 *@fileName: the name of the file
 */
void alertFileError(char* desc, char* fileName)
{
	fprintf(stderr, "[%s] : %s %s\n", fileName, "[Error] -> ", desc);
}