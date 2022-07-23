#include "firstpass.h"
extern int IC, DC;

void firstpass(char *filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline;
    bool is_label, is_entry, is_extern, is_datasymbol;
    FILE *processedfile = fopen(filename, "r");
    IC = DC = 0;
    is_label = is_entry = is_extern = is_datasymbol = false;
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
            is_datasymbol = isDataSymbol(trimmedline);
            /*if label flaged*/
            /*insert to symbol list with data flag with DC value (if exist send error)*/
            /*continue */

            /*if .extern? .entry? */
            is_entry = isEntry(trimmedline);
            is_extern = isExtern(trimmedline);
            /*insert to symbol list*/

            /* if flag is label */
            /*Insert to symbol list as IC error if already exist*/
            /* check instruction, if not exist, add error. */
            /*check operands and count them*/
            /*build binary code of the instruction*/
            /* IC --> IC +L */
            is_label = is_entry = is_extern = is_datasymbol = false;
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