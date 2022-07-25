#include "firstpass.h"
extern int IC, DC;

void firstpass(char *filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline;
    bool is_label, is_entry, is_extern, is_datasymbol, is_error;
    FILE *processedfile = fopen(filename, "r");
    IC = DC = 0;
    is_label = is_error = false;
    /*read next line from file*/
    if (processedfile != NULL)
    {
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
        {
            trimmedline = trim(line);
            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;

            /*it is label? */
            is_label = isLabel(trimmedline);

            /*check if .data? .string? .struct? */
            if (isDataSymbol(trimmedline))
                if (is_label)
                {
                    printf("Data Symbol + lable\n");
                    printf("%s\n",trimmedline);
                    /*insert tavit as data label with value of DC*/
                    /*determine symboltype encode the memory*/
                    /*update DC */
                    continue;
                }

            /*if .extern? .entry? */
            if( isEntry(trimmedline) || isExtern(trimmedline))
                if(isExtern(trimmedline))
                {
                    printf("It is extern!\n");
                    printf("%s\n",trimmedline);
                    /*add external symbols (one or more) to symbol list without a value*/
                    continue;
                }

            /* if flag is label */
            if(is_label)
            {
                printf("Inside label\n");
                printf("%s\n",trimmedline);
                /* insert to symbol as code with IC value*/
                /* check instruction, if not exist, add error. */
                /*check operands and count them*/
                /*build binary code of the instruction*/
                /* IC --> IC +L */
                IC++;
            }
        }
        /* Finished reading the file*/

        if (is_error)
            /* print errors */
                return;

        /* update symbol list data adding the right IC
            while(headptr != NULL)
            {
                headptr->dc+=IC;
                headptr=headptr->next;
            }
        */

        /*Start second pass*/
        secondpass(filename);
    }
    else
        /* Add error unable to open file*/
        printf("Unable to open file %s\n", filename);
}