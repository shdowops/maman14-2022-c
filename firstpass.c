#include "firstpass.h"
extern int IC, DC;

void firstpass(char *filename)
{
    char line[MAX_LINE_LENGTH], *temp, *trimmedline;
    bool labelflag = false;
    FILE *processedfile = fopen(filename, "r");
    IC = DC = 0;
    /*read next line from file*/
    if (processedfile != NULL)
    {
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
        {
            trimmedline = trim(line);
            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;
                
            /*it is label? */
            temp = isLabel(trimmedline);
            if (temp != NULL)
                labelflag = true;
                
            /*check if .data? .string? .struct? */
            /*if label flaged*/
            /*insert to symbol list with data flag with DC value (if exist error)*/
            /*continue */

            /*if .extern? .entry? */
            /* if extern*/
            /*insert to symbol list*/

            /* if flag is label */
            /*Insert to symbol list as IC error if already exist*/
            /* check instruction, if not exist, add error. */
            /*check operands and count them*/
            /*build binary code of the instruction*/
            /* IC --> IC +L */
            labelflag = false;
        }
        /* Finished reading the file*/

        /*if got errors
            , stop.

        update symbol list data adding the right IC*/

        /*Start second pass*/
        secondpass(filename);
    }
    else
        /* Add error unable to open file*/
        printf("Unable to open file %s\n", filename);
}