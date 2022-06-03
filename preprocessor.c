#define _GNU_SOURCE
#include "preprocessor.h"
/* Preprocessor for macros */
int preprocessor(FILE *codefile)
{
    char *line = NULL;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, codefile) != -1))
    {
        printf("%s", line);
    }
    free(line);
    fclose(codefile);
    return 0;
}