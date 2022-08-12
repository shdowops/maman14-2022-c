#include "firstpass.h"

long IC, DC;
long linenumber;

void firstpass(char *filename)
{
    extern Symbol *head;
    Symbol *temp;
    char line[MAX_LINE_LENGTH], *trimmedline, label[MAX_LABEL_LENGTH];
    bool is_label, is_error, is_data, is_code, is_entry, is_extern;
    FILE *processedfile = fopen(filename, "r");
    head = NULL;
    IC = 100;
    DC = linenumber = 0;
    is_label = is_error = is_data = is_code = is_entry = is_extern = false;

    /*read next line from file*/
    if (processedfile == NULL)
    {
        /* Add error unable to open file*/
        printf("Unable to open file %s\n", filename);
        return;
    }

    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        ++linenumber;
        trimmedline = trim(line);
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*is it a label? */

        /*check if .data? .string? .struct? */
        if ((is_data = isDataSymbol(trimmedline)))
            if (is_label)
            {
                printf("Data Symbol + label\n");
                add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/
                continue;
            }

        /*if .extern? .entry? */
        if ((is_entry = isEntry(trimmedline)) || (is_extern = isExtern(trimmedline)))
            if (is_extern)
            {
                printf("It is extern!\n");
                add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
                continue;
            }

        is_code = true;

        printf("line=%s\n",trimmedline);
        if (is_label)
        {
            printf("Inside label + Command\n");
            add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
            /* insert to symbol as code with IC value*/

            IC++;
        }

        /* check instruction, if not exist, add error. */

        /*check operands and count them*/
        /*build binary code of the instruction*/
        /* IC --> IC +L */
    }
    /* Finished reading the file*/
    print_symbol(head);
    if (is_error)
        /* print errors */
        return;

    /* update symbol list data adding the right IC */
    temp = head;
    while (temp != NULL)
    {
        if (temp->is_Data)
            temp->address += IC;
        temp = temp->next;
    }
    /*   while(headptr != NULL)
       {
           headptr->dc+=IC;
           headptr=headptr->next;
       }
   */
    /*Start second pass*/
    fclose(processedfile);
    secondpass(filename);
}