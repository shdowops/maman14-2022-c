#include "secondpass.h"
extern int IC, DC;
void secondpass(char * filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline;
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
        if(isLabel(trimmedline))
            /*skip to next field*/
            continue;

        /* is data? string? struct? extern? */
        if(isDataSymbol(trimmedline)|| isExtern(trimmedline))
            continue;

        /* is entry */

        if(isEntry(trimmedline))
        /* insert entry to entry symbol table */
            continue;
        
        /* finish encoding operands */
        /* update IC -> IC + L */
    }
    /* end reading file */

    if(is_error)
        /*print error*/
        return;
    /* save files */
}