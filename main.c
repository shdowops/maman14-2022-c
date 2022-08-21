#include "main.h"
int main(int argc, const char *argv[])
{
    FILE *fptr;

    int i;
    if (argc == 1) /* If no files specified in CLI */
    {
        alertFileError(NO_FILE_SPECIFIED);
        return 1;
    }
    for (i = 1; i < argc; i++)
    {
        filename = malloc(strlen(argv[i]) + MAX_EXT_LENGTH);
        strcpy(filename, argv[i]);
        strcat(filename, ORIGINAL_EXT); /*adding .as to file name*/
        fptr = fopen(filename, "r");

        if (fptr == NULL) /*error opening file */
        {
            alertFileError(FILENOTFOUND);
            continue;
        }
        else
        {
            preprocessor(fptr, filename);
            fclose(fptr);
            firstpass(filename);
        }
        free(filename);
    }
    return 0;
}