#include "firstpass.h"

long IC, DC;
long linenumber;
extern Symbol *head, *tail;

void firstpass(char *filename)
{
    int op_type;
    bool is_label, no_error, is_data, is_code, is_entry, is_extern;
    char line[MAX_LINE_LENGTH], trimmedline[MAX_LINE_LENGTH], label[MAX_LABEL_LENGTH], binarydata[BINARY_LENGTH];
    char *token, *savedbinarydata;
    FILE *processedfile = fopen(filename, "r");
    head = NULL;
    IC = 0;
    DC = 0;
    linenumber = 0;
    no_error = true;
    savedbinarydata = NULL;

    /*read next line from file*/
    if (processedfile == NULL)
    {
        alertFileError(ER_OPEN_FILE); /* Add error unable to open file*/
        return;
    }

    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        memset(label, 0, MAX_LABEL_LENGTH - 1); /*Reset the label to nothing*/
        memset(binarydata,0,BINARY_LENGTH -1);
        is_label = is_data = is_code = is_entry = is_extern = false;
        ++linenumber;
        strcpy(trimmedline, trim(line));
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*is it a label? */

        if ((is_data = isDataSymbol(trimmedline))) /*is it .data? .string? .struct? */
            if (is_label)
            {
                savedbinarydata = NULL;
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/
                token = strtok(trimmedline, LINE_SPACE);
                token = trim(strtok(NULL, LINE_SPACE));
                if (isDataDeclaration(trimmedline))
                    no_error &= checkNumbers(token, &savedbinarydata);
                else if (isStringDeclaration(trimmedline))
                    no_error &= checkString(token, &savedbinarydata);
                else
                    no_error &= checkStruct(token, &savedbinarydata);
                
                savedbinarydata[strlen(savedbinarydata)-1] = '\0';
                tail->binarydata = savedbinarydata;
                continue;
            }

        if ((is_entry = isEntry(trimmedline)) || (is_extern = isExtern(trimmedline))) /*is it .extern? .entry? */
        {
            if (is_extern)
            {
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern);
                tail->binarydata = savedbinarydata;
            }
            continue;
        }

        is_code = true; /*all conditions failed - so it's code line*/

        no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /* insert to symbol as code with IC value*/
        token = (char *)malloc(strlen(trimmedline));
        strcpy(token, trimmedline);
        token = strtok(token, ARGUMENT_SEPARATOR);                   /*get instruction*/
        no_error &= isCommand(token, &op_type);                      /* check instruction, if not exist, add error. */
        no_error &= check_opcode(trimmedline, &op_type, binarydata); /*check operands and count them*/
        free(token);
        savedbinarydata = (char*)malloc(strlen(binarydata));
        strcat(binarydata,INSTRUCTION_ARE_BITS);
        strcpy(savedbinarydata,binarydata);
        tail->binarydata = savedbinarydata;
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

void updateData(Symbol *head)
{
    while (head != NULL)
    {

        if (head->is_Data)
            head->address += IC;
        head = head->next;
    }
}
