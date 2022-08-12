#include "firstpass.h"

long IC, DC;
long linenumber;
extern Symbol *head, *tail;

void firstpass(char *filename)
{ 
    char line[MAX_LINE_LENGTH], trimmedline[MAX_LINE_LENGTH], label[MAX_LABEL_LENGTH], *token;
    bool is_label, no_error, is_data, is_code, is_entry, is_extern;
    FILE *processedfile = fopen(filename, "r");
    head = NULL;
    IC = 100;
    DC = linenumber = 0;
    no_error = true;

    /*read next line from file*/
    if (processedfile == NULL)
    {
        /* Add error unable to open file*/
        alertFileError(ER_OPEN_FILE);
        return;
    }

    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        init_label(label);
        is_label = is_data = is_code = is_entry = is_extern = false;
        ++linenumber;
        strcpy(trimmedline,trim(line));
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*is it a label? */

        /*check if .data? .string? .struct? */
        if ((is_data = isDataSymbol(trimmedline)))
            if (is_label)
            {
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/
                token = strtok(trimmedline,ARGUMENT_SEPARATOR);
                token = strtok(NULL,ARGUMENT_SEPARATOR);
                printf("trimmed line:%s\n",token);
                if(isData(trimmedline))
                {
                    printf("Calculating numbers\n");
                    /*calculateNumbers()*/
                }
                else if (isString(trimmedline))
                {
                    printf("Calculating string\n");
                    continue;
                }
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
        /* insert to symbol as code with IC value*/
        if (is_label)
            no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);

        /* check instruction, if not exist, add error. */

        /*check operands and count them*/
        /*build binary code of the instruction*/
        /* IC --> IC +L */
    }
    /* Finished reading the file*/
    if (!no_error)
        return;
    /* update symbol list data adding the right IC */
    updateData(head);
    print_symbol(head);
    /*Start second pass*/
    fclose(processedfile);
    /*secondpass(filename);*/
}

void init_label(char *label)
{
    int i;
    for(i=0;i<MAX_LABEL_LENGTH;i++)
        label[i] = '\0';
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