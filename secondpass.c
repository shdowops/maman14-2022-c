#include "secondpass.h"
extern int IC, DC;
void secondpass(char * filename)
{
    char line[MAX_LINE_LENGTH];
    bool is_error;
    FILE *processedfile = fopen(filename, "r");
    IC = 0;
    /*read next line from file*/
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        /* is label ?*/
        if(isLabel(line))
            /*skip to next field*/
            continue;

        /* is data? string? struct? extern? */
        if(isDataSymbol(line)|| isExtern(line))
            continue;

        /* is entry */

        if(isEntry(line))
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