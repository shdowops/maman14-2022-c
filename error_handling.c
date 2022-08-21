#include "error_handling.h"

void alertFileError(char *desc)
{
	fprintf(stderr, "[%s] : %s %s\n", filename, "[Error] ", desc);
}

void alertError(char *desc)
{
	fprintf(stderr, "[%s]->[Please revise line - %ld] %s %s]\n", filename, linenumber, "[Error-", desc);
}
