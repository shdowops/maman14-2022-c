#include "secondpass.h"
extern int IC, DC;
void secondpass(char * filename)
{
    IC = 0;
    /*read next line from file*/

        /* is label ?*/
            /*skip to next field*/
        /* is data? string? struct? extern? */
          /*  continue; */
        /* is entry */
            /* insert entry to entry symbol table */
            /*  continue; */
        
        /* finish encoding operands */
        /* update IC -> IC + L

    /* end reading file */

    /*if errors*/
        /*stop!!!!*/
    /* save files */
}