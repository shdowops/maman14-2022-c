#define  _GNU_SOURCE
#include <stdio.h>
#include "main.h"

/*Main function to run the compiler*/
int main(int argc, const char *argv[])
{
    FILE *fptr;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int i;
    /*Check if a file name specified in cli*/
    if(argc==1){
        printf("No file specified for compiler\n");
        return 1;
    }
    /*At least one file in user input*/
    else{

        for (i=1;i<argc;i++)
        {
            char *filename = malloc(strlen(argv[i])+1);
            strcpy(filename, argv[i]);
            printf("filename=%s\n",filename);
            fptr=fopen(strcat(filename,".as"),"r"); 
            
            /*Read file, line by line*/
            while((read = getline(&line, &len, fptr)!= -1)){
                printf("%s", line);
            }
            printf("Closing file\n");
            free(line);
            fclose(fptr); 
        }
    }
    /*Finished processing all files without errors*/
    return 0;   
}