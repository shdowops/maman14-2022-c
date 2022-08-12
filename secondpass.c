#include "secondpass.h"
extern long IC, DC;
void secondpass(char * filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline, label[MAX_LABEL_LENGTH];
    bool is_error;
    
    FILE *processedfile = fopen(filename, "r");
    IC = 0;
    is_error = false;
    /*read next line from file*/
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        trimmedline = trim(line);
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        /* is label ?*/
        if(isLabel(trimmedline, label))
            /*skip to next field*/
            continue;

        /* is data? string? struct? extern? */
        if(isDataSymbol(trimmedline)|| isExtern(trimmedline))
            continue;

        /* is entry */

        if(isEntry(trimmedline))
        {
            char * entry = getEntry(trimmedline);
            if(entry == NULL)
                printf("Error - empty entry statement\n");
        /* insert entry to entry symbol table */
            continue;
        }
        
        /* finish encoding operands */
        /* update IC -> IC + L */
    }
    /* end reading file */

    if(is_error)
        /*print error*/
        return;

    printf("Finito\n");
    /* save files */
}