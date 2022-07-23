#include "secondpass.h"
extern int IC, DC;
void secondpass(char * filename)
{
    char line[MAX_LINE_LENGTH];
    FILE *processedfile = fopen(filename, "r");
    IC = 0;
    /*read next line from file*/
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        /* is label ?*/
        if(isLabel(line))
            continue;
            /*skip to next field*/
        /* is data? string? struct? extern? */
        if(isDataSymbol(line))
            continue;
          /*  continue; */
        /* is entry */
        if(isEntry(line))
            continue;
            /* insert entry to entry symbol table */
            /*  continue; */
        
        /* finish encoding operands */
        /* update IC -> IC + L */
    }
    /* end reading file */

    /*if errors*/
        /*stop!!!!*/

    /* save files */
}