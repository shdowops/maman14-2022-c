#include "firstpass.h"
long IC, DC;
long linenumber;
extern Symbol *head, *tail;

void firstpass(char *filename)
{
    int op_type;
    bool is_label, no_error, is_data, is_code, is_entry, is_extern;
    char line[MAX_LINE_LENGTH], trimmedline[MAX_LINE_LENGTH], label[MAX_LABEL_LENGTH];
    char *token, *savedbinarydata;
    FILE *processedfile = fopen(filename, "r");
    
    head = NULL;
    IC = 100;
    DC = 0;
    linenumber = 0;
    no_error = true;

    if (processedfile == NULL)
    {
        alertFileError(ER_OPEN_FILE);
        return;
    }
    
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))/*get next line*/
    {
        memset(label, 0, MAX_LABEL_LENGTH - 1);
        savedbinarydata = NULL;
        is_label = is_data = is_code = is_entry = is_extern = false;
        ++linenumber;
        strcpy(trimmedline, trim(line));
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        is_label = isLabel(trimmedline, label); /*checking if it is a label */

        if ((is_data = isDataSymbol(trimmedline))) /*checking if it is a .data, .string, or .struct*/
            if (is_label)                          /*If it is a label*/
            {
                no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /*creating a new data Symbol*/
                token = strtok(trimmedline, LINE_SPACE);
                token = trim(strtok(NULL, LINE_SPACE));
                /*Adding binary data*/
                if (isDataDeclaration(trimmedline))
                    no_error &= checkNumbers(token, &savedbinarydata);
                else if (isStringDeclaration(trimmedline))
                    no_error &= checkString(token, &savedbinarydata);
                else
                    no_error &= checkStruct(token, &savedbinarydata);

                savedbinarydata[strlen(savedbinarydata) - 1] = '\0';
                tail->binarydata = savedbinarydata;
                continue;
            }

        if ((is_entry = isEntry(trimmedline)) || (is_extern = isExtern(trimmedline))) /*Checking if entry or extern*/
        {
            if (is_extern) /*If is an extern*/
            {
                
                token = strtok(trimmedline, ARGUMENT_SEPARATOR);
                token = strtok(NULL, ARGUMENT_SEPARATOR);
                no_error &= add_symbol(token, token, is_code, is_data, is_entry, is_extern);
                tail->binarydata = NULL;
            }
            continue;
        }

        is_code = true;
        no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /* create new code symbol */
        token = (char *)malloc(sizeof(char *) * strlen(trimmedline));
        strcpy(token, trimmedline);
        token = strtok(token, ARGUMENT_SEPARATOR);                         /*get instruction*/
        no_error &= isCommand(token, &op_type);                            /*check instruction, identify type, if not exist, alert appropriate error. */
        no_error &= check_opcode(trimmedline, &op_type, &savedbinarydata); /*check operands and count them*/
        free(token);
        strcat(savedbinarydata, ABSOLUTE);
        tail->binarydata = savedbinarydata;
    }
    /* Finished reading the file*/
    if (!no_error)
        return;

    updateData(head);
    fclose(processedfile);
    /*Start second pass*/
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
