#include "secondpass.h"
extern long IC, DC;
extern Symbol *head, *tail;
void secondpass(char *filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline, label[MAX_LABEL_LENGTH];
    bool is_error;
    bool no_error, is_data, is_code, is_entry, is_extern;
    FILE *processedfile = fopen(filename, "r");
    memset(label,0,MAX_LABEL_LENGTH-1); /*Reset the label to nothing*/

    
    if (processedfile == NULL) /*If file was not opened*/
    {
        alertFileError(ER_OPEN_FILE);
    }
    else /*File was opened*/
    {
        IC = 0;
        is_error = false;
        /*read next line from file*/
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
        {
            trimmedline = trim(line);
            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;

            /* is label ?*/
            if (isLabel(trimmedline, label))
                /*skip to next field*/
                continue;

            /* is data? string? struct? extern? */
            if (isDataSymbol(trimmedline) || isExtern(trimmedline))
                continue;

            /* is entry */

            if (isEntry(trimmedline))
            {
              char *entry;
               is_data = is_code = is_entry = is_extern = false;
                entry = getEntry(trimmedline);
                if (entry == NULL)
                    alertError(ER_EMPTY_ENTREY);
                else
                {
                    is_entry = true;
                    no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /* insert to symbol as code with IC value*/
                }
                continue;
            }

            /* finish encoding operands */
            /* update IC -> IC + L */
        }
    }
    /* end reading file */

    if (is_error)
        /*print error*/
        return;

    printf("filename:%s\n", filename);
    /* save files */
}