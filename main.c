#include "main.h"
/*Main function to run the compiler*/
int main(int argc, const char *argv[])
{
    FILE *fptr;

    int i;
    /*Check if a file name specified in cli*/
    if (argc == 1)
    {
        alertFileError(NO_FILE_SPECIFIED);
        return 1;
    }
    /*At least one file in user input*/
    for (i = 1; i < argc; i++)
    {
        filename = malloc(strlen(argv[i]) + 1);
        strcpy(filename, argv[i]);
        strcat(filename, ORIGINAL_EXT);
        fptr = fopen(filename, "r");

        if (fptr == NULL)
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
    /*Finished processing all files without errors*/
    return 0;
}