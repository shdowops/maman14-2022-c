#include "firstpass.h"

long IC, DC;
long linenumber;
extern Symbol *head, *tail;

void firstpass(char *filename)
{ 
    char line[MAX_LINE_LENGTH], trimmedline[MAX_LINE_LENGTH], label[MAX_LABEL_LENGTH];
    bool is_label, no_error, is_data, is_code, is_entry, is_extern;
    FILE *processedfile = fopen(filename, "r");
    head = NULL;
    IC = 100;
    DC = linenumber = 0;
    no_error = true;
    is_label = is_data = is_code = is_entry = is_extern = false;

    /*read next line from file*/
    if (processedfile == NULL)
    {
        /* Add error unable to open file*/
        alertFileError(ER_OPEN_FILE);
        return;
    }

    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        ++linenumber;
        strcpy(trimmedline,trim(line));
        /*trimmedline = trim(line);*/
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*is it a label? */


        /*check if .data? .string? .struct? */
        if ((is_data = isDataSymbol(trimmedline)))
            if (is_label)
            {
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/

                continue;
            }

        /*if .extern? .entry? */
        if ((is_entry = isEntry(trimmedline)) || (is_extern = isExtern(trimmedline)))
            if (is_extern)
            {
                 no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
                continue;
            }

        is_code = true;
        if (is_label)
        {
            no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
            /* insert to symbol as code with IC value*/
            no_error &= check_opcode(trimmedline);
            IC++;
        }
        /* check instruction, if not exist, add error. */

        /*check operands and count them*/
        /*build binary code of the instruction*/
        /* IC --> IC +L */
    }
    /* Finished reading the file*/
    print_symbol(head);
    if (!no_error)
        return;

    /* update symbol list data adding the right IC */
    updateData(head);
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

void updateData(Symbol *head)
{
     while (head != NULL)
    {
        if (head->is_Data)
            head->address += IC;
        head = head->next;
    }
}