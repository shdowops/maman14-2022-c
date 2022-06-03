#include "main.h"
#include "preprocessor.h"

/*Main function to run the compiler*/
int main(int argc, const char *argv[])
{
    FILE *fptr;

    int i;
    /*Check if a file name specified in cli*/
    if (argc == 1)
    {
        printf("No file specified for compiler\n");
        return 1;
    }
    /*At least one file in user input*/
    for (i = 1; i < argc; i++)
    {
        char *fullfilename;
        char *filename = malloc(strlen(argv[i]) + 1);
        strcpy(filename, argv[i]);
        fullfilename = strcat(filename, ".as");
        fptr = fopen(fullfilename, "r");

        if (fptr == NULL)
            printf("Unable to open the file: %s\n", fullfilename);
        else
        {
            preprocessor(fptr);
        }
    }
    /*Finished processing all files without errors*/
    return 0;
}