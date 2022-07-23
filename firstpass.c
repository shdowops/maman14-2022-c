#include "firstpass.h"
extern int IC, DC;

void firstpass(char *filename)
{
    bool labelflag = false;
    char line[MAX_LINE_LENGTH], *temp;
    FILE *processedfile = fopen(filename, "r");
    IC = DC = 0;
    /*read next line from file*/
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        if(isEmptyLine(line) || isComment(line))
            continue;

        /*it is label?*/
        if ((temp = isLabel(line)) != NULL)
            labelflag = true;
            printf("is Label: %s", temp);

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
    }
    /* Finished reading the file*/

    /*if got errors
        , stop.

    update symbol list data adding the right IC*/

    /*Start second pass
    secondpass(filename);*/
}