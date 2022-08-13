#include "firstpass.h"

long IC, DC;
long linenumber;
extern Symbol *head, *tail;

void firstpass(char *filename)
{
    int op_type, length;
    bool is_label, no_error, is_data, is_code, is_entry, is_extern;
    char line[MAX_LINE_LENGTH], trimmedline[MAX_LINE_LENGTH], label[MAX_LABEL_LENGTH], *token;
    FILE *processedfile = fopen(filename, "r");
    head = NULL;
    IC = 100;
    DC = linenumber = 0;
    no_error = true;

    /*read next line from file*/
    if (processedfile == NULL)
    {
        alertFileError(ER_OPEN_FILE);         /* Add error unable to open file*/
        return;
    }

    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        memset(label,0,MAX_LABEL_LENGTH-1); /*Reset the label to nothing*/
        is_label = is_data = is_code = is_entry = is_extern = false;
        ++linenumber;
        strcpy(trimmedline, trim(line));
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*is it a label? */

        if ((is_data = isDataSymbol(trimmedline)))         /*is it .data? .string? .struct? */
            if (is_label)
            {
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/
                token = strtok(trimmedline, LINE_SPACE);
                token = trim(strtok(NULL, LINE_SPACE));
                if (isData(trimmedline))
                    no_error &= checkNumbers(token);
                else if (isString(trimmedline))
                    no_error &= checkString(token);
                else
                    no_error &= checkStruct(token);
                continue;
            }

        if ((is_entry = isEntry(trimmedline)) || (is_extern = isExtern(trimmedline)))         /*is it .extern? .entry? */
        {
            if (is_extern)  
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
            continue;
        }

        is_code = true; /*all conditions failed - so it is code*/
        
        no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /* insert to symbol as code with IC value*/
        no_error &= isCommand(trimmedline, &op_type); /* check instruction, if not exist, add error. */

        no_error &= check_opcode(trimmedline, &op_type, &length); /*check operands and count them*/
        /*build binary code of the instruction*/
        /* IC --> IC +L */
    }
    /* Finished reading the file*/
    if (!no_error)
        return;
    /* update symbol list data adding the right IC */
    updateData(head);
    /* print_symbol(head);*/
    /*Start second pass*/
    fclose(processedfile);
    /*secondpass(filename);*/
}

void reset_label(char *label)
{
    int i;
    for (i = 0; i < MAX_LABEL_LENGTH; i++)
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

bool checkNumbers(char * line)
{
    int count = 0;
    if(line[START_OF_LINE]==COMMA)
    {
        alertError(ER_DATA_BEGINS_WITH_COMMA);
        return false;
    }
    if(!isdigit(line[strlen(line)-1]))
    {
        alertError(ER_DATA_ENDS_WITH_COMMA);
        return false;
    }
    while((line = strtok(NULL,ARGUMENT_SEPARATOR)))
        count++;

    DC+=count;
    return true;
}

bool checkString(char * line)
{
    char * temp = strtok(line,"\"");
    if(strcmp(line,temp)==0)
    {
        alertError(ER_STRING_WITHOUT_QUOTES);
        return false;
    }

    DC+=strlen(line);
    return true;
}

bool checkStruct(char * line)
{
    line = strtok(NULL,ARGUMENT_SEPARATOR);
    DC+=strlen(line);
    return true;
}